#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

__attribute__((__noreturn__))
void abort(void) {
#if defined(__is_libk)
    // kernel panic
    //  FUTURE TODO: Log the error, dump the state, and halt the system.
    printf("kernel: panic: abort()\n");
    // Maybe I can enter an infinite loop or halt the CPU.
    while (1) { }
#else
    // Abnormally terminate the process as if by SIGABRT
    // Raise the SIGABRT signal to terminate the process
    raise(SIGABRT);
    // If for some reason raise fails, we can call exit with a non-zero status.
    _exit(1);
#endif
    // This point should never be reached.
    __builtin_unreachable();
}
