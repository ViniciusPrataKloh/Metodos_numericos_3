set xlabel 'Tempo' offset -3
set ylabel 'Espaço' offset 3
set zlabel 'Número de células' rotate by 90 center
set xrange [0:1]
set yrange [-1:1]
set zrange [0:1.4]
set cbrange [0:1.4]
set term png
set output 'explicit/0.05_graph_3D_intense.png'

set palette defined (0 '#4682B4',\
                     2 '#00FF7F',\
                     3 '#00FF00',\
                     4 '#FFFF00',\
                     6 '#FFA500', \
                     7 '#FF0000', \
                     8 '#8B1A1A', \
                     9 '#8B008B', \
                     10 'black')
#set cblabel "Num. de células" offset -9

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
set pm3d
#set pm3d at b
#set ticslevel 0.5
#

splot 'explicit/output.dat' u 1:2:3 title '' w p lc rgb "gray" pt 6 ps 0


#splot 'output.dat' u 1:2:3 w lines
#
#plot '0.10.dat' u 1:2 title '' w lines ls 1, \
#     '0.20.dat' u 1:2 title '' w lines ls 2, \
#     '0.30.dat' u 1:2 title '' w lines ls 3
