EXEC = test
EXEC_CPP = test_cpp

IFLAGS = -I.
CFLAGS = -Wall -g
#CFLAGS += -rdynamic

all: clean
	gcc ${CFLAGS} ${IFLAGS} -o ${EXEC} test.c backtrace.c
	g++ ${CFLAGS} ${IFLAGS} -o ${EXEC_CPP} test.cpp backtrace.cpp

clean:
	rm -f ${EXEC} ${EXEC_CPP} *.o

clean_${EXEC}:
	rm -f ${EXEC} *.o

clean_${EXEC_CPP}:
	rm -f ${EXEC_CPP} *.o

${EXEC}: clean_test
	gcc ${CFLAGS} -DBACKTRACE ${IFLAGS} -o ${EXEC} test.c backtrace.c

${EXEC_CPP}: clean_test_cpp
	g++ ${CFLAGS} -DBACKTRACE ${IFLAGS} -o ${EXEC_CPP} test.cpp backtrace.cpp
