#include "iGraphics.h"
#include<stdio.h>
using namespace std;

int bdtank_x, bdtank_y;
int gamestate=0;
int i1,i2,i3;
int f1=0;
int f1_x,f1_y;
char story[11][100]={"0.bmp","1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp","8.bmp","9.bmp","10.bmp"};
int explosion = 0;
int a=0;
bool musicOn = true;
#define CarNumber 6
#define ScreenHeight 540
#define ScreenWidth 1080
bool BDtankshow = 1;											//BDtankshow,  still working
char cars[10][20] = {"pakt.bmp","pakt.bmp","pakt.bmp","pakt.bmp","pakt.bmp","pakt.bmp","pakt.bmp","pakt.bmp","pakt.bmp","pakt.bmp"};

char road[3][100]= {"s1.bmp", "s2.bmp", "s3.bmp"};
int roadIndex = 0;
char burst[3][100]={"e1.bmp","e2.bmp","e3.bmp"};
int b=0;
int b1 = 0;
char fire[10][100] = {"bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp",
	"bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp"};
int firecon[10]= {0};

//high score file	
FILE *fp;
char name[20] = {}, point[10] = {};


//high score name input
char nameStr[20] = {}, nameStr2[20] = {};
int nameLength = 0, nameMode = 0, thanks = 0;

//still working
int fireIndex = 0;

struct car
{
	int car_x;
	int car_y;
	int carIndex;
	int carShow;
};

car enemy[CarNumber];
void burstf()																		//burst
{
	b++;
	if (b>2)        //An Explosion will be shown
	{
		b=0;
    }
}
void burst2f(){

	burstf();

	bdtank_x = 300 + 5 * (rand() % 100) + rand() % 130,  bdtank_y=0;					//tank's position will be initialized after explosion
	BDtankshow = 1;
	explosion = 0;


}
struct fire
{
	int fire_x;
	int fire_y;
};


struct shoot{
	int shoot_x;
	int shoot_y;

};


struct shoot bomb[10];



void EnemyMovement()
{
	if(gamestate == 1 && a==10)																/* if gamestate == 1 then tank will be shown */
	{
		for(int i=0; i< CarNumber;i++)
		{
			if(enemy[i].carShow)
			{
				iShowBMP2(enemy[i].car_x, enemy[i].car_y,cars[enemy[i].carIndex],0) ;
			}
			if( ( (bdtank_x+72 >= enemy[i].car_x) && (bdtank_x <= enemy[i].car_x+72) &&
					(enemy[i].car_y+100 >= bdtank_y) && (enemy[i].car_y <= bdtank_y+100) )   )
				{
					burstf();												//burst
					explosion = 1;
					BDtankshow =0;
					
					
				}
		}
	}
}


void move(){
	roadIndex++;
	if( roadIndex>=2)
	{
		roadIndex=0;
	}

	if(gamestate == 1)
	{
		for(int i=0;i<CarNumber;i++)
		{
			enemy[i].car_y -= 10;									//car speed
			if(enemy[i].car_y <= 0)
			{
				enemy[i].car_y = ScreenHeight + rand() % 300  + rand() % 300;
			}
			enemy[i].carIndex++;
			if(enemy[i].carIndex >= 10)
			{
				enemy[i].carIndex = 0;
			}
		}
	}
}
 void storyf()
{
	if(a<10)
	{
		a++;
	}
}

void setEnemyVariables()
{
	for(int i=0; i< CarNumber;i++)
	{
		enemy[i].car_y = ScreenHeight + rand() % rand() ;
		enemy[i].car_x = 300 + 5 * (rand() % 100) + rand() % 130;
		if(enemy[i].car_x>770)
		{
			enemy[i].car_x = 300 + 5* (rand() % 100 + rand() % 130);
		}
		enemy[i].carIndex = rand() % 10;
		enemy[i].carShow = true;
	}
}

int c=0;
void Fireshow()	
{

	for(int i=0;i<10;i++)
	{
		if (firecon[i]==i+1){

			
			iShowBMP2( bomb[i].shoot_x,bomb[i].shoot_y, fire[i],0);							 //fire function
			bomb[i].shoot_y++;

		}


}
}

void Fire()						//fire function
{

if(firecon[c]==c)
{
	bomb[c].shoot_x=bdtank_x+15;

	bomb[c].shoot_y=bdtank_y+50;

	firecon[c]=c+1;
	if(c==9){

		firecon[0]=0;
		c=0;
	}
	else 
	{
	firecon[c+1]=c+1;
	c++;

	}
	
}
}


//score
int myScore = 0, myScoreCopy;
char myScoreText[10];
void score()
{
	sprintf_s( myScoreText, 10, "%d", myScore );
	iSetColor(255, 255, 0);
	iFilledRectangle(15,570, 150, 25);
	iSetColor(0, 0, 160);
	iText(20,470, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(80, 470, myScoreText, GLUT_BITMAP_TIMES_ROMAN_24);
	myScoreCopy = myScore;
}






void iDraw()
{
	//place your drawing codes here
	iClear();

	if(gamestate==0)
	{
		iShowBMP(0,0, "menu.bmp" );
	
	}
	else if(gamestate == 1)
	{
		
		iShowBMP(200,0,story[a]);
		if(a==10)
		{
			score();
			iShowBMP(200,0, road[roadIndex]);
			iShowBMP2( bdtank_x, bdtank_y, "bdt.bmp",0);
			
			Fireshow();
			if(f1==1)
			{
				//iShowBMP2(f1_x, f1_y,"bomb1.bmp",0);
				Fire();
			}
			if(explosion == 1)
			{
				iShowBMP2(bdtank_x,bdtank_y,burst[b],0);      //explosion code here
				BDtankshow = 0;
				burst2f();
				BDtankshow = 1;
				explosion = 0;
				//BDtankshow = false;
				//gamestate = 4;
				
			}
			
		}

	}
	else if(gamestate == 2)
	{
	iShowBMP(0, 0,"highscorePage.bmp");
		iSetColor(255, 255, 255);
		//file
		/*int namePosition = 400;
		fp = fopen("Highscore file.txt","r");
		for(int i=0; i<5; i++)
		{
			namePosition -= 40;
			fscanf(fp, "%s %s", name, point);
			iText(200, namePosition, name, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(500, namePosition, point, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		fclose(fp);*/
	}
	else if(gamestate == 3)
	{
		iShowBMP(0,0, "control.bmp");
	}
	else if(gamestate == 4)
	{
		iShowBMP(0,0, "credit.bmp");
	}

	EnemyMovement();

}

void iMouseMove(int mx, int my)
{
	//place your codes here
}
void iPassiveMouse(int mx, int my)
{
	//place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
	printf( "%d %d\n", mx, my);
	if( gamestate==0)
	{
		if(mx >=38 && mx <=185 && my >=340 && my <= 385)
		{
			gamestate=1;
		}
		else if(mx >=38&& mx <= 172 && my>=283 && my <=323)
		{
			gamestate=2;
		}
		else if(mx >=37 && mx <= 188 && my>=231 && my <=271)
		{
			gamestate=3;
		}
		else if(mx>=38 && mx<= 183 && my >= 173 && my <= 213)
		{
			gamestate=4;
		}
		/*else if(mx>=47   && mx<=172   && my >= 120   && my <= 140 )
		{
			exit();
		}*/
	}
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}


void iKeyboard(unsigned char key)
{
	if(key == 'x')
	{
		gamestate = 0;
	}
	if(key == 'p')
	{
		iPauseTimer(0);
	}
	if(key == 'r')
	{
		iResumeTimer(0);
	}
	if(key == 'f')
	{
		Fire();	
		//f1 = 1;
	}
	if(key == 'm')
	{
		if(musicOn)
		{
			musicOn = false;
			PlaySound(0,0,0);
		}
		else
		{
			musicOn = true;
			//PlaySound("Music\\Chol chol chol.wav",NULL, SND_LOOP | SND_ASYNC);
		}

		}
	if(key == 's')
	{
			a=10;
	}
	if(key == 'd')
	{ 
		if(a<10){
			a++;

	}


	}

}
void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	if(key == GLUT_KEY_LEFT)
	{
		if(bdtank_x >= 250)
		{
			bdtank_x -= 10;
			if(f1 != 1)										//still working
			{ f1_x -=10; }
		}
	}
	if(key == GLUT_KEY_RIGHT)
	{
		if( bdtank_x <=770)
		{
			bdtank_x +=10;
			if(f1 != 1)										//still working
			f1_x+= 10;
		}
	}
	if(key == GLUT_KEY_UP)
	{
		if(bdtank_y <= 440)
		{
			bdtank_y += 10;
			if(f1 != 1)										//still working
			f1_y += 10;
		}
	}
	if(key == GLUT_KEY_DOWN)
	{
		if(bdtank_y >= 10)
		{
			bdtank_y -= 10;
			if(f1 != 1)										//still working
			f1_y -= 10;
		}
	}
}

void musics()
{
	//PlaySound("Music//Chol chol chol.wav",NULL, SND_LOOP | SND_ASYNC);
}

int main()
{
    bdtank_x=400;
    bdtank_y=0;
	f1_x = bdtank_x+15,f1_y = bdtank_y+50; //bullet placing
	
	setEnemyVariables();
	iSetTimer(200,move);
//	iSetTimer(4800,storyf);
	if(musicOn)
	{
		musics();
	}

	iInitialize(ScreenWidth, ScreenHeight, "WARS71");
	iStart();
	return 0;
}

