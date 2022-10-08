set title "Number of Infected Agents as a function of Mean Connection Number Increase Speed"
set xlabel "Time (Days)"
set ylabel "Number of Agents"
plot "SIRPlotBase.txt" using 1:3 lw 3 title "No Connection Dynamics", "SIRPlotSlow.txt" using 1:3 lw 3 title "Slow Mean Connection Increase", "SIRPlotMedium.txt" using 1:3 lw 3 title "Medium Mean Connection Increase", "SIRPlotFast.txt" using 1:3 lw 3 title "Fast Mean Connection Increase"
pause -1