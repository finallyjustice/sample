# Run "gnuplot iops.p"

#set terminal postscript eps enhanced color font 'Helvetica,10' size 12,8
set terminal png size 1000,800 enhanced font "Helvetica,20"
set xtics (1,2,3,4,5) font "Verdana,20" 
set ytics font "Verdana,20"
set key font "Verdana,20"
set title font "Verdana,20"
set xlabel font "Verdana,20"
set ylabel font "Verdana,20"
set output 'iops.png'
set grid
set title 'IOPS'
set yrange [80:160]
set xlabel 'numjobs'
set ylabel 'IOPS(K)'
plot 'iops.dat' u 1:2:(sprintf("%d", $2)) w lp t 'default', 'iops.dat' u 1:3:(sprintf("%d", $2)) w lp t 'polling'
