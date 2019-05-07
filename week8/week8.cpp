#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <map>
#include <limits.h>
#include <sys/wait.h>


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


	int fd[2];
	char buf[PIPE_BUF];
	int pid, len;

    while(1)
    {
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
               setup_gpio();
               buf[len] = '\0';
               printf("Read %d bytes \n", len);
               printf("content: %s \n", buf);


               gpio_set_value(166, buf[0] - '0');
               gpio_set_value(164, buf[1] - '0');
               gpio_set_value(162, buf[2] - '0');
               gpio_set_value(160, buf[3] - '0');

               cout << "buf0 " << buf[0] << endl;\
               cout << "buf1 " << buf[1] << endl;
               cout << "buf2 " << buf[2] << endl;
               cout << "buf3 " << buf[3] << endl;
               /**
               cout << fd[0] << " " << buf << " " << PIPE_BUF<<endl;
    **/
    }

           close(fd[0]);

       }



         if (pid > 0)
          {


              close(fd[0]);

           //    cout << "input start...." << endl;
               char writeBuf[] = "Hello pipe!";
                 cout << "please enter LED state: " ;
                 cin >> writeBuf;

                 write(fd[1], writeBuf, strlen(writeBuf));
                 close(fd[1]);

           }
        waitpid(pid, NULL, 0);
        }






    return 0;

 
}

