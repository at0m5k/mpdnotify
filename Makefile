PROG	   = mpdnotify
CC	   = gcc
PREFIX	  ?= /usr/local
BINPREFIXi =  ${PREFIX}/bin

CFLAGS	= -pedantic -Wall
LIBS	= -lmpdclient
CFLAGS	+= `pkg-config --cflags libnotify gdk-pixbuf-2.0`
LIBS	+= `pkg-config --libs libnotify gdk-pixbuf-2.0`

${PROG}: ${PROG}.c
	@${CC} ${CFLAGS} ${LIBS} -o ${PROG} ${PROG}.c
	@strip ${PROG}

install:
	install -Dm755 ${PROG} ${DESTDIR}${BINPREFIX}/${PROG}

uninstall:
	rm -f ${BINPREFIX}/${PROG}

clean:
	rm -f ${PROG}
