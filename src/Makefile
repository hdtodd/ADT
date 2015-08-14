#Makefile for DIATOM xml input testing programs
#Developed on OSX 10.10, January, 2015
#Verified on Raspbian 18 Jan 2015
#Main testing program is dia-xml-inp
#'tree' dumps the xml file as individual nodes
#'ptest' tests parsing of plotting/optimization ranges

PROJ = dia-xml-inp
TREE = tree
PTEST= ptest
CC = gcc
CFLAGS = `xml2-config --cflags`
LDFLAGS = `xml2-config --libs`
OBJS = dia-xml-inp.o xmlParse.o

all:	${PROJ} ${TREE} ${PTEST}

.SUFFIXES: .c

.o:	.c

.c.o:	
	$(CC) $(CFLAGS) -c $<

${PROJ}: ${OBJS}
	$(CC) -o $@ $(CFLAGS) ${OBJS} ${LDFLAGS}

${TREE}: tree.o
	$(CC) -o $@ $(CFLAGS) tree.o ${LDFLAGS}

${PTEST}: ptest.o
	$(CC) -o $@ $(CFLAGS) ptest.o ${LDFLAGS}

clean:
	/bin/rm -f *.o *~

really-clean: 
	/bin/rm -f *~ *.o $(PROJ) $(TREE) $(PTEST)
