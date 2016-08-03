// Segments in proc->gdt.
#define NSEGS     7

// Per-CPU state
struct cpu {
	uchar id;                    // index into cpus[] below
	uchar apicid;                // Local APIC ID
	////struct context *scheduler;   // swtch() here to enter scheduler
	////struct taskstate ts;         // Used by x86 to find stack for interrupt
	////struct segdesc gdt[NSEGS];   // x86 global descriptor table
	volatile uint started;       // Has the CPU started?
	int ncli;                    // Depth of pushcli nesting.
	int intena;                  // Were interrupts enabled before pushcli?
	
	// Cpu-local storage variables; see below
	void *local;
};

extern struct cpu cpus[NCPU];
extern int ncpu;

// Per-CPU variables, holding pointers to the
// current cpu and to the current process.
// The asm suffix tells gcc to use "%gs:0" to refer to cpu
// and "%gs:4" to refer to proc.  seginit sets up the
// %gs segment register so that %gs refers to the memory
// holding those two variables in the local cpu's struct cpu.
// This is similar to how thread-local variables are implemented
// in thread libraries such as Linux pthreads.
extern __thread struct cpu *cpu;
