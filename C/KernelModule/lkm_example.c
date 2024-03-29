/*JP:~/WIP/GITRepos/wsl-repository/C/KernelModule$ make
make -C /lib/modules/5.10.60.1-microsoft-standard-WSL2/build M=/home/jp/WIP/GITRepos/wsl-repository/C/KernelModule modules
make[1]: *** /lib/modules/5.10.60.1-microsoft-standard-WSL2/build: No such file or directory.  Stop.
make: *** [Makefile:3: all] Error 2

Fix  for WSL2 : https://unix.stackexchange.com/questions/594470/wsl-2-does-not-have-lib-modules*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE(“GPL”);
MODULE_AUTHOR(“Jayaprakash Palanisamy”);
MODULE_DESCRIPTION(“Linux Kernel Module Test”);
MODULE_VERSION(“0.01”);
MODULE_LICENSE("GPL")

static int __init lkm_example_init(void) {
 printk(KERN_INFO “Hello, World!\n”);
 return 0;
}

static void __exit lkm_example_exit(void) {
 printk(KERN_INFO “Goodbye, World!\n”);
}

module_init(lkm_example_init);
module_exit(lkm_example_exit);

/*
Viewing module printk log messages
-----------——---------------------
dmesg -c > / dev /null
insmod <module_name>.ko
rmmod <module_name>
dmesg
----------------------
Tracing Function calls
-----------------------
cd / sys /kernel/debug/tracing/
echo 0 >tracing_ on
echo function_graph >current_tracer
cat available_tracers
hwlat blk miotrace function_graph wakeup_dl wakeup_rt wakeup function nop
echo >trace
echo :mod:<module_name> ›set_ftrace_filter
echo 1 >tracing_on
insmod <module_name>.ko
cat trace
*/