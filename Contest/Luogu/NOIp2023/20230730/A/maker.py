from cyaron import *

_n = 100000
_m = 1000000
graph = Graph.UDAG(_n, _m, self_loop=False, repeated_edges=False)

file = open(".in", "w+")
file.write("%d %d\n" % (_n, _m))

for edge in graph.iterate_edges():
    file.write("%d %d\n" % (edge.start, edge.end))
