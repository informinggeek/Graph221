CXX = g++ -std=c++11
OPTS = -g3 -O2
WARN = -Wall -Werror
DEPS = -MMD -MF $*.d
INCL =

OBJS = test_graph.o

default: $(OBJS)

docs:
	doxygen DoxygenSetup/doxyfile.prog04

clean:
	rm -rf Dependencies $(OBJS) timer.o

timer.o: timer.cpp timer.h
	$(CXX) $(OPTS) $(WARN) $(INCL) $< -c -o $@

%.o: %.cpp timer.o
	$(CXX) $(OPTS) $(WARN) $(DEPS) $(INCL) $^ -o $@
	cat $*.d >> Dependencies
	rm -f $*.d

-include Dependencies

