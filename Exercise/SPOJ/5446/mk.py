from cyaron import *

f = IO(file_prefix="data")
g = Graph.graph(10, 100)
f.input_writeln(10, 100)
f.input_writeln(g.to_str(output=Edge.unweighted_edge))
f.input_writeln((0, 0))
f.close()