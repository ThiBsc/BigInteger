CCOPTS=-Wall -std=c++11 -O2
SRC=src
BDIR=build
OBJS=$(BDIR)/biginteger.o
CXX=g++

bint: $(BDIR) $(OBJS) $(SRC)/main.cpp
	$(CXX) $(CCOPTS) -o $(BDIR)/$@ $(SRC)/main.cpp $(OBJS)

$(BDIR)/%.o: $(SRC)/%.cpp
	$(CXX) $(CCOPTS) -o $@ -c -MMD $<

$(BDIR):
	mkdir build

clean:
	rm -f $(BDIR)/*.o
	rm -f $(BDIR)/*.d

-include $(BDIR)/*.d
