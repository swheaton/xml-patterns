OBJS	= NodeFlyweight.o Facade.o Interpreter.o Attr.o Document.o Element.o NamedNodeMap.o Node.o Text.o XMLTokenizer.o XMLSerializer.o XMLValidator.o ValidChildren.o Director.o Builder.o Subject.o Invoker.o
CPPFLAGS= -Iregexpp3/ -g -std=c++11

all: Test

clean:
	rm *.o Test

Test: ${OBJS} Test.o
	${CXX} -g -Lregexpp3/libs/regex/build/gcc -o Test $^ -lboost_regex
