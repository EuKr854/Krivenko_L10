CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

LIB_NAME = graph

all: libgraph.dll test_graph.exe

libgraph.dll:
	$(CC) $(CFLAGS) -shared -o libgraph.dll src/graph.c

test_graph.exe:
	$(CC) $(CFLAGS) tests/test_graph.c -L. -lgraph -o test_graph.exe

clean:
	del /Q *.exe *.dll *.o 2>nul

syntax:
	gcc -Wall -Wextra -Wpedantic -fsyntax-only src/graph.c

analyze:
	gcc -Wall -Wextra -Wpedantic -fanalyzer -c src/graph.c

sanitize:
	gcc -Wall -Wextra -fsanitize=address,undefined -Iinclude src/graph.c tests/test_graph.c -o sanitize_test.exe
	sanitize_test.exe