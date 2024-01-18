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
	{ 0x410a7f31, "__platform_driver_register" },
	{ 0x5fbdcc10, "gpiod_put" },
	{ 0xa7196f80, "proc_remove" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x8025af77, "gpiod_get" },
	{ 0x79819bc7, "proc_create" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0xd4e60229, "platform_driver_unregister" },
	{ 0xdcb764ad, "memset" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x3854774b, "kstrtoll" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0x6f978cf7, "gpiod_get_value" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0xa30ddf9b, "gpiod_direction_input" },
	{ 0xb516d99f, "gpiod_set_value" },
	{ 0x1e747a3d, "gpiod_direction_output" },
	{ 0xf7038a43, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cgpio,mygpiodev");
MODULE_ALIAS("of:N*T*Cgpio,mygpiodevC*");

MODULE_INFO(srcversion, "4BD21C59B25A685093767CE");
