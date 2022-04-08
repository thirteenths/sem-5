/*Написать программу, запускающую не мене двух новых процессов системным вызовом fork(). В предке вывести собственный идентификатор (функция getpid()), идентификатор группы ( функция getpgrp())  и идентификаторы потомков. В процессе-потомке вывести собственный идентификатор, идентификатор предка (функция getppid()) и идентификатор группы. Убедиться, что при завершении процесса-предка потомок, который продолжает выполняться, получает идентификатор предка (PPID), равный 1 или идентификатор процесса-посредника.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int childpid_1;
    int childpid_2;
    if ((childpid_1 = fork()) == -1)
    {
       perror("Can’t fork.\n");
       exit(1);
    }
    else if (childpid_1 == 0)
    {
        printf("\nChild:  id = %d \tparent_id = %d \tgroup_id = %d\n", getpid(), getppid(), getpgrp());
        sleep(1);
        printf("\nChild:  id = %d \tparent_id = %d \tgroup_id = %d\n", getpid(), getppid(), getpgrp());
        return 0;
    }

    if ((childpid_2 = fork()) == -1)
    {
        perror("Can’t fork.\n");
        exit(1);
    }
    else if (childpid_2 == 0)
    {
        printf("\nChild:  id = %d \tparent_id = %d \tgroup_id = %d\n", getpid(), getppid(), getpgrp());
        sleep(1);
        printf("\nChild:  id = %d \tparent_id = %d \tgroup_id = %d\n", getpid(), getppid(), getpgrp());
        return 0;
    }

    printf("Parent: id = %d	group_id  = %d \tchildren = %d %d\n", getpid(), getpgrp(), childpid_1, childpid_2);
    return 0;
} 
