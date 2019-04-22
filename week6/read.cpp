#include<stdio.h>

int main()
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


