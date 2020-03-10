sternhalma: main.cpp board.cpp
	g++ main.cpp board.cpp -o $@ -lncurses

clean:
	rm -rf sternhalma
