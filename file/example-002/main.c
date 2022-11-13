#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char* path = "/tmp/example1.tmp";
    int fd = open(path, O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("Open file failed\n");
    }

    int pid = fork();
    if (pid > 0) {
        printf("In main process\n");

        char buf[] = "Hello!\n";
        int ret = write(fd, buf, sizeof(buf));
        if (ret < 0) {
            perror("Write file failed\n");
        }

        sleep(2);

        printf("Exit main process\n");
    } else if (pid == 0) {
        printf("In child process\n");
        sleep(1);

        char buf[100] = "\0";

        lseek(fd, 0, SEEK_SET);
        int ret = read(fd, buf, sizeof(buf));
        if (ret <= 0) {
            perror("Read failed\n");
        } else {
            printf("%s", buf);
        }

        printf("Exit child process\n");
    } else {
        perror("Fork failed\n");
    }

    close(fd);
    
    return 0;
}