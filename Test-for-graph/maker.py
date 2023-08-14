from cyaron import *

_n = int(1e6)
_m = int(2e6)

test_data = IO(file_prefix="data0")

test_data.input_writeln(_n, _m)
graph = Graph.graph(_n, _m)
test_data.input_writeln(graph)

test_data.close()

test_data = IO(file_prefix="data1")

test_data.input_writeln(_n, _m)
graph = Graph.graph(_n, _m)
test_data.input_writeln(graph)

test_data.close()

test_data = IO(file_prefix="data2")

test_data.input_writeln(_n, _m)
graph = Graph.graph(_n, _m)
test_data.input_writeln(graph)

test_data.close()

test_data = IO(file_prefix="data3")

test_data.input_writeln(_n, _m)
graph = Graph.graph(_n, _m)
test_data.input_writeln(graph)

test_data.close()

# chain graph

test_data = IO(file_prefix="data4")

graph = Graph.chain(_n)
test_data.input_writeln(_n, _n - 1)
test_data.input_writeln(graph)

test_data.close()

# flower graph

test_data = IO(file_prefix="data5")

graph = Graph.flower(_n)
test_data.input_writeln(_n, _n - 1)
test_data.input_writeln(graph)

test_data.close()

# tree

test_data = IO(file_prefix="data6")

test_data.input_writeln(_n, _n - 1)
graph = Graph.tree(_n)
test_data.input_writeln(graph)

test_data.close()

# full

test_data = IO(file_prefix="data7")

_n = 1000

edge = []

for i in range(1, _n):
    for j in range(i + 1, _n + 1):
        edge.append([i, j])

test_data.input_writeln(_n, len(edge))

for e in edge:
    test_data.input_writeln(e[0], e[1])

