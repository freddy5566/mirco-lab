#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <map>
#define PIPE_BUF 512

using namespace std;

int gpio_export(unsigned int gpio){
	int fd, len;
	char buf[64];
	
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd<0) {
		perror("gpio/export");
		return fd;
	}
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf ,len);
	close(fd); //close file
	
	return 0;
}

int gpio_unwxport(unsigned int gpio){
	int fd, len;
	char buf[64];
	
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd<0) {
		perror("gpio/export");
		return fd;
	}
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf ,len);
	close(fd); //close file
	
	return 0;

}

int gpio_set_dir(unsigned int gpio, string dirStatus){
	int fd;
	char buf[64];

	snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);
	fd = open(buf, O_WRONLY);
	if (fd<0){
		perror("gpio/direction");
		return fd;
	}
	
	if (dirStatus == "out"){
		write(fd, "out", 4);
	}
	else 
		write(fd, "in", 3);
	
	close(fd);
	return 0;
}


int gpio_set_value(unsigned int gpio, int value) {
	int fd;
	char buf[64];

	snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);
	fd = open(buf, O_WRONLY);

	if (fd<0){
			perror("gpio/direction");
			return fd;
		}
		
	if (value == 0){
		write(fd, "0", 2);
	}
	else 
		write(fd, "1", 2);
		
	close(fd);
	return 0;

	
}

void setup_gpio() {
	gpio_export(166);
	gpio_export(164);
	gpio_export(162);
	gpio_export(160);
	gpio_set_dir(166, "out");
	gpio_set_dir(164, "out");
	gpio_set_dir(162, "out");
	gpio_set_dir(160, "out");
}

void shine(int times) {
	int value = 1;	
	for (int i = 0; i < times; i++) {
		cout << "value = " << value << endl;
		cout << "!value = " << !value << endl; 
		gpio_set_value(166, value);
		gpio_set_value(164, value);
		gpio_set_value(162, !value);
		gpio_set_value(160, !value);
		value = !value;
		sleep(1);
		}
}

int main(int argc, char *argv[]) {
	string commend = string(argv[1]);
	map<string, int> Leds;
	Leds["LED1"] = 166;
	Leds["LED2"] = 164;
	Leds["LED3"] = 162;
	Leds["LED4"] = 160;
	
    setup_gpio();

	int fd[2];
	char buf[PIPE_BUF];
	int pid, len;
	
	if ((pipe(fd)) < 0) 
	{
        perror("pipe error");
        exit(1);
    }
    pid = fork();

    if (pid < 0)
    {
        perror("fork error");  
        exit(1);
    }
    
    if(pid == 0) 
    {
        close(fd[1]);
        while ((len = read(fd[0], buf, PIPE_BUF)) > 0)
        {
            buf[len] = '\0';
            printf("Read %d bytes \n", len);
            printf("content: %s \n", buf);
        }

        printf("pipe_buf: %s \n", PIPE_BUF);
        close(fd[0]);
    }

    if (pid > 0)
    {
        close(fd[0]);
        char writeBuf[] = "Hello pipe!";
        write(fd[1], writeBuf, strlen(writeBuf));
        close(fd[1]);
    }

    waitpid(pid, NULL, 0);
    exit(0);





	return 0;

}

