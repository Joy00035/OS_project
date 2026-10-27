#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#ifndef SYS_mycall
#define SYS_mycall 454
#endif

int main() {
    long ret = syscall(SYS_mycall, 7);
    printf("sys_mycall(7) = %ld\n", ret);
    return 0;
}
