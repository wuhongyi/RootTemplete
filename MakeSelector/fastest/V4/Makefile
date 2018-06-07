OBJ = wu

CXX=g++        
CXXFLAGS:=-std=c++11 -g -Wall -lrt  -I. 
ROOTLIBS = $(shell root-config --libs) -lGui
ROOTINC = -I$(shell root-config --incdir) 
CXXFLAGS+=$(ROOTINC)
LIBS:=



INCLUDES:=DataClass.h UserClass.h

OBJECTS:=main.o Dict.o DataClass.o UserClass.o

SRCS:=main.cc Dict.cc DataClass.C UserClass.C

all: $(OBJ)


$(OBJ): $(SRCS) $(OBJECTS) $(INCLUDES)
	$(CXX) -o  $@  $(OBJECTS) $(CXXFLAGS) $(LIBS) $(ROOTLIBS)

%.o: %.cxx 
	$(CXX) $(CXXFLAGS) -c $< 
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<
%.o: %.C
	$(CXX) $(CXXFLAGS) -c $< 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< 
Dict.cc:DataClass.h UserClass.h Linkdef.h
	rootcint -f $@ -c $^


clean: 
	rm -f *.o *~ $(OBJ) *Dict*

very-clean:
	rm -f $(OBJ) *.o *~

.PHONY: clean very-clean
#.SILENT:
