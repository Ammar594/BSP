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
	/* Nur für Aufgabenblatt 1
	 * Hier Test Funktion für kprintf schreiben und
	 * nach dem vollständigen initialisieren aufrufen
	 */
	kprintf("kprintf_test\n");


	kprintf("this was supposed to be a number: %q %q",1234, 11);
	int x = 10;
	kprintf("testing hexadecimal: %p \n", 60);
	kprintf("testing hexadecimal with field width 8: %8p \n", 60);
	kprintf("testing unsigned with field width 8 and 0s: %08u\n", 60);
	kprintf("test negative number : %i\n", -333);
	kprintf("test negative number with field width 8: %8i\n", -333);
	kprintf("test negative number with field width 8: %08i\n", -333);
	kprintf("test negative number with field width 8: %8i\n", 0);
	kprintf("test negative number with field width 8: %08i\n", 0);
	kprintf("test negative number %i\n", 3);
	kprintf("this is an address! %p\n", &x);
	kprintf("this is an address! %8p\n", &x);
	kprintf("testing a string: %s\n", "what a sexy kernal!");
	kprintf("testing a character: %c\n", 87);
	kprintf("testing zero: %u\n",0);
	kprintf("testing zero in hexdecimal %x \n", 0);
	kprintf("testing zero hexdecimal with field width 8 %8x \n", 0);
	kprintf("testing zero hexdecimal with field width 8 and 0s %08x \n", 255);
	kprintf("keyboard input, press any key and it will be printed on the screen. \n");
	while(1){
	char c = uart_getc();
		kprintf("Es wurde folgender Charakter eingegeben: %c, In Hexadezimal: %x, In Dezimal: %08u\n", c, c, c);
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
