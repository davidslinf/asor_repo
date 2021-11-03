#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<pwd.h>
#include<errno.h>

int main(int argv, char **argc){

    uid_t uidReal = getuid();
    uid_t uidEfectivo = geteuid();
    
    printf("UID REAL %i\n",uidReal);
    printf("UID EFECTIVO %i\n",uidEfectivo);
    
    struct passwd *pw=getpwuid(uidReal);
    
    if(pw==0){
        perror( "Error en getpwid");
        printf("Error",strerror(errno));
        return -1;
    }
    printf("NAME %s\n",pw->pw_name);
    printf("HOME %s\n",pw->pw_dir);
    printf("SHELL %s\n",pw->pw_shell);

    return 0;
}
