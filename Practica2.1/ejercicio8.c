#include <sys/types.h>
#include<errno.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdio.h>

int main(int argv, char **argc){
	
	uid_t uidReal = getuid();
    uid_t uidEfectivo = geteuid();
    
    printf("UID REAL %i\n",uidReal);
    printf("UID EFECTIVO %i\n",uidEfectivo);
    
    return 0;
}
