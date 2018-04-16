SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,${SOURCES})
main:${OBJS}
	gcc $^ -o $@

clean:
	rm main ${OBJS}
