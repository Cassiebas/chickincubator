#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
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
__used __section("__versions") = {
	{ 0x92997ed8, "_printk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x23d20fbd, "__class_create" },
	{ 0x255a40b1, "device_create" },
	{ 0x4f2b3590, "cdev_init" },
	{ 0x12567b45, "cdev_add" },
	{ 0xedadcbe4, "device_destroy" },
	{ 0x48be46d6, "class_destroy" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x9d8130b9, "cdev_del" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0xdcb764ad, "memset" },
	{ 0x8025af77, "gpiod_get" },
	{ 0x6f978cf7, "gpiod_get_value" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0xa30ddf9b, "gpiod_direction_input" },
	{ 0x1e747a3d, "gpiod_direction_output" },
	{ 0xb516d99f, "gpiod_set_value" },
	{ 0xf7038a43, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "4D726131F08C5C372061181");
