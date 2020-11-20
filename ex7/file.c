#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "stdio.h"
#include <unistd.h>
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
	off_t fileSize = 0;
	fileSize = lseek(fb,0,SEEK_END);
	char* src;
	if ((src = mmap(0,fileSize,PROT_READ,MAP_SHARED,fb,0)) == MAP_FAILED)
	{
		printf("Mmap error\n");
		close(fb);
		return 0;
	}
	int tableCurret = 1;
	int* table = malloc(TABLE_SIZE*sizeof(int));
	if (table == NULL)
	{
		printf("Memory error\n");
		return 0;
	}
	table[0] = 0;
	for(int i=0;i<fileSize;++i)
	{
		if (src[i]=='\n')
		{
			table[tableCurret] = i+1;
			tableCurret++;
			if (tableCurret >= TABLE_SIZE)
			{
				printf("Table size not enough\n");
				free(table);
				return 0;
			}
		}
	}
printf("Table:\n");
for(int i=0;i<tableCurret;++i)
{
	printf("%d - %d\n",i,table[i]);
}
int stringNumber =0; 
fd_set rfds;
    struct timeval tv;
    int retval;

FD_ZERO(&rfds);
FD_SET(0, &rfds);
tv.tv_sec = 5;
    tv.tv_usec = 0;
    printf("You have 5 second to put number or programm will be closed\n");
    retval = select(1, &rfds, NULL, NULL, &tv);

if (retval)
{
	while(1)
	{
		scanf("%d",&stringNumber);
		if (stringNumber == 0)
		break;

		if ((stringNumber>=0)&&(stringNumber<tableCurret))
		{
			char c;
			for(int i=table[stringNumber-1];i<table[stringNumber];++i)
			{
				printf("%c",src[i]);
			}
		}
		else
		{
			printf("Valid data from 0 to %d\n",tableCurret);
		}
	}
}
else
{
	printf("Time is out\nFull file:\n");
	for(int j=0;j<fileSize;++j)
	{
		printf("%c",src[j]);
	}
}
munmap(src,fileSize);
close(fb);
free(table);
return 0;
}
