#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>

char * int_to_str(int n){
	unsigned int modulen = n > 0 ? n : -n;
	unsigned int modulen2 = modulen;
	unsigned int size = 0;
	while(modulen > 0){ //calcolo le cifra in n
		modulen /= 10;
		size++;
	}

	if(n < 0)
		size++;
	char *string = malloc(sizeof(char)*size);

	if(!string)
		return NULL;

	

	while(modulen2){
		char c = modulen2%10 + '0';
		modulen2 /= 10;
		string[--size] = c; 
	}

	if(n < 0)
		*string = '-';

	return string;
}

void printff(char const *  c, ...){

	va_list ptr; //for iteration

	va_start(ptr, c); //getting the list to the arguments passed in ...

	while(*c){
		if(*c != '%')
			putchar(*c);
		else{
			c++;
			char *str;

			if(*c == 'd'){
				str = int_to_str(va_arg(ptr, int));
				
			}
			else if(*c == 's'){
				str = va_arg(ptr, char*);
				
			}

			while(*str)
				putchar(*str++);
		}
		c++;	
	}
}

int main(){
	printff("Salaman%d %s %d %ds dds parm ds",1299,"Torta",-10,-19999199);
}