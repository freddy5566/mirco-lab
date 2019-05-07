#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    char buf[1024] = "";
    FILE *fp = fopen("/dev/demo","w+");
	
	char* command = argv[1];
    char* action = argv[2];
	
	int i = 0;
//command: LED1
	for (i = 0; i < strlen(command); i++)
	{
		buf[i] = command[i];
	}
	
	//buf[i + 1] = action == "on";
	if (action[1]=='n'){
	//on
		strcat(buf,"on");
		//printf("buf: %s", buf);
	}
	else {strcat(buf,"off");}
	if(fp == NULL)
    {
        printf("can't open device!\n");
        return 0;
    }

    fwrite(buf,sizeof(buf),1,fp);
	printf("%s",buf);
    fclose(fp);
    return 0;
}
