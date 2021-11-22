#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>

int main (int argc, char** argv) {

        int PlanificacionNum = sched_getscheduler(0);

        int Prioridad = getpriority(PRIO_PROCESS, 0);

        char*  Planificacion = "SCHED_RR";

        if(PlanificacionNum == 0)
                Planificacion = "SCHED_OTHER";
        else if(PlanificacionNum >=  1 && PlanificacionNum <= 99)
                Planificacion = "SCHED_FIFO";


        int PrioridadMax = sched_get_priority_max(PlanificacionNum);
        int PrioridadMin = sched_get_priority_min(PlanificacionNum);

        printf("Politica de planificacion: %s, Prioridad: %i,\n", Planificacion, Prioridad);
        printf("Prioridad minima: %i, Prioridad maxima: %i,\n", PrioridadMin, PrioridadMax);


        return 0;
}
