#include<stdio.h>
#include<string.h>
#include<time.h>
#include<errno.h>

int main(int argv, char **argc){

        time_t t = time(NULL);

        if(t==-1){
                perror("Error en time");
                return -1;
        }

        printf("Principio de los tiempos %li\n",t);

        return 0;
}
