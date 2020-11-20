#include <unistd.h>
#include <sys/types.h>

void printIdentifier()
{
 printf("ID:\nUser Effective: %d\nGroup Effective: %d\nUser Real: %d\nGroup Real: %d\n", geteuid(), getegid(), getuid(), getgid()); 
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
	case 'i': printIdentifier();  break;
	case 's': 
	
	}
}
return 0;
}
