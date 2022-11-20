/*      El mensaje de finalizacion solo se mostrara en la version con system() ya que con execvp() se esta sustituyendo la imagen del proceso original por
        la del comando que se está realizando.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){

        if(argc == 1) {
                perror("Se necesita de un argumento\n");
                return -1;
        }

        if(execvp(argv[1],argv +1) == -1) {
                perror("Error en execvp()\n");
                return -1;
        }
        printf("Comando execvp() ejecutado correctamente\n");
/*
        if(system(argv[1]) == -1) {
                perror("Error en system()\n");
                return -1;
        }
        printf("Comando system() ejecutado correctamente\n");
*/
        return 0;
}






