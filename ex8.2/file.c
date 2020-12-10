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
#include <string.h>

int fileClosing(int _fd)
{
	if (close(_fd) != 0)
	{
		printf("error %d\n", errno);
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
	int fd = open(argv[1],O_RDWR);
	if (fd  == -1)
	{
		printf("error %d\n",errno);
		fileClosing(fd);
		return -1;
	}
	off_t fileSize = 0;
	fileSize = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);
	printf("file opened with %d size\n", fileSize);
	struct flock fl_info;
	memset(&fl_info, 0, sizeof(fl_info));
	fl_info.l_type = F_WRLCK;
    	fl_info.l_whence = SEEK_SET;
    	fl_info.l_start = 0;
    	fl_info.l_len = 0;
	if (fcntl(fd, F_GETLK, &fl_info) == -1) 
	{
       		printf("F_GETLK returned not null\n");
        	fileClosing(fd);
		return;
    	}
	if (fl_info.l_type != F_UNLCK) 
	{
		printf("file already locked\n");
		fileClosing(fd);
		return;
	}
	else
	{
		printf("file already unlocked\n");
	}
	fl_info.l_type = F_WRLCK;
    	if ( fcntl(fd, F_SETLK, &fl_info) == -1) 
	{
        	perror("F_SETLK error");
		fileClosing(fd);
        	return;
    	}
	printf("file locked by this programm\n");

	system("nano input.txt");
	
	fl_info.l_type = F_UNLCK;
        if ( fcntl(fd, F_SETLK, &fl_info) == -1)
        {
                perror("F_SETLK error\n");
                fileClosing(fd);
                return;
        }

return fileClosing(fd);
}
