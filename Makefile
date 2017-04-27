all: main

new: clean all run

clean: delete main
	rm *.o

delete:
	rm *.o

run: main
	./FatTree

main: main.o root.o commandList.o children.o basic.o
	g++ main.o root.o commandList.o children.o basic.o -o FatTree

main.o: main.cpp
	g++ -c main.cpp

root.o: root.cpp root.h
	g++ -c root.cpp

commandList.o: commandList.cpp commandList.h
	g++ -c commandList.cpp

children.o: children.cpp children.h
	g++ -c children.cpp

basic.o: basic.cpp basic.h
	g++ -c basic.cpp