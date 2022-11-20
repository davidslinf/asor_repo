#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv){

        if(argc == 1){
                perror("Se necesitan argumentos\n");
                return -1;
        }

        pid_t pid = fork();
 	if(pid == -1){  //Error
                perror("Error en el fork\n");
                return -1;
        }
        if(pid == 0){   //Hijo
                if(setsid() == -1){
                        perror("Error al crear nueva sesion\n");
                        return -1;
                }

                if(chdir("/tmp") == -1){
                        perror("Error al cambiar de directorio\n");
                        return -1;
                }

                int fd1 = open("/tmp/daemon.out", O_RDWR | O_CREAT, 0644);
                int fd2 = open("/tmp/daemon.err", O_RDWR | O_CREAT, 0644);
                int fd3 = open("/dev/null", O_RDWR | O_CREAT, 0644);
		
		if(fd1 == -1 || fd2 == -1 || fd3 == -1){
                        perror("Error en el open\n");
                        return -1;
                }

                dup2(fd1,1);    //Salida
                dup2(fd2,2);    //Salida error
                dup2(fd3,0);    //Entrada

                if(execvp(argv[1], argv+1) == -1){
                        perror("Error en execvp\n");
                        return -1;
                }
        }
	 else{   //Padre
                sleep(30);
                int status;
                waitpid(pid, &status, 0);
                printf("Se acabo el zombie\n");
        }
        return 0;
}

