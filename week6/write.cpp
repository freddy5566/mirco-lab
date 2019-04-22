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

    string isOn = value == 1 ? "on" : "close";

    switch (gpio) {
    case 166:
        cout << "LED1 " + isOn << endl;
        break;
    case 164:
        cout << "LED2 " + isOn<< endl;
        break;
    case 162:
        cout << "LED3 " + isOn << endl;
        break;
    case 160:
        cout << "LED4 " + isOn << endl;
        break;
    default:
        break;
    }

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

    char buf[1024] = "Data Input 12345";
    //
    FILE *fp = fopen("/dev/demo", "w+");
    if (fp == NULL)
    {
        printf("can't open device\n");
        return 0;
    }
    fwrite(buf, sizeof(buf), 1, fp);
    fclose(fp);


    if (commend.compare("Mode_Shine")) {
        int gpio = Leds[argv[1]];
        string action = string(argv[2]);

        gpio_export(gpio);
        gpio_set_dir(gpio, "out");

        int value = !action.compare("on") ? 1 : 0;

        cout << "gpio = " << gpio << endl;
        cout << "argv[2] = " << argv[2] << endl;
        cout << "value = " << value << endl;
        cout << "gpio = " << gpio << endl;

        gpio_set_value(gpio, value);

    } else {
        cout << "Mode_Shine start..." << endl;
        setup_gpio();

        int times = atoi(argv[2]);
        cout << "times = " << times << endl;
        shine(times);
    }

    return 0;

}
