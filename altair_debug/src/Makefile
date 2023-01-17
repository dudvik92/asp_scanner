LIBNAME = altair_debug

BUILD_DIR = ../build/
LIB_DIR = ../lib/

SRC = ${wildcard *.cpp}
OBJS = ${SRC:.cpp=.o}

CFLAGS = -Wall -I../inc

CC = g++

clean:
	rm -rf ${OBJS} lib/${LIBNAME}.a

release: dirs ${OBJS} static

all: release

dirs:
	mkdir -p ${BUILD_DIR}
	mkdir -p ${LIB_DIR}

%.o : %.cpp ${HEADERS} Makefile
	${CC} -c ${CFLAGS} $< -o ${BUILD_DIR}$@

static: ${OBJS}
	ar cr ${LIB_DIR}${LIBNAME}.a ${BUILD_DIR}${OBJS}

.PHONY: all clean static debug release