#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {

        if(argc == 2) {

                const char * Nombre =  argv[1];
                const char * TerminacionRig = ".hard";
                const char * TerminacionSim = ".sym";

                char * NombreRigido = malloc(strlen(Nombre) + strlen(TerminacionRig) +1);
                char * NombreSimbolico = malloc(strlen(Nombre) + strlen(TerminacionSim) +1);

                strcat(strcpy(NombreRigido, Nombre), TerminacionRig);
                strcat(strcpy(NombreSimbolico, Nombre), TerminacionSim);

                link(Nombre, NombreRigido);
                symlink(Nombre, NombreSimbolico);

                free(NombreRigido);
                free(NombreSimbolico);

        }

        else {
                perror("Falta el nombre del fichero\n");

                return -1;
        }


        return 0;
}
