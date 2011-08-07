#!/bin/bash

#instances=(bugtrap1chico Tchico rooms_easychico complexchico)
instances=($1) #probar con este primero
population=(50 250)
omegas=(0.7 1.5)
phips=(0.6 1 1.4)
phigs=(0.6 1 1.4)
pivots=(2 5 8) #3n+2, n=0,1,2,...
methods=($2)
iterations=(5 10 30)
alphas=(2 2.5 3)
bases=(1 30 60)

#directorio salida
out_dir='out_'$1'_'$2'_'$3

#numero iteracion
iteracion_actual=1

#cantidad de combinaciones
let total_ejecuciones=${#instances[*]}*${#population[*]}*${#omegas[*]}*${#phips[*]}*${#phigs[*]}*${#pivots[*]}*${#methods[*]}*${#iterations[*]}*${#alphas[*]}*${#bases[*]}

#crear directorio salida, si ya existe no hace nada
mkdir $out_dir

	for f in ${instances[*]}
	do
		for s in ${population[*]}
		do
			for w in ${omegas[*]}
			do
				for p in ${phips[*]}
				do
					for g in ${phigs[*]}
					do
						for q in ${pivots[*]}
						do
							for m in ${methods[*]}
							do
								for i in ${iterations[*]}
								do
									for a in ${alphas[*]}
									do
										for b in  ${bases[*]}
										do
											echo 'echo "[map: '$1' | method: '$2' | #: '$3'] iteracion: '$iteracion_actual' de '$total_ejecuciones' ('$(($iteracion_actual*100/$total_ejecuciones))'%)"';
											echo './psomp.bin  -iteraciones '$i ' -particulas '$s'  -alpha '$a' -omega '$w'  -phip '$p' -phig '$g' -map 'maps/$f'.dat -pivotes '$q' -mode '$m' -hbase '$b' -f '$out_dir'/';
											let iteracion_actual=$iteracion_actual+1;
										done
									done
								done
							done
						done
					done
				done
			done
		done
	done

