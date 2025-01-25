project_debug: user_interface llist
	g++ -DDEBUG -o project_debug user_interface.o llist.o
user_interface: user_interface.cpp
	g++ -DDEBUG -ansi -pedantic-errors -Wall -c user_interface.cpp
llist: llist.cpp
	g++ -DDEBUG -ansi -pedantic-errors -Wall -c llist.cpp
