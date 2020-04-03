#include <linux/sched/signal.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/sched.h>

// init function
int hw_init(void)
{
	struct task_struct *p;
    char p_buf_tempalte[] = KERN_INFO "pid: %6d|pname: %20s|state: %6d\n";	 

    for_each_process(p) {
        printk(p_buf_tempalte, p->pid, p->comm, p->state);
    }

	return 0;
}

void hw_exit(void)
{
	printk(KERN_INFO "remove module\n");
}

module_init(hw_init);
module_exit(hw_exit);
