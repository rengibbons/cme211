CXX := g++
CXXFLAGS := -O3 -Wall -Wconversion -Wextra -std=c++11

TARGET := main
OBJS := main.o CGSolver.o COO2CSR.o matvecops.o
INCS := CGSolver.hpp COO2CSR.hpp matvecops.hpp

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

%.o: %.cpp $(INCS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)