#Compilador
PDFLATEX=pdflatex
#binarios esperados
BIN=main.pdf
#fuentes
SRC = main.tex
#objetos generados en el proceso
OBJ=*.acn *.aux *.glo *.ist *.log

all: $(SRC)
	$(PDFLATEX)  $(SRC)

clean:
	rm -rf $(BIN) $(OBJ) 
