from cyaron import *

n = int(9e4)
m = int(1e5)

v1 = Vector.random(n, [(-int(1e5), -1)])
v2 = Vector.random(m, [(-int(1e5), -1)])
f = IO(file_prefix="A")
f.input_writeln(n, m)
f.input_writeln(v1)
f.input_writeln(v2)
f.output_gen(".\\A.exe")