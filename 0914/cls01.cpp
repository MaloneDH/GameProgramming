#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int main(void){
	char s;
	scanf("%c", &s);
	while(1) {
		printf("%c", s);
		scanf("%c", &s);
		if(s='\n') { break; }
	}
	printf("Good Bye!");
	return 0;
}

