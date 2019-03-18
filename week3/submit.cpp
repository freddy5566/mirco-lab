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

	cout << "Content-type: text/html\n\n" << endl;
	cout << "<html><head><title>test</title></head>\n" << endl;
	
	data = getenv(""QUERY_STRING);

	char myContent[128];

	if (strstr(data, "studentID"))
	{
		sscanf(data, "login=studentID&Text=%[a-zA-A0-9]&S=Submit", &myContent);
		cout << "<p>選項: 學號</p>" << endl;
		cout << "<p>內容: " << myContent << "</p>" << endl;
	}
	else if (strstr(data, "name"))
	{
		sscanf(data, "login=name&Text=%[a-zA-A0-9]&S=Submit", &myContent);
		cout << "<p>選項: 姓名</p>" << endl;
		cout << "<p>內容: " << myContent << "</p>" << endl;
	}
	else
	{
		cout << "error" << endl;
	}

	return 0;

}
