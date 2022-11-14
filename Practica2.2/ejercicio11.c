#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {

        if(argc == 2){
                struct stat buf;
                stat(argv[1], &buf);
                if(buf.st_mode == "S_ISREG"){
                        const char *Nombre = argv[1];
                        const char *TermRig = ".hard";
                        const char *TermSim = ".sym";

                        char *NombreRig = malloc(strlen(Nombre) + strlen(TermRig) +1);
                        char *NombreSim = malloc(strlen(Nombre) + strlen(TermSim) +1);

                        strcat(strcpy(NombreRig, Nombre),TermRig);
                        strcat(strcpy(NombreSim, Nombre),TermSim);

                        link(Nombre, NombreRig);
                        symlink(Nombre, NombreSim);

                        free(NombreRig);
                        free(NombreSim);
                }
                else{
                        perror("No es un fichero regular\n");
                        return -1;
                }


        }

        else {
                perror("Falta el nombre del fichero\n");

                return -1;
        }


        return 0;
}
