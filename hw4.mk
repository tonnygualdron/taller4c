Resultados_hw4.pdf: Resultados_hw4.tex
	pdflatex Resultados_hw4.tex

Resultados_hw4.tex: *.jpg

*.jpg: PDE.cpp PDE.o *.txt ODE.cpp ODE.o 
	python3 Plots_hw4.py

*.txt: PDE.cpp PDE.o ODE.cpp ODE.o
	./ODE.o	
	./PDE.o

PDE.o:
	c++ PDE.cpp -o PDE.o
ODE.o:
	c++ ODE.cpp -o ODE.o

clean:
	rm -f *.txt *.jpg *.o
