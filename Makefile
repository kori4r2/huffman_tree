CFLAGS = -g -Wall

all:
	gcc $(CFLAGS) -o program *.c -I./

clean:
	rm -f program
	clear

run:
	./program

.zip:
	zip huffman_tree.zip *.c *.h Makefile

debug: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < 2.in > test2.out
	diff test2.out 2.out
	#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program < 5.in > test5.out
	#diff test5.out 5.out

