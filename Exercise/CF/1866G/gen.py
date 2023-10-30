from cyaron import *

n = 10
a = Vector.random(n, [(0, 20)])
b = Vector.random(n, [(0, n - 1)])
f = IO(file_prefix="")
f.input_writeln(n)
f.input_writeln(a)
f.input_writeln(b)