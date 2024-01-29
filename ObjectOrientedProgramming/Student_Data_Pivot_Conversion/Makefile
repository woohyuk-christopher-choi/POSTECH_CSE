CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = 

SRCS = Assign2_20210236.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = Assign2_20210236.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
