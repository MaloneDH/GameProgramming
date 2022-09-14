#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int main(void){
	char string[20];
	char c;
	printf("문자열입력: ");
	scanf("%s", string); 
	printf("문자입력: ");
	scanf("%c", &c);
	
	printf("%s\n", string);
	printf("!!%c!!\n", c); 
	return 0;
}

