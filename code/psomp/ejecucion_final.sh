#!/bin/bash

bin=./psomp.bin
out_dir=ejecucion_final/

#PRIMERA LINEA DE LA TABLA
map=maps/bugtrap1chico.dat
particulas=250
alpha=2
omega=1.5
phip=1.5
phig=1.5
pivotes=2
mode=bezier
iteraciones=100
ejecuciones=100
hbase=10
subdir=linea1/

mkdir -p $out_dir$subdir

for i in $(seq 1 $ejecuciones)
do
	echo $out_dir$subdir' | iteracion '$i;
	$bin -map $map  -particulas $particulas-alpha $alpha -omega $omega -phip $phip -phig $phig -pivotes $pivotes -mode $mode -iteraciones $iteraciones -hbase $iteraciones -f $out_dir$subdir
done

#SEGUNDA LINEA DE LA TABLA
map=maps/Tchico.dat
particulas=250
alpha=2
omega=1.5
phip=1.5
phig=1.5
pivotes=2
mode=bezier
iteraciones=100
ejecuciones=100
hbase=10
subdir=linea2/

mkdir -p $out_dir$subdir

for i in $(seq 1 $ejecuciones)
do
	echo $out_dir$subdir' | iteracion '$i;
	$bin -map $map  -particulas $particulas-alpha $alpha -omega $omega -phip $phip -phig $phig -pivotes $pivotes -mode $mode -iteraciones $iteraciones -hbase $iteraciones -f $out_dir$subdir
done

#TERCERA LINEA DE LA TABLA
map=maps/rooms_easychico.dat
particulas=250
alpha=2.5
omega=1.5
phip=0.6
phig=1.5
pivotes=5
mode=bezier
iteraciones=100
ejecuciones=100
hbase=10
subdir=linea3/

mkdir -p $out_dir$subdir

for i in $(seq 1 $ejecuciones)
do
	echo $out_dir$subdir' | iteracion '$i;
	$bin -map $map  -particulas $particulas-alpha $alpha -omega $omega -phip $phip -phig $phig -pivotes $pivotes -mode $mode -iteraciones $iteraciones -hbase $iteraciones -f $out_dir$subdir
done

#CUARTA LINEA DE LA TABLA
map=maps/complexchico.dat
particulas=250
alpha=2
omega=1.5
phip=1.5
phig=1.5
pivotes=5
mode=bezier
iteraciones=100
ejecuciones=100
hbase=10
subdir=linea4/

mkdir -p $out_dir$subdir

for i in $(seq 1 $ejecuciones)
do
	echo $out_dir$subdir' | iteracion '$i;
	$bin -map $map  -particulas $particulas-alpha $alpha -omega $omega -phip $phip -phig $phig -pivotes $pivotes -mode $mode -iteraciones $iteraciones -hbase $iteraciones -f $out_dir$subdir
done

#QUINTA LINEA DE LA TABLA
map=maps/bugtrap1chico.dat
particulas=250
alpha=3
omega=1.5
phip=1.5
phig=1.5
pivotes=2
mode=hermite
iteraciones=100
ejecuciones=100
hbase=10
subdir=linea5/

mkdir -p $out_dir$subdir

for i in $(seq 1 $ejecuciones)
do
	echo $out_dir$subdir' | iteracion '$i;
	$bin -map $map  -particulas $particulas-alpha $alpha -omega $omega -phip $phip -phig $phig -pivotes $pivotes -mode $mode -iteraciones $iteraciones -hbase $iteraciones -f $out_dir$subdir
done

#SEXTA LINEA DE LA TABLA
map=maps/Tchico.dat
particulas=250
alpha=3
omega=1.5
phip=1.5
phig=0.6
pivotes=2
mode=hermite
iteraciones=100
ejecuciones=100
hbase=10
subdir=linea6/

mkdir -p $out_dir$subdir

for i in $(seq 1 $ejecuciones)
do
	echo $out_dir$subdir' | iteracion '$i;
	$bin -map $map  -particulas $particulas-alpha $alpha -omega $omega -phip $phip -phig $phig -pivotes $pivotes -mode $mode -iteraciones $iteraciones -hbase $iteraciones -f $out_dir$subdir
done

#SEPTIMA LINEA DE LA TABLA
map=maps/rooms_easychico.dat
particulas=250
alpha=3
omega=1.5
phip=0.6
phig=0.6
pivotes=5
mode=hermite
iteraciones=100
ejecuciones=100
hbase=10
subdir=linea7/

mkdir -p $out_dir$subdir

for i in $(seq 1 $ejecuciones)
do
	echo $out_dir$subdir' | iteracion '$i;
	$bin -map $map  -particulas $particulas-alpha $alpha -omega $omega -phip $phip -phig $phig -pivotes $pivotes -mode $mode -iteraciones $iteraciones -hbase $iteraciones -f $out_dir$subdir
done


#OCTAVA LINEA DE LA TABLA
map=maps/complexchico.dat
particulas=250
alpha=3
omega=1.5
phip=0.6
phig=1.5
pivotes=5
mode=hermite
iteraciones=100
ejecuciones=100
hbase=10
subdir=linea8/

mkdir -p $out_dir$subdir

for i in $(seq 1 $ejecuciones)
do
	echo $out_dir$subdir' | iteracion '$i;
	$bin -map $map  -particulas $particulas-alpha $alpha -omega $omega -phip $phip -phig $phig -pivotes $pivotes -mode $mode -iteraciones $iteraciones -hbase $iteraciones -f $out_dir$subdir
done
