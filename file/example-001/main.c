#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static int loop_write(int fd, char* name) {
    if (fd < 0) {
        perror("fd is incorrect\n");
        return -1;
    }

    if (name == NULL) {
        perror("name is empty\n");
        return -1;
    }

    printf("In %s process\n", name);

    const int loop = 10;
    int len = strlen(name);
    for (int i = 0; i < loop; i++) {
        int ret = write(fd, name, len);
        if (ret < 0) {
            perror("Write file failed\n");
            return -1;
        } else if (ret != len) {
            printf("Need to re-write\n");
            /* TODO */
        } else {
            printf("%s write %d bytes\n", name, ret);
        }
    }

    printf("Exit %s process\n", name);

    return 0;
}

int main() {
    char* path = "/tmp/example1.tmp";
    int fd = open(path, O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("Open file failed\n");
        return -1;
    }

    int pid = fork();
    if (pid > 0) {
        loop_write(fd, "main");
    } else if (pid == 0) {
        loop_write(fd, "child");
    } else {
        perror("Fork failed\n");
        return -1;
    }

    printf("all here\n");
    close(fd);

    return 0;
}