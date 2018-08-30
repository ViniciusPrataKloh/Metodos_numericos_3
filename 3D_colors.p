set xlabel 'Tempo' offset -3
set ylabel 'Espaço' offset 3
set zlabel 'Número de células' rotate by 90 center
set xrange [0:1]
set yrange [-1:1]
set zrange [0:1.4]
set term png
set output 'explicit/0.05.graph_3D_colors.png'

#set cblabel "Tempo" offset -9

## Estilos
#set tics out
set ticslevel 0.3
set view 40, 50
#set pm3d map
set isosample 40,40
#set dgrid3d
set grid
#set hidden3d
#set contour base
#set pm3d
#set pm3d at b
#set ticslevel 0.5
#

splot 'explicit/0.0.dat' u 1:2:3 title '' w p lc rgb "dark-red" pt 6 ps 1, \
      'explicit/0.1.dat' u 1:2:3 title '' w p lc rgb "red" pt 6 ps 1, \
      'explicit/0.2.dat' u 1:2:3 title '' w p lc rgb "orange-red" pt 6 ps 1, \
      'explicit/0.3.dat' u 1:2:3 title '' w p lc rgb "orange" pt 6 ps 1, \
      'explicit/0.4.dat' u 1:2:3 title '' w p lc rgb "yellow" pt 6 ps 1, \
      'explicit/0.5.dat' u 1:2:3 title '' w p lc rgb "light-green" pt 6 ps 1, \
      'explicit/0.6.dat' u 1:2:3 title '' w p lc rgb "green" pt 6 ps 1, \
      'explicit/0.7.dat' u 1:2:3 title '' w p lc rgb "light-blue" pt 6 ps 1, \
      'D_0.01/0.8.dat' u 1:2:3 title '' w p lc rgb "blue" pt 6 ps 1, \
      'D_0.01/0.9.dat' u 1:2:3 title '' w p lc rgb "dark-blue" pt 6 ps 1, \
      'D_0.01/1.0.dat' u 1:2:3 title '' w p lc rgb "purple" pt 6 ps 1
