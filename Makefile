CC := cc
CFLAGS := -g -Wall -Wextra -lm -w#-ansi
CPPFLAGS := #-DDEBUG
LD := gcc
LDFLAGS := -g
LIBS :=

MAIN := implementacao_3.c
PROG := 3
OBJS := matrix.o cg.o
OUTPUT := *.dat

${PROG}: ${OBJS}
	${LD} ${LDFLAGS} ${MAIN} ${CFLAGS} -o ${PROG} ${OBJS} ${LIBS} -lm

clean:
	rm -f ${PROG} ${OBJS} ${OUTPUT}

.PHONY: clean
