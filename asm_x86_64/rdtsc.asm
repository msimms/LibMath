global _GetRDTSC

section .text

_GetRDTSC:
	cpuid
	rdtsc
	shl   rdx, 32
	or    rax, rdx
	ret
