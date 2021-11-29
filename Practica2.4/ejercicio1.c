#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv) {

        int fd[2];
        if(pipe(fd) == -1) {
                perror("Error en el pipe\n");
                return -1;
        }

        pid_t pid = fork();
        if(pid == -1) { //Error
                perror("Error en el fork()\n");
                return -1;
        }
        else if(pid == 0) { //Hijo
                dup2(fd[0],0);
                close(fd[0]);
                close(fd[1]);
                execlp(argv[3],argv[3],argv[4], NULL);
        }
        else { //Padre
                dup2(fd[1],1);
                close(fd[0]);
                close(fd[1]);
                execlp(argv[1],argv[1],argv[2],NULL);
        }

        return 0;
}
