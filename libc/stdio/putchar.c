#include <stdio.h>
#include <unistd.h> // Include for the write system call

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

int putchar(int ic) {
#if defined(__is_libk)
    char c = (char) ic;
    terminal_write(&c, sizeof(c));
#else
    // Add stdio and the write system call.
    // The write system call takes three arguments: file descriptor, buffer, and count.
    // STDOUT_FILENO is the file descriptor for standard output (typically 1).
    return write(STDOUT_FILENO, &ic, 1) == 1 ? ic : EOF;
#endif
    return ic;
}
