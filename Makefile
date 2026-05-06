
CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Iinclude

TARGET = experiment
SRCS   = src/main.cpp src/matrix.cpp src/multiply.cpp src/benchmark.cpp
OBJS   = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	mkdir -p data plots
	./$(TARGET) > data/resultados.dat
	cd plots && gnuplot matmul_analysis.gp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
