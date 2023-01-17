TARGET = asp_scanner

DESTDIR = /usr/local/ea/altair/bin/

INITSCRIPT = ${TARGET}.init
	
export TARGET
export CFLAGS
	
all: release 

release: CFLAGS += -g -O2
release: src	
	
src:
	${MAKE} -C ./altair_debug all
	${MAKE} -C ./src all
	${MAKE} -C ./asp_cgi all
	
clean:
	${MAKE} -C ./altair_debug $@
	${MAKE} -C ./src $@
	${MAKE} -C ./asp_cgi $@

install:
	${MAKE} -C ./asp_cgi $@
	mkdir -p ${DESTDIR}
	cp -d ./bin/${TARGET} ${DESTDIR}
	cp -d ${INITSCRIPT} /etc/init.d/${TARGET}
	chmod +x /etc/init.d/${TARGET}
	update-rc.d ${TARGET} defaults

uninstall:
	${MAKE} -C ./asp_cgi $@
	rm -f ${DESTDIR}${TARGET}
	rm -f /etc/init.d/${TARGET}
	update-rc.d -f ${TARGET} remove

.PHONY: src clean install uninstall
