#include <stdio.h>
#include <string.h>
#include <sys/typres.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>

int main(int argv, char** args) {
        char buffer[257];
        int aux,fd,fd2,r_size,cambios=0;
        fd_set set;

        if((fd = open("tuberia", O_RDONLY |  O_NONBLOCK)) == -1){
                perror("Error al abrir la tuberia\n");
                return -1;
        }
        if((fd2 = open("tuberia2", O_RDONLY |  O_NONBLOCK)) == -1){
                perror("Error al usar open()\n");
                close(fd2);
                return -1;
         }

        while(cambios != -1) {
                FD_ZERO(&set);
                FD_SET(fd, &set);
                FD_SET(fd2, &set);

                if(fd > fd2) aux = fd + 1;
                else aux = fd2 + 1;

                cambios = select(aux, &set, NULL, NULL, NULL);
                if(cambios == -1) {
                        perror("Error al usar select()\n");
                        return -1;
                }
                else if (cambios > 0) {
                        if(FD_ISSET(fd, &set)) {
                                r_size = read(fd, buffer, sizeof(buffer)-1);
                                buffer[r_size] = '\0';
                                printf("Tuberia: tuberia, Mensaje: %s", buffer);
                                close(fd);
                                fd = open("tuberia", O_RDONLY |  O_NONBLOCK);
                        }
                        else if(FD_ISSET(fd2, &set)) {
                                r_size = read(fd2, buffer, sizeof(buffer)-1);
                                buffer[r_size] = '\0';
                                printf("Tuberia: tuberia2, Mensaje: %s", buffer);
                                close(fd2);
                                fd2 = open("tuberia2", O_RDONLY |  O_NONBLOCK);
                        }
                }
        }

        close(fd);
		close(fd2);

        return 0;
}


