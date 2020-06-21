PHONY: all doc clean compile run
.DEFAULT_GOAL := all

USERNAME=florilad
TESTEXEC=tests
CXX=g++
CXXFLAGS = -std=c++17 -O0 -Wall -Werror -pedantic -g
LDLIBS = -pthread -lstdc++fs
SOURCES=$(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp)
TESTS=$(wildcard examples/tests/*.cpp examples/tests/*/*.cpp)

%.o: %.cpp,%.hpp
	${CXX} ${CXXFLAGS} -c -o $*.o $*.cpp

all: doc compile

doc: Doxyfile
	mkdir -p doc
	doxygen Doxyfile
	ln -s html/index.html doc/index.html

clean: cleanTests
	@echo "Cleaning..."
	@rm -rf -- src/*.o src/*/*.o src/*/*/*.o src/*/*/*/*.o
	@rm -rf -- src/*.d src/*/*.d src/*/*/*.d src/*/*/*/*.d
	@rm -rf $(USERNAME)
	@rm -rf doc

cleanTests:
	@echo "Cleaning tests..."
	@rm -rf -- examples/tests/*.o examples/tests/*/*.o
	@rm -rf -- examples/tests/*.d examples/tests/*/*.d
	@rm -rf $(TESTEXEC)

compile: $(SOURCES:.cpp=.o)
	@echo "Compiling ..."
	${CXX} ${CXXFLAGS} -o ${USERNAME} ${SOURCES:.cpp=.o} ${LDLIBS}

compileTests: $(TESTS:.cpp=.o)
	@echo "Compiling tests..."
	${CXX} ${CXXFLAGS} -o ${TESTEXEC} ${TESTS:.cpp=.o} ${LDLIBS}

run: compile
	@./$(USERNAME)

runTests: compile compileTests
	@./$(USERNAME) & ./$(TESTEXEC)