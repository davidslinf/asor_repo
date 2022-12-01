#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv){

        int p_h[2];
        int h_p[2];

        if(pipe(h_p) == -1 || pipe(p_h) == -1){
                perror("Error en el pipe\n");
                return 0;
        }

        pid_t pid = fork();

        if(pid == -1){  //Error
                perror("Error en el fork\n");
                return -1;
        }
if(pid == 0){   //Hijo
                close(p_h[1]);
                close(h_p[0]);

                char mensRecibido[512];
                int longMensaje = 0;
                int i = 0;

                while(i < 10){

                        longMensaje = read(p_h[0], mensRecibido, 511);
                        mensRecibido[longMensaje] = '\0';
                        write(1, mensRecibido, longMensaje);

                        sleep(1);
                        if(i < 9)
                                write(h_p[1], "l", 2);
                        else
                                write(h_p[1], "q", 2);
                        i++;
                }

                close(p_h[0]);
                close(h_p[1]);

        }
	else{   //Padre
                close(p_h[0]);
                close(h_p[1]);

                char mensaje[512];
                int longMensaje;
                char mensRecibido[2];

                while(strcmp(mensRecibido, "q") != 0){

                        longMensaje = read(0, mensaje, 511);
                        mensaje[512] = '\0';

                        write(p_h[1], mensaje, longMensaje);

                        read(h_p[0], mensRecibido, 2);
                        printf("[PADRE]Se ha recibido el caracter %s del hijo\n", mensRecibido);

                }
                close(p_h[1]);
                close(h_p[0]);

                int status;
                waitpid(pid, &status, 0);
        }
	 return 0;
}


