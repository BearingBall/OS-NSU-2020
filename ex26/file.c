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


void printStatus(int status)
{
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
}


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
	char str[STRING_SIZE] = "echo ";
	strcat(str,argv[1]);
	printf("trying popen with\n%s\n", str);
    	FILE *pipe = popen(str, "r");
    	if (pipe == NULL)
    	{
       		printf("popen error\n");
       		return -1;
    	}
	int length = fread(str, 1, STRING_SIZE, pipe);
    	int status = pclose(pipe);
    	if(status == -1)
    	{
        	printf("pclose error\n");
        	return -1;
	}
	printStatus(status);
	if (length == -1)
    	{
        	printf("fread from pipe error\n");
        	return -1;
    	}
	for(int i=0; i<length; ++i)
    	{
        	str[i] = toupper(str[i]);
    	}
	str[length] = '\0';
    	printf("pipe returned:\n%s\n", str);
    	return 0;
}
