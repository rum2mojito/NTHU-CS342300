#include <linux/sched/signal.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/sched.h>

char p_buf_template[] = KERN_INFO "pid: %6d|pname: %20s|state: %6d\n";

void dfs(struct task_struct *t_current)
{
	struct task_struct *t_children;
	struct list_head *l_children;

	list_for_each(l_children, &t_current->children) {
		t_children = list_entry(l_children, struct task_struct, sibling);
		printk(p_buf_template, t_children->pid, t_children->comm, t_children->state);
		dfs(t_children);
	}
}

// init function
int hw_init(void)
{
    printk("DFS Starting...");
	struct task_struct *p_children;

    printk(p_buf_template, init_task.pid, init_task.comm, init_task.state);
    dfs(&init_task);

	return 0;
}

void hw_exit(void)
{
	printk(KERN_INFO "remove module\n");
}

module_init(hw_init);
module_exit(hw_exit);
