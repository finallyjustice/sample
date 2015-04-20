#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "defs.h"

extern char end[]; // first address after kernel loaded from ELF file

void cgaputc(int c);

int
main(void)
{
	cgaputc('P');
	cgaputc('Q');
	cgaputc('R');
	cgaputc('S');	
	cgaputc('\n');

	cprintf("Hello World\n");

	while(1);
	return 0;
}

pde_t entrypgdir[];  // For entry.S

// Boot page table used in entry.S and entryother.S.
// Page directories (and page tables), must start on a page boundary,
// hence the "__aligned__" attribute.  
// Use PTE_PS in page directory entry to enable 4Mbyte pages.
__attribute__((__aligned__(PGSIZE)))
pde_t entrypgdir[NPDENTRIES] = {
	// Map VA's [0, 4MB) to PA's [0, 4MB)
	[0] = (0) | PTE_P | PTE_W | PTE_PS,
	// Map VA's [KERNBASE, KERNBASE+4MB) to PA's [0, 4MB)
	[KERNBASE>>PDXSHIFT] = (0) | PTE_P | PTE_W | PTE_PS,
};
