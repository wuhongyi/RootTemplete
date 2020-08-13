
flag = -std=c++11

readvector: UserClass.hh UserClass.cc main.cc LinkDict.cc
		g++ $(shell root-config --libs --cflags) $(flag) $^ -o $@

LinkDict.cc : UserClass.hh Linkdef.h
		rootcint -f LinkDict.cc -c $^

clean:
		rm -rf readvector *Dict*
