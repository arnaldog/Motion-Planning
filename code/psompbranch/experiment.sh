#!/bin/bash

#instances=(bugtrap1chico Tchico rooms_easychico complexchico)
instances=(bugtrap1chico) #probar con este primero
population=(50 250)
omegas=(0.7 1.5)
phips=(0.6 1 1.4)
phigs=(0.6 1 1.4)
pivots=(1 2 4 6)
methods=(hermite)
iterations=(5 10 30)
alphas=(2 2.5 3)
bases=(1 10 20)

#crear directorio salida, si ya existe no hace nada
mkdir out

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
										echo './psomp.bin  -iteraciones '$i ' -particulas '$s'  -alpha '$a' -omega '$w'  -phip '$p' -phig '$g' -map '../psomp/maps/$f'.dat -pivotes '$q' -mode '$m' -hbase '$b' -f out/'
										#echo $f $i $s $a $w $p $g $q $m $b >> 'log/'$f'_'$m'.log'
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

