#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define SLEEP_SECS 5

int main (int argc, char** argv) {

        sigset_t InstrBloqueadas;
        sigset_t Conjunto;

        sigaddset(&InstrBloqueadas, SIGINT);
        sigaddset(&InstrBloqueadas, SIGTSTP);
        sigprocmask(SIG_BLOCK, &InstrBloqueadas, NULL);

        sleep(SLEEP_SECS);

        sigpending(&Conjunto);

        if(sigismember(&Conjunto, SIGINT))
                printf("Señal SIGINT recibida\n");
        else
                printf("No se ha recibido la señal SIGINT\n");

        if(sigismember(&Conjunto, SIGTSTP)) {
                printf("Señal SIGTSTP recibida\n");
                sigprocmask(SIG_UNBLOCK, &InstrBloqueadas, NULL);
        }
        else
                printf("No se ha recibido la señal SIGINT\n");


        printf("El programa se ha reanudado\n");

        return 0;
