#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#define STRING_SIZE 300


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("wrong argv\n");
	}
	int pipe_ends[2];
	if (pipe(pipe_ends) == -1)
    	{
        	printf("pipe error\n");
        	return -1;
    	}

	pid_t pid;
	pid = fork();
	if (pid == -1)
	{
		printf("fork -1\n");
		return -1;
	}
	char str[STRING_SIZE];
	if (pid == 0)
	{//child
		close(pipe_ends[1]);
        	if (read(pipe_ends[0], str, 100) == -1)
        	{
            		printf("read error");
            		close(pipe_ends[0]);
            		return -1;
        	}
        	printf("received from pipe  %s\n", str);
        	for (int i = 0; i < strlen(str); i++)
        	{
            		str[i] = (char)toupper(str[i]);
        	}
        	printf("after toupper %s\n", str);
        	close(pipe_ends[0]);
	}
	else
	{
		close(pipe_ends[0]);
        	strcpy(str, argv[1]);
        	if (write(pipe_ends[1], str, strlen(str) + 1) == -1)
        	{
            		printf("write error");
            		close(pipe_ends[1]);
            		return -1;
        	}
        	printf("sent to pipe %s\n", str);
        	close(pipe_ends[1]);

		int status;
		 do
        	{
            		pid_t killedChildPid = waitpid(pid, &status, 0);
            		if(killedChildPid == -1)
            		{
                		printf("waitpid failde\n");
                		return 0;
            		}

           		 if (WIFEXITED(status))
            		{
                		printf("Child terminated normally, status = %d\n", WEXITSTATUS(status));
            		}
            		else if (WIFSIGNALED(status))
            		{
                		printf("Killed by signal with number %d\n", WTERMSIG(status));
            		}
            		else if (WIFSTOPPED(status))
            		{
                		printf("stopped by signal %d\n", WSTOPSIG(status));
            		}
            		else if (WIFCONTINUED(status))
            		{
               			 printf("Child process was resumed\n");
            		}
        		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 0;
}
