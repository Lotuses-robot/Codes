from cyaron import *

f = IO(file_prefix="data")
f.input_writeln(1)
_n = 5
f.input_writeln(_n, 3, 4, 10)
v = Vector.random(_n, [(2, 10)])
f.input_writeln(v)