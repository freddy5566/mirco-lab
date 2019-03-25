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

int main() {
	map<string, int> Leds;
	Leds["LED1"] = 166;
	Leds["LED2"] = 164;
	Leds["LED3"] = 162;
	Leds["LED4"] = 160;

	
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
	else if (strstr(data, "control1"))
	{
				sscanf(data, "controlLED=first&S=Submit", &myContent);
				
				gpio_set_value(166, 1);
				printf("<p>LED1 on</p>\n\n");
	}
		else if (strstr(data, "control2"))
	{
				sscanf(data, "controlLED=second&S=Submit", &myContent);
				
				gpio_set_value(164, 1);
				printf("<p>LED2 on</p>\n\n");
	}
		else if (strstr(data, "control3"))
	{
				sscanf(data, "controlLED=third&S=Submit", &myContent);
				
				gpio_set_value(162, 1);
				printf("<p>LED3 on</p>\n\n");
	}
		else if (strstr(data, "control4"))
	{
				sscanf(data, "controlLED=fourth&S=Submit", &myContent);
				
				gpio_set_value(160, 1);
				printf("<p>LED4 on</p>\n\n");
	}
	else if (strstr(data, "frequency"))
	{
			sscanf(data, "frequency=%[0-9]&onoff=on&S=Submit", &myContent);
			shine(myContent[0] - '0');
			printf("<p>Shine mode: frequency is %s</p>", &myContent);
	}
	else
	{
		cout << "error" << endl;
	}


	return 0;

}
