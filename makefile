
obj = snake.cpp 


dynamic_release:
	g++ main.cpp -lsnake -Iinclude  -o main.exe -L ./ -std=c++11

release:
	g++ main.cpp -I include $(obj) -Wall -o main.exe -std=c++11
	
debug:
	g++ main.cpp -I include $(obj) -Wall -o main.exe -std=c++11 -g -DDEBUG
	

dll: snake.o
	g++ -std=c++11 -shared snake.o -o snake.dll


snake.o: snake.cpp
	g++ -std=c++11 -fPIC -c $(obj) -o snake.o -I include

	
cls:
	del *.exe


