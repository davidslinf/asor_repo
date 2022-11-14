#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {

        if(argc == 2) {
                int fd = open(argv[1], O_RDWR | O_CREAT, 0664);

                if(fd == -1){
                        perror("No se ha podido ejecutar open() correctamente\n");
                        return -1;
                }

                printf("Prueba de escritura con saldida por pantalla.");
                dup2(fd,1);
                printf("Prueba de escritura con saldida por fichero.");


                return 0;
        }

        else {
                perror("Se necesita pasar el nombre de un fichero como argumento.\n");
                return -1;
        }
}
