from cyaron import *

n = 3
f = IO(file_prefix="data")
f.input_writeln(n)
for i in range(0, n):
    v = Vector.random(n, [(-10, 10)])
    f.input_writeln(v)