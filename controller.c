#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int main() 
{
    struct input_event ev;
    int fd;

    // Open the input device (replace 'eventX' with the correct event number)
    fd = open("/dev/input/event18", O_RDWR);
    if (fd < 0) {
        perror("Failed to open device");
        return EXIT_FAILURE;
    }

    while (1) {
        // Read input events
        ssize_t bytes = read(fd, &ev, sizeof(struct input_event));
        if (bytes < (ssize_t)sizeof(struct input_event)) {
            perror("Read failed");
            close(fd);
            return EXIT_FAILURE;
        }
        // Process events
        if (ev.type == EV_KEY) {
            printf("Key %i %s\n", ev.code, ev.value ? "pressed" : "released");
        } else if (ev.type == EV_ABS) {
            printf("Absolute %i: %i\n", ev.code, ev.value);
        }
        usleep(10000); // Sleep for 10 ms to reduce CPU usage
    }

    close(fd);
    return EXIT_SUCCESS;
}

