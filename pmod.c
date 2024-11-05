// CPE 2600
// John Williams

// pmod.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <time.h>

int main() {
    // Modify process priority (reduce by 10)
    if (setpriority(PRIO_PROCESS, 0, 10) == -1) {
        perror("setpriority");
        exit(EXIT_FAILURE);
    }
    printf("Priority reduced by 10.\n");

    // Sleep for 1,837,272,638 nanoseconds
    struct timespec sleep_time;
    sleep_time.tv_sec = 1;  // 1 second
    sleep_time.tv_nsec = 837272638L;  // 837,272,638 nanoseconds

    if (nanosleep(&sleep_time, NULL) == -1) {
        perror("nanosleep");
        exit(EXIT_FAILURE);
    }

    // Print goodbye message
    printf("Goodbye!\n");

    return 0;
}