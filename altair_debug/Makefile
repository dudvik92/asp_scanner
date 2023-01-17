export CFLAGS

all: release 

release: CFLAGS += -g -O2
release: src
	
src:
	${MAKE} -C ./src all
	
clean: 
	${MAKE} -C ./src $@

.PHONY: src clean