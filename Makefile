
OBJS = stream.o jblock.o jkeyval.o jroot.o imalloc.o strtool.o mapper.o
SRC = stream.c jblock.c jkeyval.c jroot.c imalloc.c strtool.c mapper.c

all: test


.c.o:
	$(CC) -c -Wall -o $@ $<

stream.c: stream.h
stream.o: stream.c $(SRC)

imalloc.c: imalloc.h
imalloc.o: imalloc.c $(SRC)

jroot.c: jroot.h jcommon.h jblock.h
jroot.o: jroot.c $(SRC)

jblock.c: jblock.h
jblock.o: jblock.c $(SRC)

jkeyval.c: jkeyval.h jcommon.h
jkeyval.o: jkeyval.c $(SRC)

strtool.c: strtool.h
strtool.o: strtool.c $(SRC)

mapper.c: mapper.h
mapper.o: mapper.c $(SRC)

strtool_test.o: strtool_test.c
parser_test.o: parser_test.c $(SRC)

test: strtool_test parser_test
		env ./strtool_test
		env ./parser_test


strtool_test: strtool_test.o $(OBJS)
	$(CC) -Wall -o $@ $< $(OBJS)

parser_test: parser_test.o $(OBJS)
	$(CC) -Wall -o $@ $< $(OBJS)


clean:
	rm -f parser_test
	rm -f strtool_test
	rm -f *.o *~
