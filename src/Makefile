CFLAGS += -g


.PHONY: target
target: kitasuna

objs := main.o ylinkedlist.o yarraylist.o ycommon.o

kitasuna: ${objs}
	${CC} -o $@ ${CFLAGS} $^


.SUFFIXES: .c

.c.o:
	${CC} -c ${CFLAGS} $<

.PHONY: clean
clean:
	rm -rf $(objs)
