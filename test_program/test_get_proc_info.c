#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#ifndef SYS_get_proc_info
#define SYS_get_proc_info 455
#endif

struct proc_info {
    long voluntary_ctxt_switches;
    long involuntary_ctxt_switches;
    long minor_faults;
    long major_faults;
};

int main() {
    struct proc_info info;
    pid_t pid = getpid();

    long ret = syscall(SYS_get_proc_info, pid, &info);
    if (ret != 0) {
        perror("sys_get_proc_info");
        return 1;
    }

    printf("PID: %d\n", pid);
    printf("Voluntary context switches: %ld\n", info.voluntary_ctxt_switches);
    printf("Involuntary context switches: %ld\n", info.involuntary_ctxt_switches);
    printf("Minor page faults: %ld\n", info.minor_faults);
    printf("Major page faults: %ld\n", info.major_faults);

    return 0;
}
