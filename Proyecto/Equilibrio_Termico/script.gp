set term pdf
set out "Histograma1.pdf"
n=100 
max=35. 
min=0.
width=(max-min)/n
hist(x,width)=width*floor(x/width)+width/2.0
set boxwidth width*0.9
set style fill solid 0.5
plot "datos.dat" u (hist($1,width)):(1.0) smooth freq w boxes lc rgb"blue" notitle
