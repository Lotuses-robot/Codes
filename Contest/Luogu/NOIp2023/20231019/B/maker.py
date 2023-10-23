from cyaron import *

n = int(1e3)
m = int(5e5)
g = Graph.graph(n, m, self_loop = False, repeated_edges = False)
f = IO(file_prefix="")
f.input_writeln(n, m)
f.input_writeln(g.to_str(output=Edge.unweighted_edge))
