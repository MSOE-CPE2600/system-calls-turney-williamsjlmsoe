// CPE 2600
// John Williams

// info.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>

int main() {
    struct utsname system_info;  // Renamed to avoid conflict
    struct sysinfo meminfo;

    if (uname(&system_info) == 0) {
        printf("Operating system name: %s\n", system_info.sysname);
        printf("Operating system release: %s\n", system_info.release);
        printf("Operating system version: %s\n", system_info.version);
        printf("Hardware type: %s\n", system_info.machine);
    } else {
        perror("uname");
        exit(EXIT_FAILURE);
    }

    if (sysinfo(&meminfo) == 0) {
        printf("Total physical memory (in bytes): %ld\n", meminfo.totalram * meminfo.mem_unit);
        printf("Total free memory (in bytes): %ld\n", meminfo.freeram * meminfo.mem_unit);
    } else {
        perror("sysinfo");
        exit(EXIT_FAILURE);
    }

    return 0;
}