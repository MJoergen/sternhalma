OPTIONS=-DENABLE_TRACE

sternhalma: main.cpp board.cpp ai.cpp trace.cpp
	g++ $(OPTIONS) $^ -o $@ -lncurses

clean:
	rm -rf sternhalma
