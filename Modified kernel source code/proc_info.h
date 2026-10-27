#ifndef _UAPI_LINUX_PROC_INFO_H
#define _UAPI_LINUX_PROC_INFO_H

struct proc_info {
    long voluntary_ctxt_switches;
    long involuntary_ctxt_switches;
    long minor_faults;
    long major_faults;
};

#endif
