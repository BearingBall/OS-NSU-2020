#include <unistd.h>
#include <sys/types.h>

void printUndefined(int c)
{
	printf("operation %c undefined\n", c);	
}

void printIdentifierUserAndGroup()
{
	printf("ID:\nUser Effective: %d\nGroup Effective: %d\nUser Real: %d\nGroup Real: %d\n", geteuid(), getegid(), getuid(), getgid()); 
}

void setProccessAsLedear()
{
	if (setsid() == 0)
	{
		printf("successful\n");
	}
	else
	{
		perror(errno);
	}
}

void printIdentifierProccesses()
{
	printf("Proccess ID = %d\nParent-proccess ID = %d\nGroup-proccess ID = %d\n", getpid(), getppid(), getid()); 
}

void printUlimit()
{
	printf("Ulimit =%ld\n", ulimit(UL_GETFSIZE,0));
}

void setUlimit(char* tmp)
{
	long size = atol(arg);
	if (size == 0)
	{
		printf("wrong ulimit value\n");
	}
	else
	{
		size = ulimit(UL_SETFSIZE, size);
	}
}

void printCoreFileSize()
{
	
}


int main(int argc, char *argv[])
{
		if (argc == 1)
		{
			printf("Put more than 0 arguments\n");
			return 0;
		}
	int c;
	while((c=getopt(argc,argv,"ispuU:cC:dvV:")) != -1)
	{
		switch (c)
		{
			case 'i': printIdentifierUserAndGroup();  break;
			case 's': setProccessAsLedear(); break;
     			case 'p': printIdentifierProccesses(); break;
     			case 'u': printUlimit(); break;
     			case 'U': setUlimit(optarg); break;
			case 'c': printCoreFileSize(); break;
     			case 'C': setCoreFileSize(); break;
     			case 'd': printDirectory(); break;
     			case 'v': printVariables(); break;
     			case 'V': setVariable(); break;
      			default:  printUndefined(c); break;
		}
	}
	return 0;
}
