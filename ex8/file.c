#include <sys/types.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int fileClosing(int _fd)
{
	if (close(_fd) != 0)
	{
		perror(errno);
		return -1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("wrong parameters\n");
		return -1;
	}
	printf("try %s to open\n", argv[1]);
	int fd = open(argv[1],O_RDONLY);
	if (fd  == -1)
	{
		perror(errno);
		fileClosing(fd);
		return -1;
	}
	off_t fileSize = 0;
	fileSize = lseek(fd,0,SEEK_END);
	printf("file opened with %d size\n", fileSize);
	if (lockf(fd,F_TEST,fileSize) != 0)
	{
		printf("file locked, can't open\n");
		fileClosing(fd);
		return -1;
	}
	printf("file unlocked\n");
	//if (lockf(fd,F_LOCK,fileSize) != 0)
	if (flock(fd,LOCK_SH) != 0);
	{
		perror(errno);
		fileClosing(fd);
		return -1;
	}
	printf("file locked by this programm\n");
	system("nano input.txt");
	//if (lockf(fd,F_ULOCK,fileSize) != 0)
	if (flock(fd,LOCK_UN) != 0)
	{
		perror(errno);
		fileClosing(fd);
		return -1;
	}
	return fileClosing(fd);
}
