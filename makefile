CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET   = exprparser
SRCS     = src/lexer.cpp src/parser.cpp src/evaluator.cpp src/printer.cpp src/main.cpp
OBJS     = $(SRCS:.cpp=.o)
 
all: $(TARGET)
 
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
 
run: $(TARGET)
	./$(TARGET)
 
clean:
	rm -f $(OBJS) $(TARGET)
 
rebuild: clean all

lexer.o:     src/lexer.cpp src/lexer.h src/token.h
parser.o:    src/parser.cpp src/parser.h src/ast.h src/token.h
evaluator.o: src/evaluator.cpp src/evaluator.h src/ast.h src/token.h
printer.o:   src/printer.cpp src/printer.h src/ast.h src/token.h
main.o:      src/main.cpp src/lexer.h src/parser.h src/evaluator.h src/printer.h
