#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
printf("Real id - %d\n", getuid());
printf("Effective id - %d\n", geteuid());
FILE* f = fopen(argv[1], "r");
if(f == NULL)
       {
               perror("File cant be opened\n");
       }
else
       {
               printf("File can be opened\n");
               fclose(f);
       }
if (setuid(getuid())!=0)
{
	printf("Error while using setuid\n");
	return -1;
}
else
{
	printf("Seuid used successful\n");
}
f = fopen(argv[1], "r");
if(f == NULL)
       {
               perror("File cant be opened\n");
       }
else
       {
               printf("File can be opened\n");
               fclose(f);
       }
return 0;
}

