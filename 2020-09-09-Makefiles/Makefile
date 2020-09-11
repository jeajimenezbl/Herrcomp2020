all: Grafica.pdf

sumas.x: sumas.cpp
	g++ sumas.cpp -o sumas.x
datos.txt: sumas.x
	./sumas.x > datos.txt
Grafica.pdf: plot.py datos.txt
	python3 plot.py

clean:
	rm -f a.out *.x datos.txt
