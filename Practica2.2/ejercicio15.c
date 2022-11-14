#include <stdio.h>
include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

//Suponemos que el fichero se pasa por parametro
int main(int argc, char * argv[]) {

        if(argc == 2) {
                int fd = open(argv[1], O_RDWR | O_CREAT , 0645);
                if (fd == -1) {
                        perror("Fallo al abrir el fichero \n");
                        return -1;
                }
				
		//Comprobamos el estado del cerrojo
                int locked = lockf(fd, F_TEST, 0);
                if(locked != -1){
                        //Bloqueamos el cerrojo
                        lockf(fd, F_LOCK, 0);
                        //Escribimos la hora actual
                        const time_t currTime = time(NULL);
                        const  struct tm *currDate = localtime(&currTime);
                        char * s = malloc(6);
                        const char * format = "%H:%M"; 
                        strftime(s, 6, format, currDate); 
                        printf("%s\n", s);
                        free(s);
                        //Suspendemos la ejecucion durante 30 segundos
                        sleep(3);
                        close(fd);
                        //Liberamos el cerrojo
                        lockf(fd, F_ULOCK, 0);
                }
                else {
                        perror("El lock ya esta bloqueado\n");
                        return -1;
                }
        }
        else {
                perror("Introduce una ruta de fichero\n");
                return -1;
        }
        return 0;
}



