// CPE 2600
// John Williams

// finfo.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("File type: Regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("File type: Directory\n");
    } else if (S_ISCHR(mode)) {
        printf("File type: Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("File type: Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("File type: FIFO/pipe\n");
    } else if (S_ISLNK(mode)) {
        printf("File type: Symbolic link\n");
    } else if (S_ISSOCK(mode)) {
        printf("File type: Socket\n");
    } else {
        printf("File type: Unknown\n");
    }
}

void print_permissions(mode_t mode) {
    printf("Permissions: ");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat file_stat;
    if (stat(argv[1], &file_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // Print file type
    print_file_type(file_stat.st_mode);

    // Print permissions
    print_permissions(file_stat.st_mode);

    // Print owner (UID)
    struct passwd *pw = getpwuid(file_stat.st_uid);
    if (pw != NULL) {
        printf("Owner: %s (UID: %d)\n", pw->pw_name, file_stat.st_uid);
    } else {
        printf("Owner UID: %d\n", file_stat.st_uid);
    }

    // Print size of the file in bytes
    printf("Size: %ld bytes\n", file_stat.st_size);

    // Print last modification date and time
    char time_str[100];
    struct tm *time_info = localtime(&file_stat.st_mtime);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("Last modification: %s\n", time_str);

    return 0;
}