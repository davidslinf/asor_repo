#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(int argv, char **argc){
    
        long int max_link=pathconf("./NUEVO",_PC_LINK_MAX);
        long int name_max=pathconf("./NUEVO",_PC_NAME_MAX);
        long int path_max=pathconf("./NUEVO",_PC_PATH_MAX);

        printf("Numero maximo de enlaces:%li\n",max_link);
        printf("tama�o maximo de nombre:%li\n",name_max);
        printf("Tama�o maximo de ruta:%li\n",path_max);

        return 0;
}
