from cyaron import *

_n = 5
a = Vector.random(_n)
g = Graph.tree(_n)
g.add_edge(randint(1, _n), randint(1, _n))
f = IO(file_prefix="")
f.input_writeln(_n)
f.input_writeln(a)
f.input_writeln(g.to_str(output=Edge.unweighted_edge))
f.input_writeln(1)