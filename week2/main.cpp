#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

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

int main(int argc, char *argv[]) {
	
	if (argv[1] != "Mode_Shine") {
		int gpio = atoi(argv[1]);
		gpio_export(gpio);
		gpio_set_dir(gpio, "out");
		int value = argv[2] == "on" ? 1 : 0;
		gpio_set_value(gpio, value);
	} else {

	}

	return 0;

}
