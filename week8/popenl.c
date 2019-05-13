#include <stdio.h>

int main(int argc, char *argv[])
{

	FILE *fp;
	char buf[501];
	int ch;
	char command[500] = "";

	if (argc > 1)
	{
		printf("search target is %s\n", argv[1]);
		strcpy(command, "ls -R -l | grep ");
		strcat(command, argv[1]);
	}
	else
	{
		strcpy(command, "ls -R -l");
	}

	printf("command is %s\n", command);

	printf("Reading the pipe line ...\n");

	fp = popen(command, "w");
	if (fp != NULL)
	{

		ch = fread(buf, sizeof(char), 500, fp);
		if (ch > 0)
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
		return 1;
	}
}
