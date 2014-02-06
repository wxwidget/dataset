CXX=g++
all: libsvmformat.a
clean:
	rm  libsvmformat.a

SRCS=$(wildcard *.cpp)
OBJ=$(SRCS:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

libsvmformat.a:$(OBJ)
	$(AR) rcs $@ $^ 
	rm $^


