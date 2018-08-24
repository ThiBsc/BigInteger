CCOPTS=-Wall -std=c++11 -O2
OBJS=biginteger.o
CXX=g++

bint: $(OBJS) main.cpp
	$(CXX) $(CCOPTS) -o $@ main.cpp $(OBJS)

%.o: %.cpp
	$(CXX) $(CCOPTS) -c -MMD $<

clean:
	rm -f *.o
	rm -f *.d

-include *.d
