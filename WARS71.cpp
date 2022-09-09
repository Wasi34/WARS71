#include "iGraphics.h"
#include<stdio.h>
using namespace std;


int bdtank_x, bdtank_y;
int gamestate=0;

int f1=0;
int f1_x,f1_y;
char story[11][100]={"0.bmp","1.bmp","2.bmp","3.bmp","4.bmp","5.bmp","6.bmp","7.bmp","8.bmp","9.bmp","10.bmp"};
int explosion = 0;
int a=0;
bool musicOn = true;
#define ScreenHeight 540
#define ScreenWidth 1080
bool BDtankshow = 1;																			//BDtankshow
char cars[3][100] = {"pakt.bmp","pakt.bmp","pakt.bmp"};
#define CarNumber 3
int i = 0;																						//i is used for enemy tank
char road[3][100]= {"s1.bmp", "s2.bmp", "s3.bmp"};
int roadIndex = 0;
char burst[3][100]={"e1.bmp","e2.bmp","e3.bmp"};
int b=0;
int b1 = 0;
																		

//Bdtank fire
char fire[10][100] = {"bdbomb.bmp","bdbomb.bmp","bdbomb.bmp","bdbomb.bmp","bdbomb.bmp",
	"bdbomb.bmp","bdbomb.bmp","bdbomb.bmp","bdbomb.bmp","bdbomb.bmp"};

//pak tank fire

char pakfire[10][100] = {"bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp",
	"bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp","bomb1.bmp"};


int firecon[10]= {0};
int fireIndex = 0;
	

char life[7][100]={"healthbar1.bmp","healthbar2.bmp","healthbar3.bmp","healthbar4.bmp",
				"healthbar5.bmp","healthbar6.bmp","healthbar7.bmp"};


FILE *fp;																						//high score file
char name[20] = {}, point[10] = {};

char nameStr[20] = {}, nameStr2[20] = {};										
int nameLength = 0, nameMode = 0, thanks = 0;
int myScore = 0, myScoreCopy;
char myScoreText[10];

void score()
{
	sprintf_s(myScoreText, 10, "%d", myScore);
	iSetColor(255, 255, 0);
	iFilledRectangle(15,570, 150, 25);
	iSetColor(0, 0, 160);
	iText(20,470, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(80, 470, myScoreText, GLUT_BITMAP_TIMES_ROMAN_24);
	myScoreCopy = myScore;
}


void storyf()
{
	if(a<10)
	{
		a++;
	}
}


void burstf()																		//burst image shown
{
	b++;
	if (b>2)
	{
		b=0;
    }
}
void burst2f()
{
	bdtank_x = 300 + 1.5 * (rand() % 100) + rand() % 130,  bdtank_y=0;	//bdtank's position will be initialized after explosion
	
	explosion = 0;
}


//bdtank life 
int l=0;

void lifef()
{
	if( l<5 )
	{

		l++;
		
	}
	else if(l==5)
	{
		gamestate =5;
		
	}
}

// shooting code 
struct shoot{
	int shoot_x;
	int shoot_y;
	int fire_x;
	int fire_y;
	int bombShow;
};

struct shoot bomb[10];
int c=0;

void Fireshow()	    //Fire show for both BD and Pak tank
{
	for(int i=0;i<10;i++)
	{if (firecon[i]==i+1){


			iShowBMP2( bomb[i].shoot_x, bomb[i].shoot_y, fire[i], 0);	
			
			iShowBMP2( bomb[i].fire_x,  bomb[i].fire_y, pakfire[i], 0);
			
			bomb[i].shoot_y+=15;
			bomb[i].fire_y-=15;

	}
}
}
void Fire()			//BD fire function																
{
	if(firecon[c]==c)
	{
		bomb[c].shoot_x=bdtank_x+28;
		bomb[c].shoot_y=bdtank_y+65;

		firecon[c]=c+1;
		if(c == 9)
		{
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


struct car
{
	int car_x;
	int car_y;
	int carIndex;
	int carShow;
};

car enemy[CarNumber];


void EnemyMovement()
{
	if(gamestate == 1 && a==10)																	// if gamestate = 1 and a = 10 then tank will be shown 
	{
		for(int i=0; i< CarNumber;i++)
		{
			if(enemy[i].carShow)
			{
				iShowBMP2(enemy[i].car_x, enemy[i].car_y,cars[enemy[i].carIndex],0);					//enemy car is shown here

				if( ( (bdtank_x+72 >= enemy[i].car_x) && (bdtank_x <= enemy[i].car_x+72) &&				//if collision is done
					(enemy[i].car_y+100 >= bdtank_y) && (enemy[i].car_y <= bdtank_y+100) ) )
				{
					explosion = 1;
					lifef();
			
					iShowBMP2(enemy[i].car_x ,enemy[i].car_y,burst[b],0);
					enemy[i].car_x = 300 + 1.5 * (rand() % 100) + rand() % 130;
					enemy[i].car_y = enemy[i].car_y + 1000 + ScreenHeight + rand() % rand();
				}
				
			
					if( ( (bomb[i].shoot_x+10 >= enemy[i].car_x)  && (bomb[i].shoot_x <= enemy[i].car_x+72) &&
					(bomb[i].shoot_y+10 >= bdtank_y) && (bomb[i].shoot_y <= bdtank_y+70) )   ||
					    ( (bomb[i+1].shoot_x+10 >= enemy[i].car_x)  && (bomb[i+1].shoot_x <= enemy[i].car_x+72) &&
					(bomb[i+1].shoot_y+10 >= bdtank_y) && (bomb[i+1].shoot_y <= bdtank_y+70) )   ||
					    ( (bomb[i+2].shoot_x+10 >= enemy[i].car_x)  && (bomb[i+2].shoot_x <= enemy[i].car_x+72) &&
					(bomb[i+2].shoot_y+10 >= bdtank_y) && (bomb[i+2].shoot_y <= bdtank_y+70) )    )
					{
						explosion = 2;							//explosion 2 is for collision between a tank and bomb		
						iShowBMP2(enemy[i].car_x ,enemy[i].car_y,burst[b],0);
						
						if( bomb[i].shoot_y >= ScreenWidth )		//bomb's value will initilize after explosion
						{
							bomb[i].shoot_x = bdtank_x + 25;
							bomb[i].shoot_y = bdtank_y + 50;
						}
																	//line 1 nd 2
						enemy[i].car_y = ScreenHeight + rand() % 300  + rand() % 300;
																	//+ sign for sending the enemy backward and come again
					}

				}
			
			}
	}
}



void Fire2()	//pak fire function
{


if(firecon[c]==c)
{

	EnemyMovement();
	for(int i=0; i<CarNumber;i++)
	{
	bomb[c].fire_x=enemy[i].car_x+18;

	bomb[c].fire_y=enemy[i].car_y-10;

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
}









void setEnemyVariables()																	//road limit - 250 to 770
{
	if(i==0)
	{
		for(i=0; i<1;i++)																	//1st lane enemy tank
		{
			enemy[i].car_x = 80 + 3.5 * (rand() % 103) + rand() % 103 + (rand() % 103) ;
			//enemy[i].car_y = 1.5 * ScreenHeight + rand() % rand() * 1.5 ;
			enemy[i].car_y = ScreenHeight + rand() % 300  + rand() % 300;

			if(enemy[i].car_x > 300 && enemy[i].car_x < 550)
			{
				enemy[i].carShow = true;
			}
			enemy[i].carIndex = rand() % 10;
		}
	}
	if(i==1)
	{
		for( i=1; i<2;i++)																//2nd lane enemy tank
		{
		enemy[i].car_x = 330 + 2.5 * (rand() % 133) + rand() % 133 + (rand() % 123) ;
		//enemy[i].car_y = 1.5 * ScreenHeight + rand() % rand() * 1.5 ;
		enemy[i].car_y = ScreenHeight + rand() % 300  + rand() % 300;

		if(enemy[i].car_x > 360 && enemy[i].car_x < 650)
		{
			enemy[i].carShow = true;
		}
		enemy[i].carIndex = rand() % 10;
		}
	}
	if(i==2)
	{
		for( i=2; i<3;i++)												//3rd lane enemy tank
		{
			enemy[i].car_x = 520 + 2.3 * (rand() % 133) + rand() % 113 + (rand() % 123);
			//enemy[i].car_y = 1.5 * ScreenHeight + rand() % rand() * 1.5 ;
			enemy[i].car_y = ScreenHeight + rand() % 300  + rand() % 300;

			if(enemy[i].car_x > 500 && enemy[i].car_x < 770)
			{
				enemy[i].carShow = true;
			}
			//enemy[i].carShow = false;
			enemy[i].carIndex = rand() % 10;
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
			if(enemy[i].carIndex >= 3)
			{
				enemy[i].carIndex = 0;
			}
		}
	}
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
		if(a<9)
		{
		iText(0,525,"Press's'to skip full story,'d'to view next picture and 'a'to view previous picture");
		}
		if(a==10)
		{
			iShowBMP(200,0, road[roadIndex]);
			iShowBMP2( bdtank_x, bdtank_y, "bdt.bmp",0);

			iText(15,500,"BD Tank Life:" );

			iShowBMP(0,450,life[l]);
			
			Fireshow();
			if(f1==1)
			{
				
				Fire();
			}
			if(explosion == 1)																//explosion 1 is for collision between BD tank and pak tank
			{
				iShowBMP2(bdtank_x,bdtank_y,burst[b],0);									//explosion code here
				burstf();
				burst2f();
				explosion = 0;
																			//gameover
			}			
			if(explosion == 2)																//explosion 2 is for collision between a tank and bomb
			{
													//explosion code here
				burstf();
				explosion = 0;
																			
			}

		}
	}
	else if(gamestate == 2)
	{
	iShowBMP(0, 0,"highscorePage.bmp");
		iSetColor(255, 255, 255);
		//file
		int namePosition = 400;
		fp = fopen("Highscore file.txt","r");
		for(int i=0; i<5; i++)
		{
			namePosition -= 40;
			fscanf(fp, "%s %s", name, point);
			iText(200, namePosition, name, GLUT_BITMAP_TIMES_ROMAN_24);
			iText(500, namePosition, point, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		fclose(fp);
	}
	else if(gamestate == 3)
	{
		iShowBMP(0,0, "controls.bmp");
	}
	else if(gamestate == 4)
	{
		iShowBMP(0,0, "credits.bmp");
	}
	else if(gamestate == 5)
	{
		iShowBMP(0,0, "gameover.bmp");
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
	//printf( "%d %d\n", mx, my);
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
		else if(mx>=47   && mx<=172   && my >= 120   && my <= 140 )
		{
			exit(0);
		}
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
			PlaySound("Music\\Chol chol chol.wav",NULL, SND_LOOP | SND_ASYNC);
		}

		}
	if(key == 's')
	{
			a=10;
	}
	if(key == 'd')
	{ 
		if(a<10)
		{
			a++;
		}
	}


	if(key == 'a')
	{ 
		if(a>0 && a<10)
		{
			a--;
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
		}
	}
	if(key == GLUT_KEY_RIGHT)
	{
		if( bdtank_x <=770)
		{
			bdtank_x +=10;
		}
	}
	if(key == GLUT_KEY_UP)
	{
		if(bdtank_y <= 440)
		{
			bdtank_y += 10;
		}
	}
	if(key == GLUT_KEY_DOWN)
	{
		if(bdtank_y >= 10)
		{
			bdtank_y -= 10;

		}
	}
}

void musics()
{
	PlaySound("Music//Chol chol chol.wav",NULL, SND_LOOP | SND_ASYNC);
}

int main()
{
    bdtank_x=400;
    bdtank_y=0;
	f1_x = bdtank_x+35,f1_y = bdtank_y+50;										//bullet placing
	setEnemyVariables();
	iSetTimer(120,move);
	iSetTimer(1700,Fire2);
	if(musicOn)
	{
		musics();
	}

	iInitialize(ScreenWidth, ScreenHeight, "WARS71");
	iStart();
	return 0;
}

