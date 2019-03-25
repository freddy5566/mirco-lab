#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <map>

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
	gpio_export(161);
	gpio_export(160);
	gpio_set_dir(166, "out");
	gpio_set_dir(161, "out");
	gpio_set_dir(164, "out");
	gpio_set_dir(160, "out");
}

void shine(int times) {
	int value = 1;	
	for (int i = 0; i < times; i++) 
	{
		gpio_set_value(166, value);
		gpio_set_value(164, value);
		gpio_set_value(161, !value);
		gpio_set_value(160, !value);
		value = !value;
		sleep(1);
	}
}

int main() {

	char *data;
	long m, n;

	setup_gpio();

	cout << "Content-type: text/html\n\n" << endl;
	cout << "<html><head><title>test</title></head>\n" << endl;
	
	data = getenv("QUERY_STRING");

	char myContent[128];

	if (strstr(data, "studentID"))
	{
		sscanf(data, "login=studentID&logincontent=%[a-zA-A0-9]&onoff=on&S=Submit", &myContent);
		printf("<p>選項: 學號</p>\n\n");
		printf("<p> content: %s <p>", myContent);
	}
	else if (strstr(data, "name"))
	{
		sscanf(data, "login=name&logincontent=%[a-zA-A0-9]&S=Submit", &myContent);
		printf("<p>選項: 姓名</p>\n\n");
		printf("<p> content: %s<p>", myContent);
	}

	if (strstr(data, "control1"))
	{
				gpio_set_value(166, 1);
				printf("<p>LED1 on</p>\n\n");
	} 
	else if(strstr(data, "control1=first&frequency=&onoff=off"))
	{
		gpio_set_value(166, 0);
		printf("<p>LED1 off</p>\n\n");
	}

	if (strstr(data, "control2"))
	{

				gpio_set_value(164, 1);
				printf("<p>LED2 on</p>\n\n");
	}
	else if(strstr(data, "control2=second&frequency=&onoff=off"))
	{
		gpio_set_value(164, 0);
		printf("<p>LED2 off</p>\n\n");
	}


	if (strstr(data, "control3"))
	{
				gpio_set_value(161, 1);
				printf("<p>LED3 on</p>\n\n");
	}
	else if(strstr(data, "control3=third&frequency=&onoff=off"))
	{
		gpio_set_value(161, 0);
		printf("<p>LED3 off</p>\n\n");
	}

	if (strstr(data, "control4"))
	{
		gpio_set_value(160, 1);
		printf("<p>LED4 on</p>\n\n");
	}
	else if(strstr(data, "control4=fourth&frequency=&onoff=off"))
	{
		gpio_set_value(160, 0);
		printf("<p>LED4 off</p>\n\n");
	}
	
	
	if (strstr(data, "frequency"))
	{
		if (sscanf(data, "login=name&logincontent=%[a-zA-A0-9]&frequency=%[0-9]&onoff=on&S=Submit", &myContent))
		{
			shine(myContent[0] - '0');
			printf("<p>Shine mode!!!!: \n\nfrequency is %s</p>", myContent);
		}
		else if (sscanf(data, "login=studentID&logincontent=%[a-zA-A0-9]&frequency=%[0-9]&onoff=on&S=Submit", &myContent))
		{
			shine(myContent[0] - '0');
			printf("<p>Shine mode!!!!: \n\nfrequency is %s</p>", myContent);		
		}
	}
	
	return 0;

}
