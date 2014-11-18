# Makefile for the lab4 driver.

COMPILER_TYPE= gnu

CC=gcc

PROG=	lab5
SRCS=	lab5.c test5.c video_gr.c

CCFLAGS= -Wall

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+= -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>
