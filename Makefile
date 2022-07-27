
OBJS = stream.o jblock.o jkeyval.o jroot.o imalloc.o

all: parser

parser: parser.o $(OBJS)
	$(CC) -Wall -o $@ $< $(OBJS)

.c.o:
	$(CC) -c -Wall -o $@ $<

stream.c: stream.h
stream.o: stream.c

imalloc.c: imalloc.h
imalloc.o: imalloc.c

jroot.c: jroot.h jcommon.h
jroot.o: jroot.c

jblock.c: jblock.h
jblock.o: jblock.c

jkeyval.c: jkeyval.h jcommon.h
jkeyval.o: jkeyval.c


clean:
	rm -f *.o *~
