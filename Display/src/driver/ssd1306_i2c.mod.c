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
	{ 0x5049b362, "i2c_register_driver" },
	{ 0x92997ed8, "_printk" },
	{ 0xa7196f80, "proc_remove" },
	{ 0x79819bc7, "proc_create" },
	{ 0x4ee378a6, "i2c_del_driver" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0xdcb764ad, "memset" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0x9adfe79a, "i2c_transfer_buffer_flags" },
	{ 0x37a0cba, "kfree" },
	{ 0xf7038a43, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("i2c:ssd1306");
MODULE_ALIAS("of:N*T*Cdisplay,ssd1306");
MODULE_ALIAS("of:N*T*Cdisplay,ssd1306C*");

MODULE_INFO(srcversion, "7116A49607E9A4D7355914D");
