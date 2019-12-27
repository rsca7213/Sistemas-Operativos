
all: timeprog ucp procmsg

timeprog: timeprog.c
	gcc -o timeprog timeprog.c

ucp: ucp.c
	gcc -o ucp ucp.c

procmsg: procmsg.c
	gcc -o procmsg procmsg.c

clean:
	rm timeprog ucp procmsg