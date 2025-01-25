project: llist user_interface
	g++ -o project user_interface.o llist.o

user_interface: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall -c user_interface.cpp

llist: llist.cpp
	g++ -ansi -pedantic-errors -Wall -c llist.cpp
