#!/bin/bash
#script.sh

instances=(bugtrap t rooms complex)
population=(1000 500)
omegas=(2 1)
phips=(15 25 35)
phigs=(10 20 30)
pivots=(8 5 2)
methods=(bezier hermite)
iterations=(100)
alphas=(2)
bases=(50 20)

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

										echo './psomp.bin  -iteraciones '$i ' -particulas '$s'  -alpha '$a' -omega '$w'  -phip '$p' -phig '$g' -map '$f'.dat  -pivotes '$q' -mode '$m' -hbase '$b' -f out/ >> log/'$f'_'$m'.log'
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

