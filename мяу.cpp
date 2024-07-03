// мяу.cpp: главный файл проекта.


#include "stdafx.h" 
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <string.h> 
#include <malloc.h> 
#include <windows.h>
#include <clocale> 

using namespace std; 
using namespace System; 
using namespace System::IO; 

#define ENTER 13 
#define ESC 27 
#define UP 72 
#define DOWN 80 
 

 
struct z { 
  char name[20]; 
  char vid[20]; 
  long tsena; 
  char data[11];
  long kolva;
}; 
struct sp { 
  char punkt[20]; 
  long tsena;   
  struct sp* sled;
  struct sp* pred;
  long kolva;
 } *spisok; 
struct sp* spisko;
 
int menu(int); 
void maxim(struct z*); 
void first(struct z*); 
void text_data(char *,char *); 
void kolvo(struct z *); 
void alfalist(struct z*); 
void vstavka(struct z*,char*); 
void vstavko(struct z*,char*); 
void listing(struct z*); 
void diagram(struct z*); 
void slvpr(struct z*);
 
int main(array<System::String ^> ^args) 
{ 
int i,n,NC; 
FILE *in;
char dan[9][55]={ 
 "Какой пункт в меню стоит наибольшую сумму?            ", 
 "Самый старый пункт меню:                              ", 
 "Список пунктов \"Сразу\"  с ценой свыше 50 рублей       ", 
 "Алфавитный список пунктов меню                        ", 
 "Количество пуктов в меню по виду с клавиатуры         ", 
 "Диаграмма. Процент покупок                            ", 
 "2 пункта меню с одинаковой ценой, но разным временем  ",
 "Выход                                                 ", 
 "                                                      ",
}; 
char BlankLine[ ]="                                                        "; 
struct z *menus; 
setlocale(LC_CTYPE,".1251"); 
Console::CursorVisible::set(false); 
Console::BufferHeight=Console::WindowHeight; 
Console::BufferWidth=Console::WindowWidth; 
 
if((in=fopen("MENU.txt","r"))==NULL)
{
printf("\nФайл не открыт !"); 
getch(); 
return 0; 
}
 
fscanf(in,"%d",&NC); 
menus=(struct z*)malloc(NC*sizeof(struct z)); 
for(i=0;i<NC;i++) 
fscanf(in,"%s%s%ld%s%ld",menus[i].name, menus[i].vid, &menus[i].tsena, menus[i].data, &menus[i].kolva); 
for(i=0;i<NC;i++) 
printf("\n%-20s %-20s %7ld %s %7ld", menus[i].name, menus[i].vid, menus[i].tsena, menus[i].data,menus[i].kolva); 
getch(); 
 
while(1) 
{ 
 Console::ForegroundColor=ConsoleColor::Black; 
Console::BackgroundColor=ConsoleColor::Green; 
Console::Clear(); 
Console::ForegroundColor=ConsoleColor::White; 
Console::BackgroundColor=ConsoleColor::Black; 
 Console::CursorLeft=10; 
Console::CursorTop=4; 
printf(BlankLine); 
for(i=0;i<9;i++) 
{ 
Console::CursorLeft=10; 
Console::CursorTop=i+5; 
printf(" %s ",dan[i]); 
} 
 Console::CursorLeft=10; 
 Console::CursorTop=12; 
 printf(BlankLine); 
 
n=menu(8); 
 switch(n) { 
case 1: maxim(menus); break; 
case 2: first(menus); break; 
case 3: listing(menus); break; 
case 4: alfalist(menus); break; 
case 5: kolvo(menus); break; 
case 6: diagram(menus); break; 
case 7: slvpr(menus); break;
case 8: exit(0); 
 } 
} // конец while(1)... 
return 0; 
} // конец main() 
 
int menu(int n) 
{ 
	char dan[9][55]={ 
 "Какой пункт в меню стоит наибольшую сумму?            ", 
 "Самый старый пункт меню:                              ", 
 "Список пунктов \"Сразу\"  с ценой свыше 50 рублей       ", 
 "Алфавитный список пунктов меню                        ", 
 "Количество пуктов в меню по виду с клавиатуры         ", 
 "Диаграмма. Процент покупок                            ", 
 "2 пункта меню с одинаковой ценой, но разным временем  ",
 "Выход                                                 ", 
 "                                                      ",
}; 
 

int y1=0,y2=n-1; 
char c=1; 
while (c!=ESC) 
{ 
switch(c) { 
case DOWN: y2=y1; y1++; break; 
case UP: y2=y1; y1--; break; 
case ENTER: return y1+1; 
} 
if(y1>n-1){y2=n-1;y1=0;} 
if(y1<0) {y2=0;y1=n-1;} 
Console::ForegroundColor=ConsoleColor::White; 
Console::BackgroundColor=ConsoleColor::Magenta; 
Console::CursorLeft=11; 
Console::CursorTop=y1+5; 
printf("%s",dan[y1]); 
 
Console::ForegroundColor=ConsoleColor::White; 
Console::BackgroundColor=ConsoleColor::Black; 
Console::CursorLeft=11; 
Console::CursorTop=y2+5; 
printf("%s",dan[y2]); 
c=getch(); 
} // конец while(c!=ESC)... 
exit(0); 
} 
 
void maxim(struct z* menus) 
{ 
int i=0,NC; 
struct z best; 
FILE* in;
in=fopen("MENU.txt","r");
fscanf(in,"%d",&NC); 


strcpy(best.name,menus[0].name); 
best.tsena=menus[0].tsena; 
for(i=1;i<NC;i++) 
if (menus[i].tsena>best.tsena) 
{ 
strcpy(best.name,menus[i].name); 
best.tsena=menus[i].tsena; 
} 
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::Green; 
Console::CursorLeft=10; 
Console::CursorTop=15; 
printf("Максимальную стоимость %ld рублей",best.tsena); 
Console::CursorLeft=10; 
Console::CursorTop=16; 
printf("имеет пункт %s",best.name); 
getch(); 
} 
 
void text_data(char *s,char *sd) 
{ 
char s0[3],month[12][9]={ 
"января","февраля","марта","апреля","мая","июня", 
"июля","августа","сентября","октября","ноября","декабря"}; 
strcpy(s,sd+8); 
strcat(s," "); 
strncpy(s0,sd+5,2); s0[2]=0; 
strcat(s,month[


atoi(s0)-1]); 
strcat(s," "); 
strncat(s,sd,4); 
return; 
} 
void first(struct z* menus) 
{ 
int i,NC; 
char s[17]; 
struct z* best=menus; 
FILE* in;
in=fopen("MENU.txt","r");
fscanf(in,"%d",&NC); 
for(i=1;i<NC;i++) 
if (strcmp(menus[i].data,best->data)<0) 
best=&menus[i]; 
text_data(s,best->data); 
 
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::Green; 
Console::CursorLeft=10; 
Console::CursorTop=15; 
printf("Самый \"старый\" пункт меню со скоростью приготовления \"%s\" за %ld р.", best->vid,best->tsena); 
Console::CursorLeft=10; 
Console::CursorTop=16; 
printf("имеет блюдо %s",best->name); 
Console::CursorLeft=10; 
Console::CursorTop=17; 
printf("Добавлен %s ",s); 
getch(); 
} 
 
void kolvo(struct z *menus) 
{ 
int i,k=0,NC; 
char F[20];
FILE* in;
in=fopen("MENU.txt","r");
fscanf(in,"%d",&NC); 
Console::CursorLeft=10; 
Console::CursorTop=15; 
Console::ForegroundColor=ConsoleColor::Yellow; 
Console::BackgroundColor=ConsoleColor::Green; 
printf("Ввдите поисковую характеристику\n");
SetConsoleCP(1251);
Console::CursorLeft=10; 
gets(F);
SetConsoleCP(866);
for(i=0;i<NC;i++) 
if (strcmp(menus[i].vid,F)==0) 
k++; 

if (k!=0){
	Console::CursorLeft=10; 
Console::CursorTop=17; 
printf("Время выдачи \"%s\" Всего : %d",F,k); 

}
else{
	Console::CursorLeft=10; 
Console::CursorTop=17; 
	printf("Нет результата");
}
getch(); 
} 
 
void alfalist(struct z* menus) 
{ 
int i,NC; 
struct sp* nt; 
struct sp* z; 
FILE* in;
in=fopen("MENU.txt","r");
fscanf(in,"%d",&NC); 
Console::ForegroundColor=ConsoleColor::White; 
Console::BackgroundColor=ConsoleColor::Black; 
Console::Clear(); 
if(!spisok) 
for(i=0;i<NC;i++) 
vstavka(menus,menus[i].name); 
if(!spisko)
for(i=0;i<NC;i++)
vstavko(menus,menus[i].name);
Console::Clear(); 
printf("\n Алфавитное меню"); 
printf("\n ===============================\n"); 
for(nt=spisok; nt!=0; nt=nt->sled) 
printf("\n %-20s %ldр.",nt->punkt,nt->tsena); 
Console::CursorLeft = 60;
Console::CursorTop = 4;

for(nt=spisko; nt!=0; nt=nt->sled){
Console::CursorLeft = 60;
	printf(" %-20s %ldр.\n",nt->punkt,nt->tsena); 
}

getch(); 
}
 
void vstavka(struct z* menus,char* punkt) 
{ 
int i,NC; 
struct sp *nov,*nt,*z=0; 
FILE* in;
in=fopen("MENU.txt","r");
fscanf(in,"%d",&NC); 
for(nt=spisok; nt!=0 && strcmp(nt->punkt,punkt)<0; z=nt, nt=nt->sled); 
if(nt && strcmp(nt->punkt,punkt)==0) return; 
nov=(struct sp *) malloc(sizeof(struct sp)); 
strcpy(nov->punkt,punkt); 
nov->sled=nt; 
nov->tsena=0; 
for(i=0;i<NC;i++) 
if(strcmp(menus[i].name,punkt)==0) 
nov->tsena+=menus[i].tsena; 
if(!z) spisok=nov; 
else z->sled=nov; 
return; 
} 
void vstavko(struct z* menus,char* punkt){
	int i,NC;
	struct sp *nov,*nt,*z=0; 
	FILE* in;
	in=fopen("MENU.txt","r");
	fscanf(in,"%d",&NC); 
	for(nt=spisko; nt!=0 && strcmp(nt->punkt,punkt)>0; z=nt, nt=nt->sled);
	if(nt && strcmp(nt->punkt,punkt)==0)
		return;
	nov=(struct sp *) malloc(sizeof(struct sp));
	strcpy(nov->punkt,punkt);
	nov->sled=nt;
	nov->tsena=0;
	for(i=0;i<NC;i++)
		if(strcmp(menus[i].name,punkt)==0)
			nov->tsena+=menus[i].tsena;
	if (!z)
		spisko=nov;
	else
		z->sled=nov;
	return;
}
 
void listing(struct z* menus) 
{ 
int i,NC; 
struct z* nt;
FILE* in;
in=fopen("MENU.txt","r");
fscanf(in,"%d",&NC); 
Console::ForegroundColor=ConsoleColor::White; 
Console::BackgroundColor=ConsoleColor::Black; 
Console::Clear(); 
printf("\n\r Список пунктов \"Сразу\"  с ценой свыше 50 рублей"); 
printf("\n\r=====================================================\n\r"); 
for(i=0,nt=menus;i<NC;nt++,i++) 
if (nt->tsena>50 && strcmp(nt->vid,"Сразу")==0) 
printf("\n\r %-20s %ld р.",nt->name,nt->tsena); 
getch(); 
}
void slvpr(struct z *menus)
{

int n=0,NC;
FILE* in;
in=fopen("MENU.txt","r");
fscanf(in,"%d",&NC); 
Console::ForegroundColor=ConsoleColor::White; 
Console::BackgroundColor=ConsoleColor::Black;
Console::Clear();
printf("\n\r Список пунктов с равной ценой но разным временем подачи"); 
printf("\n\r=====================================================\n\r"); 
int i,j;
	for(int i=1 ;i<NC;i++)
	{if(n==1) break;
		for(int j=0;j<i;j++)
		{if(n==1) break;
		if (strcmp(menus[i].vid,menus[j].vid)==1)
		{
			if(menus[i].tsena==menus[j].tsena)
			{
				printf("%-20s %7ld %s \n",menus[i].name,menus[i].tsena,menus[i].vid);
				printf("%-20s %7ld %s \n",menus[j].name,menus[j].tsena,menus[j].vid);
				n=1;
			}
		}
}
	}

getch();
}
void diagram(struct z *menus) 
{ 
struct sp *nt; 
int len,i,NColor,k,il,NC; 
FILE* in;
in=fopen("MENU.txt","r");
fscanf(in,"%d",&NC); 
long sum = 0,kil ; 
float raschet;
char F[20];
char str1[20]; 
char str2[20]; 
System::ConsoleColor Color; 
Console::ForegroundColor=ConsoleColor::White; 
Console::BackgroundColor=ConsoleColor::Black; 
Console::Clear(); 
for(i=0;i<NC;i++) sum = sum+menus[i].kolva ; 

if(!spisok) 
for(i=0;i<NC;i++) 
vstavka(menus,menus[i].name); 
Color=ConsoleColor::Black; NColor=0; 

for(nt=spisok,i=0,k=0; nt!=0; nt=nt->sled,i++,k++) 
{sprintf(F,nt->punkt);
	for(il=0;i<NC;il++){
		if (strcmp(menus[il].name,F)==0){
			break;
		}
	}
kil=menus[il].kolva;
raschet=((kil*100.)/sum);
sprintf(str1,"%s",F); 
sprintf(str2,"%3.1f%%",raschet); 
Console::ForegroundColor=ConsoleColor::White; 
Console::BackgroundColor= ConsoleColor::Black; 
Console::CursorLeft=5; Console::CursorTop=i+1; 
printf(str1); 
Console::CursorLeft=20; 
printf("%s",str2);

Console::BackgroundColor=++Color; NColor++; 
Console::CursorLeft=30; 
for(len=0; raschet!=0, raschet>0; len++){
printf(" ");
raschet=raschet-1;
}
if(NColor==14) 
{ Color=ConsoleColor::Black; NColor=0; } 
} 
getch(); 
return ; 
}