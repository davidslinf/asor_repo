#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char** argv) {

        int h_p[2];
        int p_h[2];

        if(pipe(h_p) == -1 || pipe(p_h) == 1) {
                perror("Error en el pipe\n");
                return -1;
        }

        pid_t pid = fork();

        if(pid == -1) { //Error
                perror("Error en el fork()\n");
                return -1;
        }
        else if(pid == 0) { //Hijo
                close(h_p[0]);
                close(h_p[1]);

                char mensRecibido[512];
                int longMensaje = 0;

                while(i < 10) {
                        longMensaje = read(p_h[0],mensRecibido, 512);
                        mensaRecibido[longMensaje] = '\0';
                        write(1,mensajeRecibido, longMensaje);

                        sleep(1);
						if(i < 9) write(h_p[1], "l", 2);
                        else write(h_p[1], "q", 2);
                        i++;
                }
                close(h_p[1]);
                close(p_h[0]);
        }
        else { //Padre
                close(h_p[1]);
                close(p_h[0]);

                char mensaje[512];
                int longMensaje;
                char mensRecibido[2];

                while(strcmp(mensRecibido, "q") != 0) {
                        longMensaje = read(0, mensaje, 512);
                        mensaje[longMensaje] = '\0';
						 write(p_h[1], mensaje, longMensaje);

                        read(h_p[0], mensRecibido, sizeof(mensRecibido));
                        printf("Se ha recibido el caracter %s del hijo\n", mensRecibido);
                }
                wait(NULL);
                close(h_p[0]);
                close(p_h[1]);
                printf("El padre ha acabado\n");
        }

        return 0;
}

