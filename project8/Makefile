all: 
	make clean && make vm_translator

vm_translator: main.o code_writer.o parser.o types.o
	g++ -g main.o code_writer.o parser.o types.o -std=c++17 -o vm_translator

code_writer.o: code_writer.cpp code_writer.h code_writer.ipp
	g++ -g -c code_writer.cpp -std=c++17

types.o: types.cpp types.h
	g++ -g -c types.cpp -std=c++17

parser.o: parser.cpp parser.h
	g++ -g -c parser.cpp -std=c++17

main.o:
	g++ -g -c main.cpp

clean:
	rm -f vm_translator *.o

