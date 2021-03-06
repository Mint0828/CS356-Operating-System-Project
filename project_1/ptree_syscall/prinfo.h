#ifndef __LINUX_PRINFO_H
#define __LINUX_PRINFO_H

#include <linux/types.h>
#include <linux/sched.h>
/*
 * this file is the header of the type prinfo
 * which stores the information required by the 
 * system call routine pstree
 */

struct prinfo {
    pid_t parent_pid;
    pid_t pid;
    pid_t first_child_pid;
    pid_t next_sibling_pid;
    long state;
    long uid;
    char comm[TASK_COMM_LEN];
};

#endif
