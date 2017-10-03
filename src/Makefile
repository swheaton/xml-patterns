OBJS	= Attr.o Document.o Element.o NamedNodeMap.o Node.o Text.o XMLTokenizer.o XMLSerializer.o XMLValidator.o ValidChildren.o XMLBuilder.o XMLParseDirector.o ElementProxy.o
CPPFLAGS= -Iregexpp3/ -std=c++11 -g3

all: Test

Test: ${OBJS} Test.o
	${CXX} -Lregexpp3/libs/regex/build/gcc -o Test $^ -lboost_regex

clean:
	rm *.o Test
