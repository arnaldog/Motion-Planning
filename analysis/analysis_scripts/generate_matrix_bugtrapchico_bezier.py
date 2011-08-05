import os
import csv

# global path for data
path = "../data/bugtrapchico_hermite/";
files = os.listdir(path);

# file name filtering
files = filter( lambda x: x.endswith(".ppm"), os.listdir(path));

# aux vars
sep = "_"
logsuffix = "log.csv"
initsuffix = "initialize.csv"
initsuffix = "iteration.csv"

# csv writer for analysis
target_file = "../results/bugtrapchico_hermite.csv";
writer = csv.writer(open(target_file, 'wb'), delimiter=',');

# csv write headers

headers = ['omega', 'phig', 'phip', 'etc']

# file loops
for f in files:
	p = f.split('_');
	#PARAMETER VALUES
	
	filename = p[4];
	#print filename

	prefix = sep.join((p[0], p[1], p[2], p[3])); 
	#print prefix	

	p0 = p[5]
	p1 = p[6]
	p2 = p[7]
	p3 = p[8]
	p4 = p[9]
	p5 = p[10]

	# reading files
	logfile = path+sep.join((prefix, logsuffix))
	reader = csv.reader(open(logfile,'rb'), delimiter=',');
	
	reader.next();

	for row in reader:
		p6 = row[0]
		p7 = row[1]
		p8 = row[2]	
		
		# print row
		#print p0, p1, p2, p3, p4, p5, p6, p7, p8
			
		prowset = [ p0, p1, p2, p3, p4, p5, p6, p7, p8 ] 
		writer.writerow(prowset);
	
	
