CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

all:
	$(CC) $(CFLAGS) src/graph.c tests/test_graph.c -o test_graph.exe

clean:
	del /Q test_graph.exe 2>nul