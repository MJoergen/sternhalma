sternhalma: main.cpp board.cpp ai.cpp
	g++ $^ -o $@ -lncurses

clean:
	rm -rf sternhalma
