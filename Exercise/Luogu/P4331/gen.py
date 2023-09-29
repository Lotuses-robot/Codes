from cyaron import *

f = IO(file_prefix="data1")
_n = int(1e6)
v = Vector.random(_n, [(0, 2**31 - 1)])
f.input_writeln(_n)
f.input_writeln(v)
