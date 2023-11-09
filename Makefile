CXX?=clang++
INCS=
LIBS=-lm

CXXFLAGS=-g -Og $(INCS) -std=c++20
LDFLAGS=$(LIBS)

SRC=sss.cpp algebra.cpp secret.cpp
HEADER=algebra.hpp secret.hpp
OBJ=$(SRC:.cpp=.o)

all: sss

%.cpp.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

$(OBJ): $(HEADER)

sss: $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ) sss
