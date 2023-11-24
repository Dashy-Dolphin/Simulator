Header_Dir=/home/sasi/Desktop/CS6170\ Rando/Proj/Simulator/headers
Library_Dir=/home/sasi/Desktop/CS6170\ Rando/Proj/Simulator/sources
Flags=-g -O3
Target=MarkP  Mark0 LRU LFU
Input=normal_3.txt

.PHONY: build Replacementpolicies run clean
build: Replacementpolicies
	g++ -std=c++14 $(Flags) -I $(Header_Dir) -L$(Library_Dir) -o tester tester.cpp $(foreach v,$(Target), $(v).o )
Replacementpolicies:
	echo "asdf"
	$(foreach v,$(Target),g++ -std=c++14 $(Flags) -I $(Header_Dir) -c -o $(v).o  $(Library_Dir)/$(v).cpp ;)
	
run:
	./tester $(Input)
clean:
	rm -f tester *.o