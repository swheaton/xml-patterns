OBJS	= Attr.o Document.o Element.o NamedNodeMap.o Node.o Text.o XMLTokenizer.o XMLSerializer.o XMLValidator.o
CPPFLAGS= -Iboost_1_56_0/boost
#CPPFLAGS= -I/usr/local/include/
#CPPFLAGS= -Iregexpp3/

all: Test

Test: ${OBJS} Test.o
	${CXX} -Lboost_1_56_0/libs/regex/build/gcc -o Test $^ -lboost_regex-gcc-1_53
#	${CXX} -L/usr/local/lib -o Test $^ -lboost_regex
#	${CXX} -Lregexpp3/libs/regex/build/gcc -o Test $^ -lboost_regex
