//214984932 Oriyas.07@gmail.com
#!make -f

CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion -ggdb
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

run: demo
	./$^

demo: Demo.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) $^ -o demo

test: $(OBJECTS) testMain.o
	$(CXX) $(CXXFLAGS) $^ -o test

testCounter: TestCounter.o 
		$(CXX) $(CXXFLAGS) $^ -o testCounter

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

testMain.o: testMain.cpp Test.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@
clean:
	rm -f *.o demo test
