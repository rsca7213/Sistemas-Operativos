
all: timeprog ucp procmsg FibMulti FibSecuencial

timeprog: timeprog.c
	gcc -o timeprog timeprog.c

ucp: ucp.c
	gcc -o ucp ucp.c

procmsg: procmsg.c
	gcc -o procmsg procmsg.c

FibMulti: FibMulti.c
	gcc -o FibMulti FibMulti.c -lpthread -lm

FibSecuencial: FibSecuencial.c
	gcc -o FibSecuencial FibSecuencial.c -lm

clean:
	rm timeprog ucp procmsg FibSecuencial FibMulti