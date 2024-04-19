
#include <Kernel/Syms.h>
#include <Kernel/File.h>
#include <Hooks.h>

DECL(bool) panic_on_oops;

bool PanicOnUpsDisable()
{
	if (!&panic_on_oops)
		return false;

	panic_on_oops = false;

	return true;
}

bool PanicOnUpsEnable()
{
	if (!&panic_on_oops)
		return false;

	panic_on_oops = true;

	return true;
}

void DriverShowLoaded()
{
	printk(KERN_INFO "");
	printk(KERN_INFO "-----Bug Logger Loaded-----");
	printk(KERN_INFO "-----Bug Logger Loaded-----");
	printk(KERN_INFO "-----Bug Logger Loaded-----");
	printk(KERN_INFO "");
}

void DriverShowUnloaded()
{
	printk(KERN_INFO "");
	printk(KERN_INFO "||||| Bug Logger Unloaded |||||");
	printk(KERN_INFO "||||| Bug Logger Unloaded |||||");
	printk(KERN_INFO "||||| Bug Logger Unloaded |||||");
	printk(KERN_INFO "");
}

bool DriverMain(uintptr_t entryPoint)
{
	PanicOnUpsDisable();
	DriverShowLoaded();
	DriverHooksInstall();
	return true;
}

void DriverShootdown()
{
	DriverHooksUninstall();
	DriverShowUnloaded();
	PanicOnUpsEnable();
}