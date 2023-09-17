#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define READERS_COUNT 5
#define WRITERS_COUNT 3

#define MAX_RAND 3

#define ACT_READER 0
#define ACT_WRITER 1
#define WAIT_READER 2
#define WAIT_WRITER 3
#define BIN_SEM 4


int* buf;

struct sembuf start_read[5] = {
    {WAIT_READER, 1, IPC_CREAT | SEM_UNDO},   
	{WAIT_WRITER, 0, IPC_CREAT | SEM_UNDO},   
    {ACT_WRITER, 0, IPC_CREAT | SEM_UNDO},    
    {ACT_READER, 1, IPC_CREAT | SEM_UNDO},    
	{WAIT_READER, -1, IPC_CREAT | SEM_UNDO}}; 

struct sembuf start_write[5] = {
    {WAIT_WRITER, 1, IPC_CREAT | SEM_UNDO},   
    {BIN_SEM, -1, IPC_CREAT | SEM_UNDO},      
    {ACT_READER, 0, IPC_CREAT | SEM_UNDO},    
    {ACT_WRITER, -1, IPC_CREAT | SEM_UNDO},    
    {WAIT_WRITER, -1, IPC_CREAT | SEM_UNDO}}; 

struct sembuf stop_read[1] = {
    {ACT_READER, -1, IPC_CREAT | SEM_UNDO}};

struct sembuf stop_write[2] = {
    {ACT_WRITER, 1, IPC_CREAT | SEM_UNDO},
    {BIN_SEM, 1, IPC_CREAT | SEM_UNDO}};


pid_t pidp[READERS_COUNT + WRITERS_COUNT];

void catch_sigint(int sig_num)
{
    for (int i = 0; i < READERS_COUNT + WRITERS_COUNT; i++)
    {
        kill(pidp[i], SIGTERM);
    }
}

void writer(int fd, int i)
{
    int stime;

    while(1)
    {
        stime = rand() % MAX_RAND;
        sleep(stime);
        
        if (semop(fd, start_write, 5) == -1)
        {
           perror("semop p\n");
           exit(1);
        }

        printf("Writer[%d] value: %d\n", i, ++(*buf));

        if (semop(fd, stop_write, 2) == -1)
        {
            perror("semop v\n");
            exit(1);
        }
    }
}

void reader(int fd, int i)
{
    int stime;

    while(1)
    {
        stime = rand() % MAX_RAND + 1;
        sleep(stime);

        if (semop(fd, start_read, 5) == -1)
        {
            perror("semop p\n");
            exit(1);
        }

        printf("Reader[%d] value: %d\n", i, *buf);

        if (semop(fd, stop_read, 1) == -1)
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
    int fd = semget(IPC_PRIVATE, 5 , IPC_CREAT | perms);

    signal(SIGINT, catch_sigint);

    if (fd == -1)
    {
        perror("semget\n");
        exit(1);
    }

    int ctrl_actR = semctl(fd, ACT_READER, SETVAL, 0);
    int ctrl_actW = semctl(fd, ACT_WRITER, SETVAL, 1); 
    int ctrl_waitW = semctl(fd, WAIT_WRITER, SETVAL, 0);
    int ctrl_waitR = semctl(fd, WAIT_READER, SETVAL, 0);
    int ctrl_bin_sem = semctl(fd, BIN_SEM, SETVAL, 1);

    if ((ctrl_actR == -1) || (ctrl_actW == -1) || (ctrl_waitR == -1) || (ctrl_waitW == -1) || (ctrl_bin_sem == -1))
    {
	    perror("ctrl\n");
        exit(1);
    }

    if ((buf_id = shmget(IPC_PRIVATE, 1 * sizeof(int), IPC_CREAT | perms)) == -1)
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

    *buf = 0;

    for (int i = 0; i < READERS_COUNT; ++i) {
        if ((pidp[i] = fork()) == -1) {
            perror("Reader fork failed.");
            exit(EXIT_FAILURE);
        }
        if (pidp[i] == 0) {
            reader(fd, i);
            return EXIT_SUCCESS;
        }
    }

    for (int i = 0; i < WRITERS_COUNT; ++i) {
        if ((pidp[READERS_COUNT + i] = fork()) == -1) {
            perror("Writer fork failed.");
            exit(EXIT_FAILURE);
        }
        if (pidp[READERS_COUNT + i] == 0) {
            writer(fd, i);
            return EXIT_SUCCESS;
        }
    }

    for (int i = 0; i < WRITERS_COUNT + READERS_COUNT; ++i) {
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