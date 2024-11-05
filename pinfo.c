// CPE 2600
// John Williams

// pinfo.c

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <unistd.h>
#include <errno.h>

void print_scheduler(int scheduler) {
    switch (scheduler) {
        case SCHED_OTHER:
            printf("Scheduling method: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Scheduling method: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Scheduling method: SCHED_RR\n");
            break;
        case SCHED_BATCH:
            printf("Scheduling method: SCHED_BATCH\n");
            break;
        case SCHED_IDLE:
            printf("Scheduling method: SCHED_IDLE\n");
            break;
        case SCHED_DEADLINE:
            printf("Scheduling method: SCHED_DEADLINE\n");
            break;
        default:
            printf("Unknown scheduling method\n");
    }
}

int main(int argc, char *argv[]) {
    pid_t pid = (argc > 1) ? atoi(argv[1]) : getpid(); // Use current PID if no argument is provided

    // Check if the PID is valid
    if (pid <= 0) {
        fprintf(stderr, "Invalid PID provided\n");
        exit(EXIT_FAILURE);
    }

    // Get and print process priority
    int priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0) {
        perror("getpriority");
        exit(EXIT_FAILURE);
    } else {
        printf("Process priority: %d\n", priority);
    }

    // Get and print scheduling method
    int scheduler = sched_getscheduler(pid);
    if (scheduler == -1) {
        perror("sched_getscheduler");
        exit(EXIT_FAILURE);
    } else {
        print_scheduler(scheduler);
    }

    return 0;
}