#include <stdint.h>

/* The prototype shows it is a naked function - in effect this is just an
assembly function. */
void HardFault_Handler( void ) __attribute__( ( naked ) );

void HardFault_Handler_Stage2( uint32_t *pulFaultStackAddress )
{
	/* These are volatile to try and prevent the compiler/linker optimising them
	away as the variables never actually get used.  If the debugger won't show the
	values of the variables, make them global my moving their declaration outside
	of this function. */
	#define __unused __attribute__((unused))
	volatile __unused uint32_t r0;
	volatile __unused uint32_t r1;
	volatile __unused uint32_t r2;
	volatile __unused uint32_t r3;
	volatile __unused uint32_t r12;
	volatile __unused uint32_t lr; /* Link register. */
	volatile __unused uint32_t pc; /* Program counter. */
	volatile __unused uint32_t psr;/* Program status register. */

    r0 = pulFaultStackAddress[ 0 ];
    r1 = pulFaultStackAddress[ 1 ];
    r2 = pulFaultStackAddress[ 2 ];
    r3 = pulFaultStackAddress[ 3 ];

    r12 = pulFaultStackAddress[ 4 ];
    lr = pulFaultStackAddress[ 5 ];
    pc = pulFaultStackAddress[ 6 ];
    psr = pulFaultStackAddress[ 7 ];

    /* When the following line is hit, the variables contain the register values. */
    for( ;; );
}

/* The fault handler implementation calls a function called
prvGetRegistersFromStack(). */
void HardFault_Handler(void)
{
	__asm volatile ("tst lr, #4\n");
	__asm volatile ("ite eq\n");
	__asm volatile ("mrseq r0, msp\n");
	__asm volatile ("mrsne r0, psp\n");
	__asm volatile ("ldr r1, [r0, #24]\n");
	__asm volatile ("ldr r2, addr\n");
	__asm volatile ("bx r2\n");
	__asm volatile ("addr: .word HardFault_Handler_Stage2\n");
/*
    __asm volatile
    (
        " tst lr, #4                                                \n"
        " ite eq                                                    \n"
        " mrseq r0, msp                                             \n"
        " mrsne r0, psp                                             \n"
        " ldr r1, [r0, #24]                                         \n"
        " ldr r2, handler2_address_const                            \n"
        " bx r2                                                     \n"
        " handler2_address_const: .word prvGetRegistersFromStack2    \n"
    );
*/
}

