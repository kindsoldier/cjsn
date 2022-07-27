
OBJS = stream.o jblock.o jkeyval.o jroot.o imalloc.o strtool.o mapper.o

all: parser test

parser: parser.o $(OBJS)
	$(CC) -Wall -o $@ $< $(OBJS)

.c.o:
	$(CC) -c -Wall -o $@ $<

stream.c: stream.h
stream.o: stream.c

imalloc.c: imalloc.h
imalloc.o: imalloc.c

jroot.c: jroot.h jcommon.h jblock.h
jroot.o: jroot.c

jblock.c: jblock.h
jblock.o: jblock.c

jkeyval.c: jkeyval.h jcommon.h
jkeyval.o: jkeyval.c

strtool.c: strtool.h
strtool.o: strtool.c

mapper.c: mapper.h
mapper.o: mapper.c


test: strtool_test
		env ./$<

strtool_test: strtool_test.o strtool.o
	$(CC) -Wall -o $@ $< $(OBJS)


strtool_test.o: strtool_test.c


clean:
	rm -f parser
	rm -f strtool_test
	rm -f *.o *~
