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

                dup2(fd,1);
                dup2(fd,2);
                printf("Prueba de escritura con saldida por pantalla.");
                perror("Prueba de escritura de errores");

                return 0;
        }
        else {
                perror("Se necesita pasar el nombre de un fichero como argumento.\n");
                return -1;
        }
}

/*
  ls > dirlist 2>&1 es diferente a ls 2>&1 > dirlist porque  en el primer caso se redirige la salida estandar al fichero y luego se redirige la salida de error al fichero, que es donde
  apunta la salida estandar; mientras que en el segundo caso la salida de error estandar se redirige a la salida estandar y luego esa salida al fichero por lo que en ese caso la salida de
  error no apunta al fichero. 
*/
