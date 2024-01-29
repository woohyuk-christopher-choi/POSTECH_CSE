CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic

all: assn3.exe

assn3.exe: main.o artist.o drawer.o parser.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cpp artist.hpp drawer.hpp parser.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

artist.o: artist.cpp artist.hpp drawer.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

drawer.o: drawer.cpp drawer.hpp artist.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

parser.o: parser.cpp parser.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: assn3.exe
	./assn3.exe $(INPUTFILE) $(CONFIGFILE) $(OUTPUTFILE)

clean:
	rm -f *.o assn3.exe
