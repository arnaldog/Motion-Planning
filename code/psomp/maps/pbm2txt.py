#!/usr/bin/python

import sys

_FILE = sys.argv[1]

#lines index, counting from zero
_FILE_SIZE_LINE = 2
_FILE_BEGIN_MAP_LINE = 3

file_input = open(_FILE)
file_output = open(_FILE+'.txt','w')

file_lines = file_input.readlines()

#obtener list del mapa
map_lines = file_lines[_FILE_BEGIN_MAP_LINE:]
map_list = []
for i in iter(map_lines):
	#print i
	for j in iter(i):
		if (j != '\n'):
			#print j
			map_list.append(j)

#print map_list

#obtener size
_WIDTH = int(file_lines[_FILE_SIZE_LINE].split()[0])
_HEIGHT = int(file_lines[_FILE_SIZE_LINE].split()[1])

#imprimir ancho y alto en distintas lineas
file_output.write(str(_WIDTH)+'\n')
file_output.write(str(_HEIGHT)+'\n')

table= [ [ map_list[i + j*_HEIGHT] for i in range(_WIDTH) ] for j in range(_HEIGHT) ]
#print table

#imprimir el mapa

#por cada fila
for i in range(len(table)):
	fila = table[i]

	#para cada columna
	for j in range(len(fila)):
		###reemplazar cualquier valor distinto de 0 con un 0 (espacio libre)
		##if (table[i][j] != 0):
		##	table[i][j] = 0
		###reemplazar cualquier valor igual a 0 con un 1 (obstaculo)
		##elif (table[i][j] == 0):
		##	table[i][j] = 1
		file_output.write(str(table[i][j]))
	file_output.write('\n')

file_output.close()
file_input.close()
