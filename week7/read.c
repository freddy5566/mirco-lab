#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    char buf[1024] = "Lab6";
    FILE *fp = fopen("/dev/demo","w+");

    if(fp == NULL)
    {
        printf("can't open device!\n");
        return 0;
    }
    fread(buf,sizeof(buf),1,fp);
	printf("%s",buf);
    fclose(fp);
    return 0;
}


