//Написать программу, реализующую задачу «Читатели – писатели» по
//монитору Хоара с четырьмя функциями: Начать_чтение,
//Закончить_чтение, Начать_запись, Закончить_запись. В программе все
//процессы разделяют одиночную переменную в разделяемой памяти.
//Писатели ее только инкрементируют, читатели могут только читать
//значение этой переменной.
//Для реализации взаимоисключения используются семафоры.

#include <sys/stat.h>   
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define     SEM_WAITING_READERS     0
#define     SEM_WAITING_WRITERS     1
#define     SEM_ACTIVE_READERS      2
#define     SEM_ACTIVE_WRITERS      3

#define     SEM_BIN                 4

#define     NUM_W   3
#define     NUM_R   7


struct sembuf start_read_act[5] = 
{
    {SEM_WAITING_READERS, 1, IPC_CREAT | SEM_UNDO},     
	{SEM_WAITING_WRITERS, 0, IPC_CREAT | SEM_UNDO},     
    {SEM_ACTIVE_WRITERS, 0, IPC_CREAT | SEM_UNDO},      
    {SEM_ACTIVE_READERS, 1, IPC_CREAT | SEM_UNDO},      
	{SEM_WAITING_READERS, -1, IPC_CREAT | SEM_UNDO}    
};


struct sembuf stop_read_act[1] = 
{ 
    { SEM_ACTIVE_READERS, -1, SEM_UNDO }
};

struct sembuf stop_write_act[2] = 
{ 
    { SEM_ACTIVE_WRITERS, -1, SEM_UNDO },
    { SEM_BIN, 1, IPC_CREAT | SEM_UNDO}
};

struct sembuf start_write_act[5] = 
{ 
    {SEM_WAITING_WRITERS, 1, IPC_CREAT | SEM_UNDO},     
    {SEM_BIN, -1, IPC_CREAT | SEM_UNDO},         
    {SEM_ACTIVE_READERS, 0, IPC_CREAT | SEM_UNDO},      
    {SEM_ACTIVE_WRITERS, -1, IPC_CREAT | SEM_UNDO},      
    {SEM_WAITING_WRITERS, -1, IPC_CREAT | SEM_UNDO}   
};



void start_write(int id_sem)
{	
    int temp = semop(id_sem, start_write_act, 5);
    if (temp == -1)
    {
        perror("semop error");
        exit(6);
    }
}

void stop_write(int id_sem)
{
    int temp = semop(id_sem, stop_write_act, 2);
    if (temp == -1)
    {
        perror("semop error");
        exit(6);
    }
}

void start_read(int id_sem)
{	
    int temp = semop(id_sem, start_read_act, 5);
    if (temp == -1)
    {
        perror("semop error");
        exit(6);
    }
}

void stop_read(int id_sem)
{
    int temp = semop(id_sem, stop_read_act, 1);
    if (temp == -1)
    {
        perror("semop error");
        exit(6);
    }
}


void action_writer(int cur_id, int id_sem, int* addr)
{
    sleep(rand() % 2 + 1);

    while (1)
    {
        start_write(id_sem);

        (*addr)++;
        printf(">> WRITER %d: wrote %d\n", cur_id, *addr);

        stop_write(id_sem);

        sleep(rand() % 2 + 1);
    }
}

void action_reader(int cur_id, int id_sem, int* addr)
{
    sleep(rand() % 3 + 1);

    while (1)
    {
        start_read(id_sem);

        printf(">> READER %d: read %d\n", cur_id, *addr);

        stop_read(id_sem);

        sleep(rand() % 2 + 1);
    }
}

int main()
{
    srand(time(NULL));

    int perms = S_IRWXU | S_IRWXG | S_IRWXO;
    int swr, sww, sar, saw, sb, res;
    pid_t writers[NUM_W], readers[NUM_R];

    int id_sem = semget(IPC_PRIVATE, 5, IPC_CREAT | perms);
    if (id_sem == -1)
    {
        perror("semget error");
        exit(1);
    }

    swr = semctl(id_sem, SEM_WAITING_READERS, SETVAL, 0);
    sww = semctl(id_sem, SEM_WAITING_WRITERS, SETVAL, 0);
    sar = semctl(id_sem, SEM_ACTIVE_READERS, SETVAL, 0);
    saw = semctl(id_sem, SEM_ACTIVE_WRITERS, SETVAL, 1);
    sb = semctl(id_sem, SEM_BIN, SETVAL, 1);

    if (swr == -1 || sww == -1 || sar == -1 || saw == -1 || sb == -1)
    {
        perror("semctl error");
        exit(2);
    }

    int id_shm = shmget(IPC_PRIVATE, 1 * sizeof(int), IPC_CREAT | perms);
    if (id_shm == -1)
    {
        perror("shmget error");
        exit(3);
    }

    int* addr = (int*)shmat(id_shm, 0, 0);
    if (addr == (int*)-1)
    {
        perror("shmat error");
        exit(4);
    }

    for (int i = 0; i < NUM_W; i++)
    {
        writers[i] = fork();
        if (writers[i] == -1)
        {
            perror("fork error");
            exit(5);
        }

        if (writers[i] == 0)
            action_writer(i, id_sem, addr);

        rand();
    }

    for (int i = 0; i < NUM_R; i++)
    {
        readers[i] = fork();
        if (readers[i] == -1)
        {
            perror("fork error");
            exit(5);
        }

        if (readers[i] == 0)
            action_reader(i, id_sem, addr);

        rand();
    }

    int status, temp_id;
    for (int i = 0; i < NUM_R + NUM_W; i++)
    {
        temp_id = wait(&status);
        
        if (temp_id == -1)
        {
            perror("wait error");
            exit(7);
        }
    }

    if (shmctl(id_shm, IPC_RMID, NULL) == -1)
    {
        perror("shmctl error");
        exit(8);
    }

    if (shmctl(id_sem, 0, IPC_RMID) == -1)
    {
        perror("shmctl error");
        exit(8);
    }

    return 0;
}