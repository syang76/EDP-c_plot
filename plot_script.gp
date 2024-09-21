set terminal pngcairo size 800,600
set output 'EDP.png'
set title 'EDP'
set xlabel 'Plasma frequency (MHz)'
set ylabel 'Altitude (km)'
set xrange [0:12]
set yrange [0:600]
plot 'fort.70' using 2:1 with lines
