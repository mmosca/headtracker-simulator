# vim:tabstop=8:shiftwidth=8:noexpandtab
# vim:ft=make:
CFLAGS:= -Wall -Werror -O3 -g

BINARIES:= msp-headtracker

all: $(BINARIES)

msp-headtracker: main.o crc.o msp-headtracker.o
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^

clean:
	$(RM) $(BINARIES) *.o *~

