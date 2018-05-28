#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "game.h"

using namespace std;

#define screenHeight 25
#define screenWidth 85
#define roadWidth 25

struct Coordinate{
	int x,y; // x,y la hoanh do, tung do
};

struct Shape{
	char a[3][3];
};

struct Object{
	Coordinate coord;
	Shape shape;
};

void Renderroad(){

	for(int i=0;i<screenHeight;i++){
		cout<<"||"<<endl;
	}
	for(int i=0;i<screenHeight;i++){
		gotoXY (roadWidth,i);
		cout<<"||";
	}
}
void Render1(Object &car){
	car.coord.y=screenHeight-2;
	car.coord.x=(roadWidth)/2+1;

	car.shape.a[0][0]=car.shape.a[0][2]=car.shape.a[2][0]=car.shape.a[2][2]='o';
	car.shape.a[0][1]=car.shape.a[2][1]='-';
	car.shape.a[1][0]=car.shape.a[1][2]='|';
	car.shape.a[1][1]='X';
}

void Render2(Object &obstacle){

	obstacle.coord.x=3+rand()%(roadWidth-4);
	obstacle.coord.y=-2;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			obstacle.shape.a[i][j]='F';
		}
	}
}

void Output(Object car,Object obstacle,int score){
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			int y=i+car.coord.y;
			int x=j+car.coord.x;
			gotoXY (x,y);
			cout<<car.shape.a[i+1][j+1];
		}
	}

	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			int y=i+obstacle.coord.y;
			int x=j+obstacle.coord.x;
			if(y>=0 && y<screenHeight){
			gotoXY (x,y);
			cout<<obstacle.shape.a[i+1][j+1];
			}
		}
	}

	gotoXY (roadWidth+5,screenHeight/2);
	cout<<"Your score: "<<score;
}

bool Process(Object &car,Object &obstacle,int &score){
    if ((abs(obstacle.coord.x-car.coord.x)<=2)&&(abs(obstacle.coord.y-car.coord.y)<=2)) return false;
    obstacle.coord.y++;
    if(obstacle.coord.y==screenHeight+2){
        score++;
        obstacle.coord.x=3+rand()%(roadWidth-4);
        obstacle.coord.y=-2;
    }
    return true;
}

void Control(Object &car){
	if(kbhit()){
		int key=_getch();
		if(key==75 && car.coord.x>=6) car.coord.x-=3; //cham bien trai
		else if(key==77 && car.coord.x<=roadWidth-5) car.coord.x+=3; //cham bien phai
        	else if(key==72 && car.coord.y>2) car.coord.y+=3;
        	else if(key==80 && car.coord.y<screenHeight-5) car.coord.y-=3;
	}
}

void GameOver(int score)
{
    Sleep(200);
    clrscr();

	gotoXY(10,10);
	cout<<"GAME OVER!!!";
	gotoXY(10,12);
	cout<<"Your score: "<<score;

	gotoXY(1,22);
}

int main(){
	Object car,obstacle;
	int score=0;
	srand(time(0));
	Render1(car);
	Render2(obstacle);
	while(1){
		clrscr();
		Renderroad();
		Output(car,obstacle,score);
		Control(car);
		if (Process(car,obstacle,score)==false) break;
		Sleep(50);
	}
	GameOver(score);
	return 0;
}
