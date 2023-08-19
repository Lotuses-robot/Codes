from cyaron import *

f = IO(file_prefix="data")
n = m = 10
t = 1
f.input_writeln(n, m, t)
v = Vector.random(n, [(-100, 100)])
f.input_writeln(v)
for i in range(0, m):
    v = Vector.random(n, [(-100, 100)])
    v.append(randint(0, 100))
    f.input_writeln(v)

