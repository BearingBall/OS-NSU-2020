#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "stdio.h"
#include <unistd.h>
#include <errno.h>
#define BUFFER_SIZE 100
#define TABLE_SIZE 100

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		printf("Put name of file in argument\n");
		return 0;
	}
	int fb = open(argv[1], O_RDONLY);
	if (fb == -1)
	{
		printf("File can't be opened\n");
		return 0;
	}
	printf("File \"%s\" opened\n",argv[1]);
	char* buffer = malloc(BUFFER_SIZE*sizeof(char));
	if (buffer == NULL)
	{
		printf("Memory error\n");
		return 0;
	}
	int tableCurret = 1;
	int* table = malloc(TABLE_SIZE*sizeof(int));
	if (table == NULL)
	{
		printf("Memory error\n");
		free(buffer);
		return 0;
	}
	table[0] = 0; 
	while(1) 
	{ 
		int readSize = read(fb, buffer, BUFFER_SIZE); 
		if (readSize == -1 && errno != EINTR)
		{
			perror("read error \n");
			free(buffer);
			free(table);
			return 0;
		}
		for(int i=0;i<readSize;++i)
		{
			if (buffer[i]=='\n')
			{
				table[tableCurret] = i+1;
				tableCurret++;
				if (tableCurret >= TABLE_SIZE)
				{
					printf("Table size not enough\n");
					free(buffer);
					free(table);
					return 0;
				}
			}
		}
		if (readSize != BUFFER_SIZE)
		{
			break;
		}
	}
printf("Table:\n");
for(int i=0;i<tableCurret;++i)
{
	printf("%d - %d\n",i,table[i]);
}


char* buffer2 = malloc(table[tableCurret]*sizeof(char));
if (buffer2 == NULL)
        {
                printf("Memory error\n");
                return 0;
        }
lseek(fb,0,SEEK_SET); 
read(fb,buffer2,table[tableCurret-1]);
int stringNumber =0;
while(1)
{
scanf("%d",&stringNumber);
if (stringNumber == 0)
{
break;
}
	if ((stringNumber>=0)&&(stringNumber<tableCurret))
	{
		for(int i=table[stringNumber-1];i<table[stringNumber];++i)
		{
			printf("%c",buffer2[i]);
		}
	}
	else
	{
	printf("Valid data from 0 to %d\n",tableCurret);
	}
}
close(fb);
free(buffer);
free(buffer2);
free(table);
return 0;
}
