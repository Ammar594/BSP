#ifndef _CONFIG_H_
#define _CONFIG_H_

/* Falls auf den Boards gearbeitet wird am besten
 * die nächste Zeile auskommentieren
 */
#define __QEMU__

/**
 * \file config.h
 *
 * Enthält defines und static Funktionen zum testen der
 * Implementierung. Wir tauschen diese Werte/Funktionen beim
 * Korrigieren zum Testen aus. Bitte fügt hier KEINE weiteren
 * defines oÄ ein. Ihr könnt diese Werte zum Testen natürlich
 * auch gerne selbst verändern.
 */

/* Include-Pfad bitte gegenfalls anpassen */
#include <arch/bsp/kprintf.h>
#include <arch/bsp/uart.h>
static inline void test_kprintf(void) {
	long unsigned psr;
	char c;
	 __asm__ volatile("mrs %0, cpsr":"=r" (psr));
    kprintf(" init cpsr: %p\n",psr);

	/*Diese Anwendung soll bei der Eingabe von einem s ein Supervisor
	Call auslösen, bei der Eingabe eines a einen Data Abort auslösen, bei der Eingabe eines u eine Undefined
	Instruction ausführen und bei der Eingabe eines p einen Prefetch Abort auslösen.*/
	while(1){
		c = uart_getc();
		kprintf("Es wurde folgender Charakter eingegeben: %c\n",c);
		
			if(c == 's')
				// Supervisor Mode
      			__asm__ ("SVC 0xFFFFFF");

    		else if(c =='p')
				// Prefetch Abort
      			__asm__ ("BKPT 0xFFFF");

		//__asm__ volatile("mrs %0, cpsr":"=r" (psr));
        kprintf("in the loop cpsr: %p\n",psr);
	}
}
/**
 * Erst ab Aufgabenblatt 2 relevant
 */

#ifdef __QEMU__
/* Werte zum testen unter QEMU */
#define BUSY_WAIT_COUNTER 3000000
#else
/* Werte zum testen auf der Hardware */
#define BUSY_WAIT_COUNTER 30000
#endif // __QEMU__

// Wir testen nur mit Werten die durch 2^n darstellbar sind
#define UART_INPUT_BUFFER_SIZE 128

// Timer Interrupt Interval zum testen in Mikrosekunden
// Systimer taktet mit 1MHz
// 1000000 -> 1 Sekunde
#define TIMER_INTERVAL 1000000


#endif // _CONFIG_H_
