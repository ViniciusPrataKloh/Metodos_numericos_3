set xlabel 'Espaco'
set ylabel 'Número de células'
set xrange [-1:1]
set yrange [0:1.4]
set key right top
set term png
set grid
set output 'explicit/0.05.graph_2D.png'

set cblabel "Tempo" offset -9
plot  'explicit/0.0.dat' u 2:3 title 'Tempo 0.0' w l lc rgb "dark-red", \
      'explicit/0.1.dat' u 2:3 title 'Tempo 0.1' w l lc rgb "red", \
      'explicit/0.2.dat' u 2:3 title 'Tempo 0.2' w l lc rgb "orange-red", \
      'explicit/0.3.dat' u 2:3 title 'Tempo 0.3' w l lc rgb "orange", \
      'explicit/0.4.dat' u 2:3 title 'Tempo 0.4' w l lc rgb "yellow", \
      'explicit/0.5.dat' u 2:3 title 'Tempo 0.5' w l lc rgb "light-green", \
      'explicit/0.6.dat' u 2:3 title 'Tempo 0.6' w l lc rgb "green", \
      'explicit/0.7.dat' u 2:3 title 'Tempo 0.7' w l lc rgb "light-blue", \
      'explicit/0.8.dat' u 2:3 title 'Tempo 0.8' w l lc rgb "blue", \
      'explicit/0.9.dat' u 2:3 title 'Tempo 0.9' w l lc rgb "dark-blue", \
      'explicit/1.0.dat' u 2:3 title 'Tempo 1.0' w l lc rgb "purple"
