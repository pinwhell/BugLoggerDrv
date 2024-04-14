#include <Hooks.h>
#include <Kernel/Decls.h>
#include <Kernel/PtRegs.h>
#include <Kernel/Memory.h>


#define EBUL_NOTFOUND ~uintptr_t(0x0)

uintptr_t ELFBaseUpwardsLookup(uintptr_t startAt, size_t maxUppwardLookup = 0xF00000)
{
	const uintptr_t upperEdge = startAt - maxUppwardLookup;

	for (uintptr_t i = startAt; i >= upperEdge; i--)
	{
		constexpr uint32_t elfMagic = 0x464c457f; // 7F 45 4C 46;

		if (*(uint32_t*)i != elfMagic)
			continue;

		return i;
	}

	return EBUL_NOTFOUND;
}

REGPARAMDECL(void) show_ip(struct pt_regs* regs, const char* loglvl);
void (KERN_CALL* oLogIp)(struct pt_regs* regs, const char* loglvl);
void KERN_CALL hLogIp(struct pt_regs* regs, const char* loglvl)
{
	uintptr_t elfBase = ELFBaseUpwardsLookup(regs->ip);

	if (elfBase == EBUL_NOTFOUND)
		return oLogIp(regs, loglvl);

	uintptr_t instDisp = regs->ip - elfBase;

	KLOG_PRINT("Module Base %llx", elfBase);
	KLOG_PRINT("IP %llx:%llx+%llx", regs->ip, elfBase, instDisp);
}

void DriverHooksInstall()
{
	HOOKTRAMP_INSTALL(show_ip, hLogIp, &oLogIp);
}

void DriverHooksUninstall()
{
	HOOKTRAMP_RESTORE(show_ip, oLogIp);
}