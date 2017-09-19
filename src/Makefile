OBJS	= Attr.o Document.o Element.o NamedNodeMap.o Node.o Text.o XMLTokenizer.o XMLSerializer.o XMLValidator.o ValidChildren.o
CPPFLAGS= -std=c++11 -Iregexpp3/

all: Test

Test: ${OBJS} Test.o
	${CXX} -Lregexpp3/libs/regex/build/gcc -o Test $^ -lboost_regex

clean:
	rm *.o Test
