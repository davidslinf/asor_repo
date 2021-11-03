#include<stdio.h>
#include<string.h>
#include<time.h>
#include<errno.h>
#include<sys/time.h>

int main(int argv, char **argc){

        time_t t =time(NULL);
 
        struct tm *local=localtime(&t);

        int anio = local->tm_year;
        printf("El año es %i\n",1900+anio);


        return 0;
}
