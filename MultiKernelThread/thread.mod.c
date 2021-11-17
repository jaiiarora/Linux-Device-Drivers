#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xe160d451, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x8d60f361, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x3ca30931, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x9cea8cdf, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xb6df2f, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xf35f9014, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x54a62ac7, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x6563d8d5, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x3401e6e5, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0xb8bac3b, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x1bf7f113, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x778b8af3, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x9c079d54, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7DEAF7D622C071B9319A420");
