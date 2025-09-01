#include <stdio.h>
#include <unistd.h>

int main() {
    char *name = ttyname(0); // check stdin (fd = 0)

    if (name != NULL) {
        printf("stdin is connected to terminal: %s\n", name);
    } else {
        printf("stdin is not a terminal\n");
    }

    return 0;
}


/*

	What is ttyname?

ttyname tells you the name of the terminal device file that a given file descriptor is connected to.

For example: if your program is connected to /dev/pts/0, ttyname will return that path.

🔹 Function prototype
#include <unistd.h>

char *ttyname(int fd);


fd → file descriptor (commonly 0 = stdin, 1 = stdout, 2 = stderr).

Returns → a string with the terminal’s path (like "/dev/pts/0") if fd is a terminal.

Returns NULL on error (and sets errno).

🔹 Example
#include <stdio.h>
#include <unistd.h>

int main() {
    char *name = ttyname(0); // check stdin (fd = 0)

    if (name != NULL) {
        printf("stdin is connected to terminal: %s\n", name);
    } else {
        printf("stdin is not a terminal\n");
    }

    return 0;
}

🔹 Possible Output

If you run it in a terminal:

stdin is connected to terminal: /dev/pts/0


If you redirect input from a file:

stdin is not a terminal

🔑 Difference from isatty

isatty(fd) → only tells you YES/NO (is it a terminal?).

ttyname(fd) → gives you the actual path of the terminal device file.

✅ Simple definition:
ttyname(fd) returns the device file path of the terminal connected to the given file descriptor (like /dev/pts/0).

Do you want me to also show how isatty and ttyname work together in the same small program?

*/