GCC = /usr/bin/gcc

# Compiler Flags
CFLAGS = -c

# Linker Flags
LFLAGS = -o

# Warning Flags
FCFLAGS = -Wall

# Remove Flags
RFLAGS = -f

# Object files
OBJS = main.o Ex_7_1.o

all: upper lower

upper: ${OBJS}
	${GCC} ${FCFLAGS} ${OBJS} ${LFLAGS} upper

lower: ${OBJS}
	${GCC} ${FCFLAGS} ${OBJS} ${LFLAGS} lower

main.o: main.c Ex_7_1.h
	${GCC} ${CFLAGS} main.c

Ex_7_1.o: Ex_7_1.c Ex_7_1.h
	${GCC} ${CFLAGS} Ex_7_1.c

clean:
	rm ${RFLAGS} ${OBJS} lower upper
