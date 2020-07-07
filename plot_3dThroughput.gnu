set grid xtics ytics ztics lt 0
set ticslevel 0
set xlabel 'Room length (m)' rotate parallel
set ylabel 'Room width (m)' rotate parallel
set zlabel 'Sum Throughput (Mbps)' rotate parallel
splot \
'AP_point.dat' u 2:3:(0) w p pt 13 lc rgb 'black' notitle, \
'UE_throughput.dat' w impulses lc rgb 'red' notitle, \
'UE_throughput.dat' w p pt 8 lc rgb 'red' notitle, \
'UE_off.dat' u 1:2:(0) w p pt 9 lc rgb 'red' notitle
