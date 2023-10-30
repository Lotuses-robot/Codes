from cyaron import *

f = IO(file_prefix="")
v = Vector.random(10000, [(1, 10000)])
for i in range(10000):
    if v[i] == i:
        v[i] = randint(1, 666)
f.input_writeln(10000)
f.input_writeln(v)
