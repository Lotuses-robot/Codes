from cyaron import *

f = IO(file_prefix="")
f.input_writeln(100000)
for i in range(100000):
    f.input_write(randint(1, int(1e9)))

f.input_write('\n')
g = Graph.tree(100000, 0.4, 0.3)
f.input_writeln(g.to_str(output=Edge.unweighted_edge))