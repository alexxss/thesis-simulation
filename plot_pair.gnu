set xrange[0.0:15.5]
set yrange[0.0:15.5]
plot \
'AP_point.dat' using 2:3:(sprintf("%d",$1)) with labels tc rgb 'black' point pt 5 lc rgb 'black' offset 1,0 title 'AP', \
'UE_point.dat' using 2:3:(sprintf("%d",$1)) with labels tc rgb 'red' point pt 8 lc rgb 'red' offset 1,1 title 'UE', \
'AP_UE_pair.dat' with lines lc rgb 'gray' notitle
