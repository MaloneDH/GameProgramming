#include<stdio.h>
#include<string.h>
#include<stdbool.h> 

void Chkmirror(char x[]);

int main(void){
	char s[]="abcdedcba";
	int length=strlen(s);
	bool t=true;
	
	for(int i=0;i<length/2;i++){
		if(s[i]!= s[length-1-i]){
			printf("ȸ���� �ƴմϴ�.");
			t=false;
			break;
		}
	}
	
	if(t==true) printf("ȸ���� �½��ϴ�.");
	
	
}

