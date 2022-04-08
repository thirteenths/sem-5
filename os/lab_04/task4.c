/*Написать программу, в которой предок и потомок обмениваются
сообщением через программный канал.*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int childpid_1;
    int childpid_2;
    int status;

    char getMes[20], sendMes[20];

    int fd[2];
    pipe(fd);

    if ((childpid_1 = fork()) == -1)
    {
       perror("Can’t fork.\n");
       exit(1);
    }
    else if (childpid_1 == 0)
    {
        printf("\nChild:  id = %d \tparent_id = %d \tgroup_id = %d\n", getpid(), getppid(), getpgrp());

        sprintf(sendMes, "Hahahahahahahahahahahahaha");
        //close(fd[0]);
        write(fd[1], sendMes, sizeof(sendMes));
        close(fd[1]);
        return 0;
    }
    //close(fd[1]);


    
    
    if ((childpid_2 = fork()) == -1)
    {
        perror("Can’t fork.\n");
        exit(1);
    }
    else if (childpid_2 == 0)
    {
        printf("\nChild:  id = %d \tparent_id = %d \tgroup_id = %d\n", getpid(), getppid(), getpgrp());
        sprintf(sendMes, "Meh");
        //close(fd[0]);
        write(fd[1], sendMes, sizeof(sendMes));
        close(fd[1]);
        return 0;
    }

    //printf("Parent: id = %d	group_id  = %d \tchildren = %d %d\n", getpid(), getpgrp(), childpid_1, childpid_2);
    
    
    
    for (int i = 0; i < 2; i++)
	{
		printf("\n--- Parent is waiting ---");
		
		pid_t childpid = wait(&status);
		if (childpid == -1)
		{
			if (errno == ECHILD)
				printf("Process does not have any unwaited for children\n");
			else if (errno == EINTR)
				printf("Call interrupted by signal\n");
			else if (errno == EINVAL)
				printf("Wrong argument\n");
			exit(1);
		}
		
		printf("\nChild finished: pid = %d\n", childpid);

		if (WIFEXITED(status))
			printf("Child exited normally with code %d\n", WEXITSTATUS(status));
		else printf("Child terminated abnormally\n");
		
		if (WIFSIGNALED(status))
			printf("Child exited due to uncaught signal # %d\n", WTERMSIG(status));
			
		if (WIFSTOPPED(status))
			printf("Child stopped, signal # %d\n", WSTOPSIG(status));
	}
    
    
    status = read(fd[0], getMes, sizeof(getMes));

    if (status == -1)
    {
        printf("Error 1 read\n");
        exit(1);
    }

    //close(fd[0]);

    printf("\nParents : %s\n", getMes);

    status = read(fd[0], getMes, sizeof(getMes));

    if (status == -1)
    {
        printf("Error 1 read\n");
        exit(1);
    }


    printf("\nParents : %s\n", getMes);

    close(fd[0]);


    return 0;
} 
