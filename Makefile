CXX = g++ 
CXXFLAGS = -g -O2 -std=c++17

all: oscillGrowth playground

oscillGrowth: oscillGrowth.o growthFunctions.o
	$(CXX) $(CXXFLAGS) -o oscillGrowth.exe oscillGrowth.o growthFunctions.o

playground: playground.o growthFunctions.o
	$(CXX) $(CXXFLAGS) -o playground.exe playground.cpp growthFunctions.o

oscillGrowth.o: oscillGrowth.cpp growthFunctions.h
	$(CXX) $(CXXFLAGS) -c oscillGrowth.cpp

growthFunctions.o: growthFunctions.h

playground.o: playground.cpp growthFunctions.h
	$(CXX) $(CXXFLAGS) -c playground.cpp

clean:
	rm oscillGrowth.o growthFunctions.o playground.o playground.exe oscillGrowth.exe