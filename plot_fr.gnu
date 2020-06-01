set xrange[0.0:15.5]
set yrange[0.0:15.5]
plot \
'AP_point.dat' using 2:3:(sprintf("%d",$1)) with labels tc rgb 'black' point pt 5 lc rgb 'black' offset 1,0 title 'AP', \
'UE_point.dat' using 2:3:(sprintf("%d",$1)) with labels tc rgb 'red' point pt 8 lc rgb 'red' offset 1,1 title 'UE', \
'FR_graph.dat' with lines dt 2 lc rgb 'green' notitle, \
'RB_assignment.dat' using 1:2:(sprintf("%d",$3)) with labels tc rgb 'blue' offset 0,1 notitle
