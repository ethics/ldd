#include<linux/module.h>
#include<linux/kernel.h>


static int __init testmodule_init(void)
{
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
MODULE_DESCRIPTION("Kernel Test Module");
MODULE_VERSION("1.0");
