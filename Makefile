Header_Dir=headers/
Library_Dir=sources/
Build_Dir=build/
Flags=-g -O3
Target=MarkP  Mark0 LRU LFU
Input=random_25_200_128
Cache=LFU
Error=0

.PHONY: build Replacementpolicies run clean
build: Replacementpolicies
	g++ -std=c++14 $(Flags) -I $(Header_Dir) -L$(Library_Dir) -o $(Build_Dir)/tester tester.cpp $(foreach v,$(Target), $(Build_Dir)$(v).o )
Replacementpolicies:
	$(foreach v,$(Target),g++ -std=c++14 $(Flags) -I $(Header_Dir) -c -o $(Build_Dir)$(v).o  $(Library_Dir)/$(v).cpp ; )	
run:
	./$(Build_Dir)/tester $(Input) $(Cache) $(Error) > log.txt
clean:
	rm -f build/*