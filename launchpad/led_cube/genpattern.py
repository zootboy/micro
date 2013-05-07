#!/usr/bin/python3

import sys

fname = sys.argv[1]

frame = [[0,0,0,0,0,0,0,0],
		 [0,0,0,0,0,0,0,0],
		 [0,0,0,0,0,0,0,0],
		 [0,0,0,0,0,0,0,0],
		 [0,0,0,0,0,0,0,0],
		 [0,0,0,0,0,0,0,0],
		 [0,0,0,0,0,0,0,0],
		 [0,0,0,0,0,0,0,0]]

with open(fname) as f:
	for line in f.readlines():
		(x,y,z) = map(int, line.split(','))
		frame[z][y] |= (1<<x)

buf = ""

print("{\n")
for z in range(8):
	buf += "    {0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x}" % (frame[z][0],frame[z][1],frame[z][2],frame[z][3],frame[z][4],frame[z][5],frame[z][6],frame[z][7])
	if(z != 7): buf += ","
	buf += "\n"
buf += "}"

print(buf)
