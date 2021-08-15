# Define Macros
CXX = g++
IFLAGS = -I../include
CXXFLAGS = -Wall -std=c++17 -Wextra -fopenmp
DBFLAGS = -g -O0

DEPS = hellomake.h
# OBJ = hellomake.o hellofunc.o 

# Target: Dependences
# <TAB>Command
# special macros $@ (target) and $^(dependence), 
# which are the left and right sides of the :, respectively
# $<: is the first item in the pre list

# %.o: %.cpp $(DEPS) 
# question 1: why $(DEPS) is not necessary?
# question 2: why I use %.out : $(OBJ) will remove object files automatically 
%.out: %.cpp 
	$(CXX) -o $@ $^ $(IFLAGS) $(CXXFLAGS)

# %.o: %.cpp 
# 	$(CXX) -c -o $@ $< $(IFLAGS)


%.db: %.cpp
	$(CXX) -o $@ $< $(IFLAGS) $(CXXFLAGS) $(DBFLAGS)

.PHONY: clean
clean:
	rm -f *.o