TARGET = asp

SRC = ${wildcard *.cpp}
OBJECTS = ${SRC:.cpp=.o}
HEADERS = ${../inc/*.h}

CGIDIR ?= /usr/local/ea/altair/cgi

CC = g++
CFLAGS += -Wall -I../baedb/
LDFLAGS += -lpq -ljson -lconfig

all: ${TARGET} Makefile

${TARGET}: ${OBJECTS} Makefile
	${CC} ${OBJECTS} ${LDFLAGS} -o ${TARGET}

%.o: %.cpp ${HEADERS} Makefile
	${CC} -c ${CFLAGS} $< -o $@

clean:
	rm -rf ${OBJECTS} ${TARGET}
	
install:
	mkdir -p ${CGIDIR}
	cp -d  ${TARGET} ${CGIDIR}/${TARGET}.cgi

uninstall:
	rm -f ${CGIDIR}/${TARGET}.cgi
	
.PHONY: all clean install uninstall