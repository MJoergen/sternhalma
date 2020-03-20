OPTIONS=-DENABLE_TRACE -O3

sternhalma: main.cpp board.cpp ai.cpp trace.cpp
	g++ $(OPTIONS) $^ -o $@ -lncurses

clean:
	rm -rf sternhalma
