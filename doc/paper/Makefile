#Compilador
PDFLATEX=pdflatex
#binarios esperados
FLAGS=--shell-escape
BIN=main.pdf
#fuentes
SRC = main.tex
#objetos generados en el proceso
OBJ=*.acn *.aux *.glo *.ist *.log

all: $(SRC)
	$(PDFLATEX) $(FLAGS) $(SRC)

clean:
	rm -rf $(OBJ) 
