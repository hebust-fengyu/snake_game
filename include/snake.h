

#pragma once
#include<atomic>
#include<vector>
#include<thread>


#define COL 79
#define ROW 24

struct pos;


class snake_food{
	
	// func
	public:
		int run();
		snake_food();
		~snake_food();
		
		
	private:
		bool food_coll_dete();
		bool self_coll_dete();
		bool board_coll_dete();
		void change_array();
		void change_direction();
		void show();
		void init();
		void random_food();
		void change_tail();
		void change_head();
		
		
	// mem
	private:
		struct pos *pHead, *pTail, *pFood_pos;
		int array[ROW][COL];
		int snake_length;
		std::atomic<char> ac;
		bool food_coll_dete_flag, self_coll_dete_flag, exit_flag, run_flag;
		bool kbhit_flag;
		std::thread t;
		
		int delay_time;
		

};
		
	