#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define SLEEP_SECS 5

int main(int argc, char **argv){

        sigset_t InstBloquear;
        sigset_t InstRecibir;

        sigemptyset(&InstBloquear);
        sigemptyset(&InstRecibir);

        sigaddset(&InstBloquear, SIGINT);
        sigaddset(&InstBloquear, SIGTSTP);

        sigprocmask(SIG_BLOCK, &InstBloquear, 0);

        sleep(SLEEP_SECS);
         sigpending(&InstRecibir);

        if(sigismember(&InstRecibir, SIGINT)){
                printf("Señal SIGINT recibida\n");
        }
        if(sigismember(&InstRecibir, SIGTSTP)){
                printf("Señal SIGTSTP recibida\n");
                sigprocmask(SIG_UNBLOCK, &InstBloquear, 0);
        }
        printf("No se recibio ninguna señal\n");

        return 0;
}

