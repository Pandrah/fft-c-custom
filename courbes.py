import os
from matplotlib.pyplot import *

lis = os.listdir("textes/")

#info = []
r = []
data = []

for file in lis:
	f = open("textes/"+file)
	r.append(f.read().splitlines())

for file in r:
	info = []
	for nombres in file:
		info.append(float(nombres))
	data.append(info)

close('all')

figure(figsize=(50,40))
for i in range(0,len(data)):
	subplot(len(data),1,i+1)
	plot(data[i])
	xlabel(lis[i])
	grid()
show()