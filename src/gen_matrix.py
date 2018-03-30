import random
import os
# This file generate a matrix of size M x N
M = 61
N = 67
# outfile = "res/matrix-" + M + "-" + N + "./txt"
outfile = "matrix-%d-%d.txt" % (M, N)
os.chdir("/home/higher/Program/morton-order-traverse/src/res")
with open (outfile, "w") as f:
	f.write("%d %d\n" %(M, N))
	i = 0
	for i in range(M):
		j = 0
		for j in range(N):
			f.write("%d " % random.randint(0, M * N * M / 3))
		f.write("\n")
print "Generate complete"
