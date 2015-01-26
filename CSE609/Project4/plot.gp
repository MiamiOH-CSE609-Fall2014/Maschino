set terminal png
set output 'plot_1.png'
reset
set surface
		set contour base
			set view 60, 30, 1, 1
				set key right
					set dgrid3d
						set grid xtics ytics ztics lc rgb '#cccccc'
							set title 'Multi-Year Weather Data from NOAA' font 'Arial-Bold'
								set xlabel 'Year' rotate parallel offset 0,-1  font 'Arial-Bold'
									set ylabel 'Month' rotate parallel  font 'Arial-Bold'
										 set zlabel 'Magnitude' rotate parallel font 'Arial-Bold'
											set xrange [1948:2014]
splot 'weather_data.txt' using 1:2:3 notitle with pm3d
