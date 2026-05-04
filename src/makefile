MathematicalCompiler: main.o lexer.o parser.o evaluator.o
	g++ -std=c++11 -g -Wall main.o lexer.o parser.o evaluator.o -o MathematicalCompiler

main.o: main.cpp lexer.h parser.h token.h ast.h evaluator.h printer.h
	g++ -std=c++11 -g -Wall -c main.cpp

lexer.o: lexer.cpp lexer.h token.h
	g++ -std=c++11 -g -Wall -c lexer.cpp 

parser.o: parser.cpp parser.h token.h ast.h 
	g++ -std=c++11 -g -Wall -c parser.cpp 

evaluator.o: evaluator.cpp evaluator.h token.h ast.h
	g++ -std=c++11 -g -Wall -c evaluator.cpp 

clean: 
	rm *.o MathematicalCompiler
