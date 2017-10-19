OBJS	= Attr.o Document.o Element.o NamedNodeMap.o Node.o Text.o XMLTokenizer.o XMLSerializer.o XMLValidator.o ValidChildren.o Director.o Builder.o Adapter.o
CPPFLAGS= -Iregexpp3/ -Ixerces/ -g

all: Test

Test: ${OBJS} Test.o
	${CXX} -g -Lregexpp3/libs/regex/build/gcc -o Test $^ -lboost_regex
