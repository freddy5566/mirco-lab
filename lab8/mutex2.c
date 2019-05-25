#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

pthread_mutex_t mutex;	
char *gpio_num;

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

int gpio_set_dir(unsigned int gpio, char* dirStatus){
	int fd;
	char buf[64];

	snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);
	fd = open(buf, O_WRONLY);
	if (fd<0){
		perror("gpio/direction");
		return fd;
	}
	
	if (!strcmp(dirStatus, "out")){
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






void * shine(int num)
{

	printf("num: %d\n", num);

		pthread_mutex_lock(&mutex);
		if (gpio_num[num]=='0'){gpio_num[num]='1';}
		else if (gpio_num[num]=='1') {gpio_num[num]='0';}
		gpio_set_value(166-num*2, gpio_num[num]-'0');

		pthread_mutex_unlock(&mutex);
		pthread_exit(NULL);
}



int main(int argc, char *argv[]) {
	// gpio id  & shine times
	pthread_t thread1, thread2, thread3, thread4;
	gpio_num = argv[1];
	char times = *argv[2];

	int i;
   	setup_gpio();
	pthread_mutex_init(&mutex, 0);
	printf("times: %d\n", times-'0');
	for (i =0; i <= times-'0'; i++ ){


		pthread_create(&thread1, NULL, shine, 0);
		pthread_create(&thread2, NULL, shine, 1);
		pthread_create(&thread3, NULL, shine, 2);
		pthread_create(&thread4, NULL, shine, 3);


		pthread_join(thread1,0);
		pthread_join(thread2,0);
		pthread_join(thread3,0);
		pthread_join(thread4,0);
		sleep(1);

		printf("gpio num: %s\n", gpio_num);	


	}
	

	
	pthread_mutex_destroy(&mutex);
	return 0;
	
}
