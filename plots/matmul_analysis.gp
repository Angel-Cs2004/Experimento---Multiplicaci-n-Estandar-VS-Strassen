set terminal pngcairo enhanced font "Arial,12" size 900,600
set output "matmul_analysis.png"

set title "Comparación de Tiempos: Multiplicación Estándar vs Strassen" font "Arial,14,Bold"
set xlabel "Tamaño de Matriz (n x n)"
set ylabel "Tiempo (ms) — Mediana de 10 repeticiones"
set grid lw 1 lt 0 lc rgb "#CCCCCC"
set border lw 1.5
set key top left box
set logscale x 2
set xtics (4, 8, 16, 32, 64, 128, 256, 512)
set format x "%g"
set arrow from 32, graph 0 to 32, graph 1 nohead lw 2 lt 2 lc rgb "red" dashtype 2
set label "n = 32\n(umbral)" at 33, graph 0.9 font "Arial,10" tc rgb "red"
set yrange [0:*]

plot "../data/resultados.dat" using 1:2 with linespoints \
        lw 2 pt 7 ps 1 lc rgb "#2980B9" title "Estándar O(n^3)", \
     "../data/resultados.dat" using 1:3 with linespoints \
        lw 2 pt 5 ps 1 lc rgb "#27AE60" title "Strassen O(n^{2.81})"

set output

set terminal qt enhanced font "Arial,12" size 900,600
replot
pause -1 "Presiona Enter para cerrar la ventana..."
