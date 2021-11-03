#include<stdio.h>
#include<string.h>
#include<time.h>
#include<errno.h>
#include<sys/time.h>

int main(int argv, char **argc){

        time_t t = time(NULL);
        struct tm *ti=localtime(&t);
        printf("Años:%i\n",1900+ti->tm_year);
        char buff[100];
        strftime(buff,100,"%A,%d %B %Y,%H:%M",ti);
        printf("Hoy es: %s\n",buff);

        return 0;
}
