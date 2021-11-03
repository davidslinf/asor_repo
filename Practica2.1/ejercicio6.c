#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char **argv) {

        printf("Longitud max de los argumentos:%li\n",sysconf(_SC_ARG_MAX));
        printf("Numero max de hijos:%li\n",sysconf(_SC_CHILD_MAX));
        printf("Numero max de ficheros:%li\n",sysconf(_SC_OPEN_MAX));

        return 0;
}

