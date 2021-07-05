CC = cc
CFLAGS = -D _GNU_SOURCE -Wall -std=c99

tarc: main.c tarc.c
	$(CC) $(CFLAGS) main.c tarc.c -o tarc

clean:
	rm -f foo.tar bar.tar foo.txt bar.txt main.o tarc.o 

run:
	make clean
	make tarc
	./tarc foo.tar $(dir)
	tar --format=ustar -cf bar.tar $(dir)
	od -c foo.tar > foo.txt
	od -c bar.tar > bar.txt
	diff foo.txt bar.txt
