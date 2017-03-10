#This is a GNU plot script for agent outputs
set title "Agent population counts for A+B=C," 
set xlabel "Iteration number" 
set ylabel "Agent Population Count" 
plot "output.dat" using 1:2 title 'A', \
     "output.dat" using 1:3 title 'B', \
     "output.dat" using 1:4 title 'C'
