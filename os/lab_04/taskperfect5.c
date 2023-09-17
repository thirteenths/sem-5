#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>

static int sigFlag = 0;

void catch_sig(int sig_numb)
{
    signal(sig_numb, catch_sig);
    sigFlag = 1;
    printf("catch_sig %d\n", sig_numb);
}

int main()
{
    int childpid[2];
    int status;

    char getMes[30];
    char sendMes[2][24];

    sprintf(sendMes[0], "\nHahahahahahahahahahahahaha");
    sprintf(sendMes[1], "\nMeh");

    int fd[2];
    status = pipe(fd);
    if (status == -1)
    {
        printf("Can't pipe\n");
        exit(1);
    }

    signal(SIGINT, catch_sig);
    sleep(5); 

    for (int i = 0; i < 2; i++)
    {
        childpid[i] = fork();
        if (childpid[i] == -1)
        {
            perror("Can't fork.\n");
            exit(1);
        }
        else if (childpid[i] == 0)
        {
            printf("\nChild:  id = %d \tparent_id = %d \tgroup_id = %d\n", getpid(), getppid(), getpgrp());

            if (sigFlag){

                close(fd[0]);

                write(fd[1], sendMes[i], sizeof(sendMes[i]));

            }
            return 0;
        }
        
    }

    

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

    close(fd[1]);
    
    read(fd[0], getMes, sizeof(getMes));

    printf("\nParents read messages: %s\n", getMes);

    printf("\nParent: id = %d	group_id  = %d \tchildren = %d %d\n", getpid(), getpgrp(), childpid[0], childpid[1]);

    return 0;
}