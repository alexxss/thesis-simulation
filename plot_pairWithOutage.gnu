set xrange[0.0:15.5]
set yrange[0.0:15.5]
set xlabel 'Room length (m)'
set ylabel 'Room width (m)'
set key at 16,16 box opaque
set border back
plot \
'AP_UE_pairFinal.dat' with lines lc rgb 'gray' lw 3 notitle, \
'AP_UE_pair.dat' with lines dt 2 lc rgb 'gray' title 'disabled', \
'AP_point.dat' using 2:3:(sprintf("%d",$1)) with labels tc rgb 'black' point pt 5 lc rgb 'black' lw 2 offset 1,0 title 'AP on', \
'AP_off.dat' pt 5 lc rgb 'gray' title 'AP off', \
'UE_point.dat' using 2:3:(sprintf("%d",$1)) with labels tc rgb 'red' point pt 8 lc rgb 'red' offset 0.5,0.5 title 'UE'
