#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

sem_t semaphore;
int counter = 0;

int gpio_export(unsigned int gpio)
{
  int fd, len;
  char buf[64];

  fd = open("/sys/class/gpio/export", O_WRONLY);
  if (fd < 0)
  {
    perror("gpio/export");
    return fd;
  }
  len = snprintf(buf, sizeof(buf), "%d", gpio);
  write(fd, buf, len);
  close(fd); //close file

  return 0;
}

int gpio_unwxport(unsigned int gpio)
{
  int fd, len;
  char buf[64];

  fd = open("/sys/class/gpio/export", O_WRONLY);
  if (fd < 0)
  {
    perror("gpio/export");
    return fd;
  }
  len = snprintf(buf, sizeof(buf), "%d", gpio);
  write(fd, buf, len);
  close(fd); //close file

  return 0;
}

int gpio_set_dir(unsigned int gpio, char *dirStatus)
{
  int fd;
  char buf[64];

  snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);
  fd = open(buf, O_WRONLY);
  if (fd < 0)
  {
    perror("gpio/direction");
    return fd;
  }

  if (!strcmp(dirStatus, "out"))
  {
    write(fd, "out", 4);
  }
  else
    write(fd, "in", 3);

  close(fd);
  return 0;
}

int gpio_set_value(unsigned int gpio, int value)
{
  int fd;
  char buf[64];

  snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);
  fd = open(buf, O_WRONLY);

  if (fd < 0)
  {
    perror("gpio/direction");
    return fd;
  }

  if (value == 0)
  {
    write(fd, "0", 2);
  }
  else
    write(fd, "1", 2);

  close(fd);
  return 0;
}

void setup_gpio()
{
  gpio_export(166);
  gpio_export(164);
  gpio_export(162);
  gpio_export(160);
  gpio_set_dir(166, "out");
  gpio_set_dir(164, "out");
  gpio_set_dir(162, "out");
  gpio_set_dir(160, "out");
}

void *child(void *inputArray)
{
  char **inputString = (char **)inputArray;

  char *inputGPIO = inputString[0];
  char *inputValue = inputString[1];
 
	while (1)
  {
    counter++;
    sem_wait(&semaphore);
    printf("gpio %s value %s\n", inputGPIO, inputValue);
		gpio_set_value(atoi(inputGPIO), atoi(inputValue));
    sleep(1);
  }
}

int main(int argc, char *argv[])
{

  char *state = argv[1];
  char *times = argv[2];

  char *input_166[] = {"166", "0"};
  char *input_164[] = {"164", "0"};
  char *input_162[] = {"162", "0"};
  char *input_160[] = {"160", "0"};

  setup_gpio();

	printf("input_166 %s\n", input_166[0]);

  sem_init(&semaphore, 0, 0);

  pthread_t t1;
  pthread_t t2;
  pthread_t t3;
  pthread_t t4;

  pthread_create(&t1, NULL, child, input_166);
  pthread_create(&t2, NULL, child, input_164);
  pthread_create(&t3, NULL, child, input_162);
  pthread_create(&t4, NULL, child, input_160);

  int i = 0;
  for (i = 1; i < times[0] - '0' + 1; i++)
  {
    printf("times %d\n", times[0] - '0');
    printf("excute.....\n");
    int isNeg = i % 2 == 0 ? 0 : 1;

    char value_1 = isNeg ? !(state[0] - '0') + '0' : state[0];
    char value_2 = isNeg ? !(state[1] - '0') + '0' : state[1];
    char value_3 = isNeg ? !(state[2] - '0') + '0' : state[2];
    char value_4 = isNeg ? !(state[3] - '0') + '0' : state[3];
		
		char value_1_string[] = "0";
		char value_2_string[] = "0";
		char value_3_string[] = "0";
		char value_4_string[] = "0";
	
		value_1_string[0] = value_1;
		value_2_string[0] = value_2;
		value_3_string[0] = value_3;
		value_4_string[0] = value_4;

    input_166[1] = value_1_string;
    input_164[1] = value_2_string;
    input_162[1] = value_3_string;
    input_160[1] = value_4_string;

		printf("166 %s\n", input_166[1]);
		printf("164 %s\n", input_164[1]);
		printf("162 %s\n", input_162[1]);
		printf("160 %s\n", input_160[1]);

    sem_post(&semaphore);
    sem_post(&semaphore);
    sem_post(&semaphore);
    sem_post(&semaphore);

    sleep(1);
  }

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);

  return 0;
}
