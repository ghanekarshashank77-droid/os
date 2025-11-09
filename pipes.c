#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2]; // fd[0] - read end, fd[1] - write end
    pid_t pid;
    char write_msg[100];
    char read_msg[100];

    if (pipe(fd) == -1) {
        printf("Pipe failed\n");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid > 0) {
        // Parent process - write to pipe
        close(fd[0]); // Close read end

        printf("Enter a message: ");
        fgets(write_msg, sizeof(write_msg), stdin);

        // Remove newline character from fgets
        write_msg[strcspn(write_msg, "\n")] = '\0';

        write(fd[1], write_msg, strlen(write_msg) + 1); // +1 for null terminator
        close(fd[1]); // Close write end after writing
    } else {
        // Child process - read from pipe
        close(fd[1]); // Close write end

        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received message: %s\n", read_msg);

        close(fd[0]); // Close read end after reading
    }

    return 0;
}

