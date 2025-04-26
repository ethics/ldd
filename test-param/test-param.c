#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>

static int debug;
module_param(debug, int, 0444); // module_param(name(name of an already defined variable), type(either byte, int, short, long ..), perm(visibility in sysfs at /sys/modules/<module_name/parameters/<param> see linux/stat.h
MODULE_PARM_DESC(debug, "Enable debug mode");

static int init_debug_mode(void)
{
	pr_info("Debug mode enabled\n");
	dump_stack(); // It is a Linux kernel function that prints the current call stack (the list of functions that were called to reach the current point).
	return 0;
}

static int __init testmodule_init(void)
{
	if(debug)
	  init_debug_mode();
	pr_info("Test module initilalized\n");
	return 0;
}

static void __exit testmodule_exit(void)
{
	pr_info("Exiting test module\n");
}

module_init(testmodule_init);
module_exit(testmodule_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sivakumar B<sivakumar.bs@gmail.com>");
MODULE_DESCRIPTION("Kernel Test Module with paramaters");
MODULE_VERSION("1.0");
