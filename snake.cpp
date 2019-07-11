#include"snake.h"
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<iostream>
#include<string.h>
#include<windows.h>
#include<stdio.h>



#ifdef DEBUG
	char buf[1024] = "0";
#endif


struct pos{
	int x;
	int y;
};

enum direction{
	dir_up = 'w',
	dir_down = 's',
	dir_left = 'a',
	dir_right = 'd'
};


enum type_model{
	type_wall = 0,
	type_food = 1,
	type_left = 2,
	type_right = 3,
	type_up = 4,
	type_down = 5,
	type_self = 6,
	type_none = 7
};


snake_food::snake_food(){
	init();
}


void snake_food::random_food(){
	pFood_pos->x = 1+rand() % (ROW-1);
	pFood_pos->y = 1+rand() % (COL-1);
}


void snake_food::init(){
	printf(	"---------------------------------------------\n"
		"|					     |\n"
		"|		up is w,		     |\n"
		"|		donw is s,		     |\n"
		"|		left is a,		     |\n" 
		"|		right is d		     |\n"
		"|					     |\n"
		"---------------------------------------------\n");
	printf("请按任意键继续");
	//getchar();
	
	system("pause");
	delay_time = 40;
	for(int i = 0; i < ROW; ++i){
		for(int j = 0; j < COL; ++j){
			array[i][j] = type_none;
		}
	}
	run_flag = exit_flag = true;
	ac.store('w');
	kbhit_flag = true;
	pTail = new pos;
	pHead = new pos;
	pFood_pos = new pos;
	srand(time(0));
	pHead->x = 15;
	pHead->y = 40;
	pTail->x = 15;
	pTail->y = 40;
	#ifdef DEBUG
		std::cout<<buf<<std::endl;
		std::cout<<"pTail is:"<<pTail->x<<","<<pTail->y<<std::endl;
		std::cout<<"pHead is:"<<pHead->x<<","<<pHead->y<<std::endl;
		std::cout<<"array[phead] is:"<<array[pHead->x][pHead->y]<<std::endl;
		std::cout<<"atomic<char>"<<ac.load()<<std::endl;	
	#endif
	
	array[pHead->x][pHead->y] = type_up;
	array[pTail->x][pTail->y] = type_self;
	random_food();
	array[pFood_pos->x][pFood_pos->y] = type_food;
	for(int i = 0; i < COL; ++i){
		array[0][i] = type_wall;
		array[ROW-1][i] = type_wall;
	}
	for(int i = 0; i < ROW; ++i){
		array[i][0] = type_wall;
		array[i][COL - 1] = type_wall;
	}
	snake_length = 1;
	//vt.push_back(std::thread(change_direction, this));
	t = std::thread(change_direction, this);
	
}


bool snake_food::food_coll_dete(){
	return array[pHead->x][pHead->y] == type_food;
}

bool snake_food::self_coll_dete(){
	return  array[pHead->x][pHead->y] == type_self ||
			array[pHead->x][pHead->y] == type_up ||
			array[pHead->x][pHead->y] == type_down ||
			array[pHead->x][pHead->y] == type_right ||
			array[pHead->x][pHead->y] == type_left;
}
	
	
bool snake_food::board_coll_dete(){
	return array[pHead->x][pHead->y] == type_wall;
}
	
	
void snake_food::change_direction(){
	while(kbhit_flag){
		if(!kbhit())
			ac.store(getch());
	}
}


void snake_food::change_array(){
				
		change_head();
		if(board_coll_dete() || self_coll_dete()){
			#ifdef DEBUG
			if(board_coll_dete()){
				
				
				strcpy(buf, "from change_array board_coll_dete");
				
			}
			else{
				
				strcpy(buf, "from change_array self_coll_dete");
				
			}
			#endif
			exit_flag = false;
			
			return;
		}
		if(food_coll_dete()){
			snake_length += 1;
			do{
				random_food();
			}while(array[pFood_pos->x][pFood_pos->y] != type_none);
			array[pFood_pos->x][pFood_pos->y] = type_food;
		}
		else{
			change_tail();
		}
		array[pHead->x][pHead->y] = type_self;
	
}


snake_food::~snake_food(){
	t.join();
	
	#ifdef DEBUG
		std::cout<<buf<<std::endl;
		std::cout<<"pTail is:"<<pTail->x<<","<<pTail->y<<std::endl;
		std::cout<<"pHead is:"<<pHead->x<<","<<pHead->y<<std::endl;
		std::cout<<"array[phead] is:"<<array[pHead->x][pHead->y]<<std::endl;
		std::cout<<"atomic<char>"<<ac.load()<<std::endl;
		
		
	#endif
	delete pHead;
	delete pTail;
	delete pFood_pos;
	pHead = pTail = pFood_pos = nullptr;
	
	
	
}
	
	
	
void snake_food::show(){
	Sleep(delay_time);
	system("cls");
	for(int i = 0; i < ROW; ++i){
		for(int j = 0; j < COL; ++j){
			if(array[i][j] == type_wall){
				std::cout<<"#";
			}
			else if(array[i][j] == type_food){
				std::cout<<"*";
			}
			else if(array[i][j] == type_none){
				std::cout<<" ";
			}
			else{
				std::cout<<"+";
			}
		}
		std::cout<<std::endl;
	}
}
	
int snake_food::run(){
	while(exit_flag && run_flag){
		change_array();
		show();
		
	}
	if(!exit_flag){
		std::cout<<"you have failure!!"<<std::endl;
		kbhit_flag = false;
	}
	return exit_flag;
}	



void snake_food::change_tail(){
	switch (array[pTail->x][pTail->y])
	{
		case type_down:
			array[pTail->x][pTail->y] = type_none;
			pTail->x += 1;
			break;
		
		case type_up:
			array[pTail->x][pTail->y] = type_none;
			pTail->x -= 1;
			break;
		case type_left:
			array[pTail->x][pTail->y] = type_none;
			pTail->y -= 1;
			break;

		case type_right:
			array[pTail->x][pTail->y] = type_none;
			pTail->y += 1;
			break;
	}
}


void snake_food::change_head(){
	switch (tolower(ac.load()))
	{
		case dir_up:
			array[pHead->x][pHead->y] = type_up;
			pHead->x -= 1;
			
			break;
		
		case dir_down:
			array[pHead->x][pHead->y] = type_down;
			pHead->x += 1;
			break;

		case dir_left:
			array[pHead->x][pHead->y] = type_left;
			pHead->y -= 1;
			break;

		case dir_right:
			array[pHead->x][pHead->y] = type_right;
			pHead->y += 1;
			break;
	}
}
	
	
	
	
	
