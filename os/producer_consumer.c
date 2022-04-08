#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N 20

#define sb 0
#define se 1
#define sf 2



#define P_COUNT 3
#define C_COUNT 3

struct sembuf producer_start[2] = {
    {se, -1, IPC_CREAT | SEM_UNDO}, 
    {sb, -1, IPC_CREAT | SEM_UNDO}}; 

struct sembuf producer_stop[2]  =  {
    {sb, 1, IPC_CREAT | SEM_UNDO}, 
    {sf, 1, IPC_CREAT | SEM_UNDO}};

struct sembuf consumer_start[2] = {
    {sf, -1, IPC_CREAT | SEM_UNDO}, 
    {sb, -1, IPC_CREAT | SEM_UNDO}};

struct sembuf consumer_stop[2]  =  {
    {sb, 1, IPC_CREAT | SEM_UNDO}, 
    {se, 1, IPC_CREAT | SEM_UNDO}};

pid_t pidp[P_COUNT + C_COUNT];

void catch_sigint(int sig_num)
{
    for (int i = 0; i < P_COUNT + C_COUNT; i++)
    {
        kill(pidp[i], SIGTERM);
    }
}

void producer(int *buf, int *prod, int fd, int i, int *val)
{
    while(1)
    {
        sleep(rand() % 3);

        if (semop(fd, producer_start, 2) == -1)
        {
           perror("semop p\n");
           exit(1);
        }

        (*val)++;
        *val = 65 + ((*val - 65) % 26);
        if (++(*prod) == N)
        {
            *prod = 0;
        }
	    *(buf + *prod) = *val;
        printf("Producer[%d] value: %c\n", i, *val);

        if (semop(fd, producer_stop, 2) == -1)
        {
            perror("semop v\n");
            exit(1);
        }
    }
}

void consumer(int *buf, int *cons, int fd, int i)
{
    while(1)
    {
        int val;

	    sleep(rand() % 5);

        if (semop(fd, consumer_start, 2) == -1)
        {
            perror("semop p\n");
            exit(1);
        }

        if (++(*cons) == N)
        {
            *cons = 0;
        }
        val = *(buf + *cons);
        printf("Consumer[%d] value: %c\n", i, val);
        if (semop(fd, consumer_stop, 2) == -1)
        {
            perror("semop v\n");
            exit(1);
        }
    }
}

int main()
{
    int status;
    int buf_id;
    int perms = S_IRWXU | S_IRWXG | S_IRWXO;
    int *buf;
    int *cons;
    int *prods;

    int fd = semget(IPC_PRIVATE, 3, IPC_CREAT | perms);

    signal(SIGINT, catch_sigint);

    if (fd == -1)
    {
        perror("semget\n");
        exit(1);
    }

    if ((semctl(fd, se, SETVAL, N) == -1) || (semctl(fd, sb, SETVAL, 1) == -1) || semctl(fd, sf, SETVAL, 0) == -1)
    {
	    perror("ctl\n");
        exit(1);
    }

    if ((buf_id = shmget(IPC_PRIVATE, (N + 3) * sizeof(int), IPC_CREAT | perms)) == -1)
    {
        perror("shmget\n");
        exit(1);
    }

    buf = (int *) shmat(buf_id, 0, 0);
    if (buf == (int *)-1)
    {
        perror("shmat\n");
        exit(1);
    }

    //
    prods = buf;
    cons = buf + 1;
    int *val = buf + 2;
    buf += 3;

    *val = 64;
    *prods = 0;
    *cons = 0;

    for (int i = 0; i < P_COUNT; ++i) {
        if ((pidp[i] = fork()) == -1) {
            perror("Producer fork failed.");
            exit(EXIT_FAILURE);
        }
        if (pidp[i] == 0) {
            producer(buf, prods, fd, i, val);
            return EXIT_SUCCESS;
        }
    }

    for (int i = 0; i < C_COUNT; ++i) {
        if ((pidp[P_COUNT + i] = fork()) == -1) {
            perror("Consumer fork failed.");
            exit(EXIT_FAILURE);
        }
        if (pidp[P_COUNT + i] == 0) {
            consumer(buf, cons, fd, i);
            return EXIT_SUCCESS;
        }
    }

    for (int i = 0; i < C_COUNT + P_COUNT; ++i) {
        int status;
        if (wait(&status) == -1) {
            perror("Child error.");
            exit(EXIT_FAILURE);
        }
        if (!WIFEXITED(status)) {
            printf("Child process terminated abnormally\n");
        }
    }

    if (shmdt(buf) == -1) 
    {
        perror("shmdt\n");
	    exit(1);
    }
    return 0;
}