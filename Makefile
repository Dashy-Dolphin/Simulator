Header_Dir=/home/sasi/Desktop/CS6170\ Rando/Proj/Simulator/headers
Library_Dir=/home/sasi/Desktop/CS6170\ Rando/Proj/Simulator/sources
Flags=-g -O3
Target=LFU
build:
	g++ -std=c++14 $(Flags) -I $(Header_Dir) -c -o $(Target).o  $(Library_Dir)/$(Target).cpp
	g++ -std=c++14 $(Flags) -I $(Header_Dir) -L$(Library_Dir) -o tester tester.cpp $(Target).o
run:
	./tester
clean:
	rm -f tester *.o