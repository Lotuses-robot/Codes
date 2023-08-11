from cyaron import *

_n = int(1e5)
graph = Graph.hack_spfa(_n)
test_data = IO(file_prefix="data4")

_m = 0
for i in graph.edges:
    _m += len(i)

test_data.input_writeln(_n, _m)

test_data.input_writeln(graph)

test_data.input_writeln(1, 1)

test_data.input_writeln(randint(1, _n))
test_data.input_writeln(randint(1, _n))

test_data.close()