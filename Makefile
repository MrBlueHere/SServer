PHONY: all doc clean compile run
.DEFAULT_GOAL := all

USERNAME=florilad
CXX=g++
CXXFLAGS = -std=c++17 -O0 -Wall -Werror -pedantic -g
LDLIBS = -pthread -lstdc++fs
SOURCES=$(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp)

%.o: %.cpp,%.hpp
	${CXX} ${CXXFLAGS} -c -o $*.o $*.cpp

all: doc compile

doc: Doxyfile
	mkdir -p doc
	doxygen Doxyfile
	ln -s html/index.html doc/index.html

clean:
	@echo "Cleaning..."
	@rm -rf -- src/*.o src/*/*.o src/*/*/*.o src/*/*/*/*.o
	@rm -rf -- src/*.d src/*/*.d src/*/*/*.d src/*/*/*/*.d
	@rm -rf $(USERNAME)
	@rm -rf doc

compile: $(SOURCES:.cpp=.o)
	@echo "Compiling ..."
	${CXX} ${CXXFLAGS} -o ${USERNAME} ${SOURCES:.cpp=.o} ${LDLIBS}

run: compile
	@./$(USERNAME)