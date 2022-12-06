#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

int main(int argc, char **argv){

        int fd1, fd2;
        char buffer[256];
        int tamMensaje;
        int cambios;
        fd_set set;
        int aux;
	
	if((fd1 = open("./tuberia1", O_RDONLY | O_NONBLOCK)) == -1){
                perror("Error en la primera tuberia\n");
                return -1;
        }

        if((fd2 = open("./tuberia2", O_RDONLY | O_NONBLOCK)) == -1){
                perror("Error en la segunda tuberia\n");
                return -1;
        }

        printf("Tuberias creadas\n");

	 while(1){

                printf("Entro al while\n");;

                FD_ZERO(&set);
                FD_SET(fd1, &set);
                FD_SET(fd2, &set);
        //      FD_SET(0, &set);

                if(fd1 < fd2) aux = fd2 + 1;
                else aux = fd1 + 1;

                printf("fd1: %i fd2: %i aux: %i\n", fd1, fd2, aux);

                cambios = select(aux, &set, 0, 0, 0);

                if(cambios == -1){
                        perror("Error en el select\n");
                        return -1;
                }
                else if(cambios > 0){
                        printf("Cambios es: %i\n", cambios);
			
			 if(FD_ISSET(fd1, &set)){
                                printf("Tuberia1 elegida\n");
                                tamMensaje = read(fd1, buffer, sizeof(buffer) -1);

                                if(tamMensaje == 0){
                                        close(fd1);
                                        fd1 = open("./tuberia1", O_RDONLY | O_NONBLOC$

                                }
                                buffer[tamMensaje] = '\0';
                                printf("TUBERIA 1: %s\n", buffer);

                        }
			else if(FD_ISSET(fd2, &set)){
                                printf("Tuberia2 elegida\n");
                                tamMensaje = read(fd2, buffer, sizeof(buffer) -1);

                                if(tamMensaje == 0){
                                        close(fd2);
                                        fd1 = open("./tuberia2", O_RDONLY | O_NONBLOC$

                                }
                                buffer[tamMensaje] = '\0';
                                printf("TUBERIA 2: %s\n", buffer);
                        }
                }
        }

        close(fd1);
        close(fd2);

        return 0;
}

