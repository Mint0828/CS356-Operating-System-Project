#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prinfo.h"

/* 
 *      CS356 Operating System Project 1: Problem 1
 * This is an executable which takes one argument from the
 * command line. This argument is taken to be the number of 
 * items to list in in pstree. e.g. $ ./pstree 100
 *           anthor: Ma Yesheng 5140209064
 */

void print_prinfo(struct prinfo *buf)
{
    printf("%s %d %ld %d %d %d %ld\n", 
        buf->comm, 
        buf->pid, 
        buf->state,
        buf->parent_pid,
        buf->first_child_pid,
        buf->next_sibling_pid,
        buf->uid
        );
}

void print_tab(int n)  { while (n--) printf("    "); }
                
void print_pstree(struct prinfo *buf, int ps_size) 
{
    int *depth;
    int i = 0;
    int j = 0;
    
    depth = malloc(ps_size*sizeof(int));
    memset(depth, 0, ps_size);
    print_prinfo(buf);
    for (i = 1; i < ps_size; ++i) {
        if (buf[i].parent_pid == buf[i-1].pid) {
            depth[i] = depth[i-1] + 1;
        } else {
            for (j = i-1; j >= 0; --j) {
                if (buf[j].parent_pid == buf[i].parent_pid) {
                    depth[i] = depth[j];
                    break;
                }
            }
        }
        print_tab(depth[i]);
        print_prinfo(buf+i);
    }
    free(depth);
}
        
int main(int argc, char **argv) 
{
	int buf_size;
    struct prinfo *buf;
    
    if (argc != 2) {
        printf("the only argument of ptree should be the buffer size\n");
        return -1;
    }
    if ((buf_size=(int)strtol(argv[1], NULL, 10)) == 0) {
        printf("invalid size of buffer");
        return -1;
    }
    buf = malloc(buf_size*sizeof(struct prinfo));
    if (syscall(356, buf, &buf_size) != 0) {
        printf("ERROR: ptree failure\n");
        return -1;
    }
    /* 
     * the content of prinfo is printed the the following order:
     * comm, pid, parent_pid, child_pid, sibling_pid, state, uid
     */
    print_pstree(buf, buf_size);
    free(buf);
    return 0;
}

