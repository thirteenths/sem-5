#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int childpid[2];
    int status;
    //pid_t childpidw;

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
            return 0;
        }
        
    }

    printf("Parent: id = %d	group_id  = %d \tchildren = %d %d\n", getpid(), getpgrp(), childpid[0], childpid[1]);

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

    return 0;
}