#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define cake_number 31  //������ ���� 

void intro_game(void);
int game_menu();
void main_game();
int choose_mode();
int choose_difficulty();
int count_player();
void input_participant(char user_name[][8], int mode, int players);
void game_control(char name[][8], int condition[], int *left, int user, int *start, int players);
void game_control_com(char name[][8], int condition[],  int *left, 
int user, int *s, int players, int difficulty);
void cake_display(char name[][8], int condition[], int left, int start, int players);
void gotoxy(int x, int y);

int main(void){
	int start=1;
	srand(time(NULL));
   
	intro_game();//���ӽ���
	do {
		system("cls");
		start=game_menu();
	} while(start==1);
}

int game_menu(){
	int menu;
	printf("���Ͻô� �޴��� ����ּ���\n");
	printf("1.���� ����");
	printf("2. ����\n");
	printf("Enter>");
	scanf("%d", &menu);
	if(menu==1){
		main_game();
		return 1;
	}
	else  return 0;
}

void main_game(){
	int i, start,cake_left=cake_number, loser, mode, players, difficulty; // 
	int cake_condition[cake_number]={0};
	
	mode=choose_mode();
	if(mode==2) 
		players=count_player();
	else {
		players=2;
		difficulty=choose_difficulty();
	}
	
	char user_name[players][8];
	
	input_participant(user_name, mode, players);//������ �ޱ�  

	start=0;
 
	system("cls");
	game_control(user_name, cake_condition, &cake_left, players,  &start, players);

	gotoxy(10, 12);
	printf("�ƹ�Ű�� ������ ���� ������ �����մϴ�. ");
	getch();
	do
	{
		for(i=0;i<players;i++)
		{
			system("cls");
			if(mode==1)
				game_control_com(user_name, cake_condition, &cake_left, i, &start, players, difficulty);
			else
				game_control(user_name, cake_condition, &cake_left, i,  &start, players);
			if (cake_left<2)
			{
				loser=i;
				break;
			}
			gotoxy(10, 12);
			printf("�ƹ�Ű�� ������ ���� ������ �����մϴ�. ");
			getch();
		}
	}while(cake_left>2);

	gotoxy(10, 12);
	printf("%s���� �����ϴ�. ", user_name[loser]);
	gotoxy(10, 13);
	printf("menu�� ���ư��ϴ�.\n");
	getch();
}
void intro_game(void){
	system("cls");
	printf("����Ų��� 31 \n\n"); 
	printf("���ڸ� �����ּ��� \n\n");	
	printf("���������ڸ� �θ��� ����̹�Ģ�Դϴ�. \n\n");
	printf("�ƹ�Ű�� ������ ������ �����մϴ�.\n");
	getch();

}

int choose_mode(){
	system("cls");
	int choice; 
	printf("���Ͻô� ��븦 ����ּ���\n");
	printf("1.��ǻ�Ϳ� �ϱ�\n"); 
	printf("2.ģ���� �ϱ�\n");
	printf("���Ͻô� ��� ���ڸ� �Է����ּ���(1 or 2) :");
	scanf("%d", &choice);
	return choice;
	 
}

int count_player(){
	system("cls");
	int players;
	printf("����̼� �÷��� �ϳ���? (2 ~ 4 ):");
	scanf("%d", &players);
	return players; 
}

int choose_difficulty(){
	system("cls");
	int difficulty;
	printf("���̵��� �������ּ���\n");
	printf("1.����\n"); 
	printf("2.����\n"); 
	printf("Enter>");
	scanf("%d", &difficulty);
	return difficulty; 
}

void input_participant(char user_name[][8], int mode, int players){ //������ �ޱ�   

	system("cls");
	if(mode==1){
		printf("����� �̸��� �Է��ϰ� Enter>");
		scanf("%s", user_name[0]);
		strncpy(user_name[1], "com", sizeof(user_name[1]));
	}
	else{
		for(int i=0; i<players; i++){
			printf("%d�� �������� �̸��� �Է��ϰ� Enter(�ִ� 8����)>", i+1);
			scanf("%s", user_name[i]);
		}
	}
	printf("�ƹ�Ű�� ������ ������ �����մϴ�.");
	getch(); 
}

void game_control(char name[][8], int condition[],  int *left, int user, int *s, int players){
	int i, choose_number, t;
	cake_display(name, condition, *left, *s, players);
	if (user==players)
		return;  
	gotoxy(10, 10);
	printf("���ڸ� ����ּ���(1~3):");
	scanf("%d",&choose_number);
	gotoxy(10, 11);
    printf("%s���� ���ڴ� %d�Դϴ�.",name[user],choose_number); 
			
	for(i=*s;i<choose_number+*s;i++)
		condition[i]=1;
	*s+=choose_number;

	cake_display(name, condition, *left, *s, players);
}	

void game_control_com(char name[][8], int condition[],  
int *left, int user, int *s, int players, int difficulty){
	int i, choose_number;
	cake_display(name, condition, *left, *s, players);

	if (user==players)
		return;   
	else if (user==0){
		gotoxy(10, 10);
		printf("���ڸ� ����ּ���(1~3):");
		scanf("%d",&choose_number);
	}
	else //computer turn
		if(difficulty=2){
			choose_number=rand()%3+1;
			if(*left<=3) choose_number=*left;
		}
		else
			choose_number=rand()%3+1;
	*left-=choose_number;
	gotoxy(10, 11);
    printf("%s���Ǽ��ڴ� %d�Դϴ�.",name[user],choose_number); 
			
	for(i=*s;i<choose_number+*s;i++)
		condition[i]=1;
	*s+=choose_number;
	
	cake_display(name, condition, *left, *s, players);
}

void cake_display(char name[][8], int condition[], int left, int s, int players){
	int i;
	const  char *eat_cake="��", *remain_cake="��";
	gotoxy(30,5);
	if (left<0)
		left=0;
	printf("���� ������ �� : %2d �� ", left);
	for(i=0;i<players;i++)
	{
		gotoxy(i*10+10, 6);
		printf("%s", name[i]);
	}
	for(i=0;i<31;i++)
		if (condition[i]==1)
		{
			gotoxy(10+i*2, 8);
			printf("%s", eat_cake);
		}
		else
		{
			gotoxy(10+i*2, 8);
			printf("%s", remain_cake);
		}
	gotoxy(10, 9);
	printf("���� ���� ��: %2d", s);
}
void gotoxy(int x, int y){ //Ŀ�� �̵�  {
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

