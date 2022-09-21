#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<conio.h>
int calc_frequency(int octave);
void practice_piano(void);

int main(){
	printf("1���� 8���� ���� Ű�� ������ \n �� ���� �Ҹ��� ��µ˴ϴ�.\n\n");
	printf("1:�� 2:�� 3:�� 4:�� 5:�� 6:�� 7:�� 8:��\n ");
	printf("���α׷� ����� ESCŰ\n");
	practice_piano();
	return 0;
}

int calc_frequency(int octave, int inx){
	double do_scale=32.7032;
	double ratio=pow(2., 1/12.), temp;
	int i;
	temp=do_scale*pow(2, octave-1);
	for(i=0;i<inx;i++){
		temp=(int)(temp+0.5);
		temp*=ratio;
	}
	return (int)temp;
}

void practice_piano(void){
	int index[]={0,2,4,5,7,9,11,12};
	int freq[8], code;
	int i;
	for(i=0;i<8;i++) freq[i]=calc_frequency(4, index[i]);
	do{
		code=getch();
		if('1'<=code && code <='8'){
			code-=49;
			Beep(freq[code], 300);
		}
	}while(code!=27);
}
