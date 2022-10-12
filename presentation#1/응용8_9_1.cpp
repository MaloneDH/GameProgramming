#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define cake_number 31  //과자의 개수 

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
   
	intro_game();//게임시작
	do {
		system("cls");
		start=game_menu();
	} while(start==1);
}

int game_menu(){
	int menu;
	printf("원하시는 메뉴를 골라주세요\n");
	printf("1.게임 시작");
	printf("2. 종료\n");
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
	
	input_participant(user_name, mode, players);//참가자 받기  

	start=0;
 
	system("cls");
	game_control(user_name, cake_condition, &cake_left, players,  &start, players);

	gotoxy(10, 12);
	printf("아무키나 누르면 다음 순서를 진행합니다. ");
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
			printf("아무키나 누르면 다음 순서를 진행합니다. ");
			getch();
		}
	}while(cake_left>2);

	gotoxy(10, 12);
	printf("%s님이 졌습니다. ", user_name[loser]);
	gotoxy(10, 13);
	printf("menu로 돌아갑니다.\n");
	getch();
}
void intro_game(void){
	system("cls");
	printf("베스킨라빈스 31 \n\n"); 
	printf("숫자를 말해주세요 \n\n");	
	printf("마지막숫자를 부르는 사람이벌칙입니다. \n\n");
	printf("아무키나 누르면 게임을 시작합니다.\n");
	getch();

}

int choose_mode(){
	system("cls");
	int choice; 
	printf("원하시는 상대를 골라주세요\n");
	printf("1.컴퓨터와 하기\n"); 
	printf("2.친구랑 하기\n");
	printf("원하시는 모드 숫자를 입력해주세요(1 or 2) :");
	scanf("%d", &choice);
	return choice;
	 
}

int count_player(){
	system("cls");
	int players;
	printf("몇명이서 플레이 하나요? (2 ~ 4 ):");
	scanf("%d", &players);
	return players; 
}

int choose_difficulty(){
	system("cls");
	int difficulty;
	printf("난이도를 설정해주세요\n");
	printf("1.보통\n"); 
	printf("2.쉬움\n"); 
	printf("Enter>");
	scanf("%d", &difficulty);
	return difficulty; 
}

void input_participant(char user_name[][8], int mode, int players){ //참가자 받기   

	system("cls");
	if(mode==1){
		printf("당신의 이름을 입력하고 Enter>");
		scanf("%s", user_name[0]);
		strncpy(user_name[1], "com", sizeof(user_name[1]));
	}
	else{
		for(int i=0; i<players; i++){
			printf("%d번 참가자의 이름을 입력하고 Enter(최대 8글자)>", i+1);
			scanf("%s", user_name[i]);
		}
	}
	printf("아무키나 누르면 게임을 시작합니다.");
	getch(); 
}

void game_control(char name[][8], int condition[],  int *left, int user, int *s, int players){
	int i, choose_number, t;
	cake_display(name, condition, *left, *s, players);
	if (user==players)
		return;  
	gotoxy(10, 10);
	printf("숫자를 골라주세요(1~3):");
	scanf("%d",&choose_number);
	gotoxy(10, 11);
    printf("%s님의 숫자는 %d입니다.",name[user],choose_number); 
			
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
		printf("숫자를 골라주세요(1~3):");
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
    printf("%s님의숫자는 %d입니다.",name[user],choose_number); 
			
	for(i=*s;i<choose_number+*s;i++)
		condition[i]=1;
	*s+=choose_number;
	
	cake_display(name, condition, *left, *s, players);
}

void cake_display(char name[][8], int condition[], int left, int s, int players){
	int i;
	const  char *eat_cake="■", *remain_cake="□";
	gotoxy(30,5);
	if (left<0)
		left=0;
	printf("남은 과자의 수 : %2d 개 ", left);
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
	printf("먹은 과자 수: %2d", s);
}
void gotoxy(int x, int y){ //커서 이동  {
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

