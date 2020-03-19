#include <linux/string.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>

typedef struct student
{
	int id;
	char *birthday;
	struct list_head node_student;
} student_t;

void my_strcpy(char* dst, const char* src)
{
	char *tmp_src = src, *tmp_dst = dst;

	while(*tmp_src != '\0') {
		*tmp_dst = *tmp_src;
		tmp_src++;
		tmp_dst++;
	}
	*tmp_dst = '\0';
}

student_t *construct_student(const int id, const char* birthday)
{
	student_t *s;
	s = kmalloc(1*sizeof(student_t), GFP_KERNEL);
	s->birthday = kmalloc(30*sizeof(char), GFP_KERNEL);

	my_strcpy(s->birthday, birthday);
	// char buf[] = KERN_INFO " %s";	   
	// printk(buf, s->birthday);
	s->id = id;

	return s;
}

struct list_head class;
char buf_info[] = KERN_INFO " %s";

// init function
int hw_init(void)
{
	char *welcome = "\n\r _   _  _____ _      _     _____ \n \
					 \r| | | ||  ___| |    | |   |  _  |\n \
					 \r| |_| || |__ | |    | |   | | | |\n \
					 \r|  _  ||  __|| |    | |   | | | |\n \
					 \r| | | || |___| |____| |___\\ \\_/ /\n \
					 \r\\_| |_/\\____/\\_____/\\_____/\\___/ \n \
					 ";
	printk(buf_info, welcome);	
	// init list head
	INIT_LIST_HEAD(&class);
	
	student_t *tmp_s;
	int id_list[5] = { 106062541, 105062841, 104052142, \
		103543212, 101021242 };
	char *birth_list[5] = { "15-7-1976", "25-2-1973", "3-8-1542", \
		"30-2-1912", "9-2-1938" };
	int i;
	for(i=0; i<5; i++) {
		tmp_s = construct_student(id_list[i], birth_list[i]);
		list_add_tail(&tmp_s->node_student, &class);
	}
	char buf[] = KERN_INFO "%d, %s.\n";	   
	list_for_each_entry(tmp_s, &class, node_student) {
		printk(buf, tmp_s->id, tmp_s->birthday);
	}
	printk(KERN_INFO "Success!\n");

	return 0;
}

void hw_exit(void)
{
	char *exit = "\r  _______   _______ _____ \n \
				  \r |  ___\\ \\ / /_   _|_   _|\n \
				  \r | |__  \\ V /  | |   | |  \n \
				  \r |  __| /   \\  | |   | |  \n \
				  \r | |___/ /^\\ \\_| |_  | |  \n \
				  \r \\____/\\/   \\/\\___/  \\_/  \n \
				  ";
	printk(buf_info, exit);

	printk(KERN_INFO "remove module\n");
}

module_init(hw_init);
module_exit(hw_exit);
