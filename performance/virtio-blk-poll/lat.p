# Run "gnuplot lat.p"

#set terminal postscript eps enhanced color font 'Helvetica,10' size 12,8
set terminal png size 1000,800 enhanced font "Helvetica,20"
set xtics (1,2,3,4,5) font "Verdana,20" 
set ytics font "Verdana,20"
set key font "Verdana,20"
set title font "Verdana,20"
set xlabel font "Verdana,20"
set ylabel font "Verdana,20"
set output 'lat.png'
set grid
set title 'Latency'
set yrange [0:3000]
set xlabel 'numjobs'
set ylabel 'latency(usec)'
plot 'lat.dat' u 1:2:(sprintf("%d", $2)) w lp t 'default', 'lat.dat' u 1:3:(sprintf("%d", $2)) w lp t 'polling'
