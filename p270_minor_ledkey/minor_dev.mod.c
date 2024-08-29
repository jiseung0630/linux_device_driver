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
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x92997ed8, "_printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x3d87ed5b, "gpio_to_desc" },
	{ 0xb4ca5a15, "gpiod_set_raw_value" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0x5f754e5a, "memset" },
	{ 0x3ea1b6e4, "__stack_chk_fail" },
	{ 0x657fc34a, "gpiod_get_raw_value" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xfe990052, "gpio_free" },
	{ 0x43838dc4, "__register_chrdev" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x39cf4498, "gpiod_direction_output_raw" },
	{ 0x943b4d0f, "gpiod_direction_input" },
	{ 0x31ce3c7c, "param_ops_int" },
	{ 0x65a4ef4c, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "A1843F44E448954D994800D");
