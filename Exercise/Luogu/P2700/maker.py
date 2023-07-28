from cyaron import *
from random import *

_n = 5
_k = 3
tr = Graph.tree(_n)

f = open(".in", "w+")
f.write("%d %d\n" % (_n, _k))

output = Vector.random(_k, [(1, 5)])

for q in output:
    f.write("%d " % (q[0]))

f.write("\n")

for edge in tr.iterate_edges():
    f.write("%d %d %d\n" % (edge.start, edge.end, randint(1, 5)))

f.close()
