#include <stdio.h>

int main ()
{

	FILE *fp;
	char buf[501];
	int ch;

	memset(buf, '\0', sizeof(buf));
	printf("Reading the pipe line ...\n");

	fp = popen("ls -l" ,"r");
	if (fp != NULL) 
	{

		ch = fread(buf, sizeof(char), 500, fp);
		if(ch>0)
		{

			printf("\File List :\n");
			printf("%s \n", buf);
		}
		pclose(fp);
	}
	else 
	{
		printf("pipe Error");
		return 1;
	}
	printf("\n Writing the binary file ... \n");
	fp = fopen("test.bin", "wb");

	if (fp == NULL)
	{
		printf("Can't open the file");
		retunr 1;
	}

}
