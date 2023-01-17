SRC = ${wildcard *.cpp}
OBJECTS = ${SRC:.cpp=.o}
HEADERS = ${../inc/*.h}

BUILD_DIR = ../build/
BIN_DIR	= ../bin/
ALTAIR_DEBUG_LIB = ../altair_debug/lib/altair_debug.a

CC = g++
CFLAGS += -Wall -I../inc -I../baedb/ -I../altair_debug/inc/
LDFLAGS += -lpq -lconfig
LDFLAGS += ${ALTAIR_DEBUG_LIB}

all: ${TARGET} Makefile

${TARGET}: ${OBJECTS} Makefile
	mkdir -p ${BIN_DIR}
	${CC} $(addprefix ${BUILD_DIR}, ${OBJECTS}) ${LDFLAGS} -o ${BIN_DIR}${TARGET}

%.o: %.cpp ${HEADERS} Makefile
	mkdir -p ${BUILD_DIR}
	${CC} -c ${CFLAGS} $< -o ${BUILD_DIR}$@

clean:
	rm -rf ${BUILD_DIR} ${BIN_DIR}

.PHONY: all clean
