CXX=g++ -std=c++17
OBJDIR=./obj/
SRCDIR=./src/
OUTDIR=./out/

all: dir montador

montador:$(OBJDIR)montador.o $(OBJDIR)utils.o $(OBJDIR)analisador_semantico.o $(OBJDIR)analisador_sintatico.o $(OBJDIR)macro.o $(OBJDIR)passagem_1.o $(OBJDIR)passagem_2.o $(OBJDIR)pre_processador.o
	$(CXX) $^ -o $@

$(OBJDIR)montador.o:montador.cpp $(SRCDIR)pre_processador.cpp $(SRCDIR)pre_processador.hpp $(SRCDIR)passagem_1.cpp $(SRCDIR)passagem_1.hpp $(SRCDIR)passagem_2.cpp $(SRCDIR)passagem_2.hpp $(SRCDIR)utils.cpp $(SRCDIR)utils.hpp 
	$(CXX) $< -c -o $(OBJDIR)montador.o

$(OBJDIR)pre_processador.o:$(SRCDIR)pre_processador.cpp $(SRCDIR)pre_processador.hpp $(SRCDIR)macro.cpp $(SRCDIR)macro.hpp $(SRCDIR)utils.cpp $(SRCDIR)utils.hpp 
	$(CXX) $< -c -o $(OBJDIR)pre_processador.o	

$(OBJDIR)passagem_2.o:$(SRCDIR)passagem_2.cpp $(SRCDIR)passagem_2.hpp $(SRCDIR)analisador_semantico.cpp $(SRCDIR)analisador_semantico.hpp $(SRCDIR)utils.cpp $(SRCDIR)utils.hpp 
	$(CXX) $< -c -o $(OBJDIR)passagem_2.o

$(OBJDIR)passagem_1.o:$(SRCDIR)passagem_1.cpp $(SRCDIR)passagem_1.hpp $(SRCDIR)analisador_sintatico.cpp $(SRCDIR)analisador_sintatico.hpp $(SRCDIR)utils.cpp $(SRCDIR)utils.hpp
	$(CXX) $< -c -o $(OBJDIR)passagem_1.o		

$(OBJDIR)macro.o:$(SRCDIR)macro.cpp $(SRCDIR)macro.hpp $(SRCDIR)utils.cpp $(SRCDIR)utils.hpp 
	$(CXX) $< -c -o $(OBJDIR)macro.o	

$(OBJDIR)analisador_sintatico.o:$(SRCDIR)analisador_sintatico.cpp $(SRCDIR)analisador_sintatico.hpp $(SRCDIR)utils.cpp $(SRCDIR)utils.hpp 
	$(CXX) $< -c -o $(OBJDIR)analisador_sintatico.o

$(OBJDIR)analisador_semantico.o:$(SRCDIR)analisador_semantico.cpp $(SRCDIR)analisador_semantico.hpp $(SRCDIR)utils.cpp $(SRCDIR)utils.hpp 
	$(CXX) $< -c -o $(OBJDIR)analisador_semantico.o
	
$(OBJDIR)utils.o:$(SRCDIR)utils.cpp $(SRCDIR)utils.hpp
	$(CXX) $< -c -o $(OBJDIR)utils.o				

dir:
	if test -d obj; then echo obj exists; else mkdir obj;fi
	if test -d out; then echo out exists; else mkdir out;fi

clean:
	rm -f $(OBJDIR)*.o $(OUTDIR)*.txt montador