#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <arch/bsp/kprintf.h>
#include <arch/bsp/uart.h>
#define MAX_PRINT_SIZE 512
#define True 1
#define False 0
int kprintf(char *format, ...) {

	va_list ap;
	unsigned char buffer[MAX_PRINT_SIZE];
	int index=0;
	va_start(ap, format);
	char * str = format;
	int toggle = False;
	int toggle2 = False;
	while(1) {
		// reched the end of the string null pointer \0
		if (*str==0) break;
		if (*str=='%') {
			str++;
			if (*str == 's'){
				char * string = va_arg(ap, char *);
				for(int i = 0;string[i] != 0;i++){
					buffer[index] = string[i];
					index++;
				}
				str++;
				continue;
			}
			else if (*str == '%'){
				buffer[index] = '%';
				index++;
				str++;
				continue;
			}
			else if (*str == 'c'){
				unsigned int num = va_arg(ap, unsigned int);
				unsigned char tmp = (unsigned char) num;
				buffer[index] = tmp;
				index++;
				str++;
				continue;
			}
			else if (*str == '0')
			{
				str++;
				if(*str == '8') {
					toggle2 = True;
					str++;
				}
				else{
					kprintf("Wrong format.\n");
				return 0;
				}
			}
			else if(*str == '8') {
				toggle = True;
				str++;
			}
			if (*str == 'p'){
				long unsigned addr = va_arg(ap, long unsigned);
				unsigned cpy = addr;
				char tmp_buffer[10];
				int num_length = 9;
				do{
					unsigned char tmp = cpy % 16;
					if(tmp >= 10) tmp += 55 ;
					else tmp += 48;
					tmp_buffer[num_length--] = tmp;
					cpy /= 16; 
				}while(cpy != 0);

				tmp_buffer[num_length--] = 'x';
				tmp_buffer[num_length--] = '0';

				if(toggle == True){
					int len = 8 - (9 - num_length);
					while(len > 0){
						buffer[index++] = '!';
						len--; 
					}
					toggle = False;
				}
				for(int i = num_length + 1; i < 10;i++) {
					buffer[index] = tmp_buffer[i];
					index++;
				}
				str++;
			}
			else if (*str=='i') {
				int num = va_arg(ap, int);
				char tmp_buffer[10];
				int num_length = 9;
				int cpy = num;
				if ( num < 0 ){
					cpy *= -1;
				}
				do{
					unsigned char tmp = (cpy % 10) + 48;
					tmp_buffer[num_length--] = tmp;
					cpy /= 10;
					if (cpy == 0) break;
				}while(cpy != 0);
				if (toggle2){
					if(num <0){
						int len = 7 - (9 - num_length);
						while(len > 0){
							tmp_buffer[num_length--] = '0';
							len--; 
						}
						tmp_buffer[num_length--] = '-';
					}
					else{
						int len = 8 - (9 - num_length);
						while(len > 0){
							tmp_buffer[num_length--] = '0';
							len--; 
						}
					}
					toggle2 = False;
				}
				else if(num < 0){
					tmp_buffer[num_length--] = '-';
				}
				
				if(toggle){
					int len = 8 - (9 - num_length);
					while(len > 0){
						buffer[index++] = ' ';
						len--; 
					}
					toggle = False;
				}
				for(int i = num_length + 1; i < 10;i++) {
					buffer[index] = tmp_buffer[i];
					index++;
				}
				str++;
			}
			else if (*str == 'u'){
				unsigned int num = va_arg(ap, unsigned int);
				char tmp_buffer[10];
				int num_length = 9;
				
				do{
					unsigned char tmp = (num % 10) + 48;
					tmp_buffer[num_length--] = tmp;
					num /= 10;
				}while(num != 0);
				// copy the number characters to buffer
				if(toggle){
					int len = 8 - (9 - num_length);
					while(len > 0){
						buffer[index++] = ' ';
						len--; 
					}
					toggle = False;
				}
				else if(toggle2 == True){
					int len = 8 - (9 - num_length);
					while(len > 0){
						buffer[index++] = '0';
						len--; 
					}
					toggle2 = False;
				}
				for(int i = num_length + 1; i < 10;i++) {
					buffer[index] = tmp_buffer[i];
					index++;
				}
				str++;
			}
			
			else if (*str=='x') {
				str++;
				unsigned int num = va_arg(ap, unsigned int);
				unsigned char tmp_buffer[10];
				int num_length = 9;
				do{
					char tmp = num % 16;
					if(tmp >= 10) tmp += 87;
					else tmp += 48;
					tmp_buffer[num_length--] = tmp;
					num /= 16;
				}while(num != 0);

				if(toggle){
					int len = 8 - (9 -num_length + 1);
					while(len > 0){
						buffer[index++] = ' ';
						len--; 
					}
					toggle = False;
				}
				if (toggle2){
					int len = 8 - (9 - num_length + 1);
					while(len >= 0){
						tmp_buffer[num_length--] = '0';
						len--; 
					}
					toggle2 = False;
				}
				for(int i = num_length + 1; i < 10;i++) {
					buffer[index] = tmp_buffer[i];
					index++;
				}
				
			}
			else
				{
				//error reporting when the argument is not valid	
				char * err = "ERROR: unknown format: ";
				for(int i = 0;i < 23;i++){
					buffer[index++] = err[i];
				}
				buffer[index++] = '%';
				buffer[index++] = *str;
				str++;
			}
		}
		else {
			buffer[index++]=*str;
			str++;
		}
	}
	va_end(ap);
	uart_write(buffer, index);

	return index;
}