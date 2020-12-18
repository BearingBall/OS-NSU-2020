c#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#define COMMAND_LENGTH 200



int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("wrong argv\n");
	}
	pid_t pid;
	pid = fork();
	if (pid == -1)
	{
		printf("fork -1\n");
		return -1;
	}
	if (pid == 0)
	{
		//execlp("cat","cat",argv[1],(char*)NULL);
		char*  str = malloc(COMMAND_LENGTH*sizeof(char));
		str[0] = 'c';
		str[1] = 'a';
		str[2] = 't';
		str[3] = ' ';
		str[4] = '\0';
		str = strncat(str,argv[1]);
		if (system(str))
		{
			free(str);
			printf("cat error\n");
		}
		free(str);
	}
	else
	{
		int status;
		 do
        	{
            		//(*)The waitpid() system call : It suspends execution of the calling process until a child specified by pid argument has changed state.
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
