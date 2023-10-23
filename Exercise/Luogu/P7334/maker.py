from cyaron import *

n = int(2e5)
m = int(2e5)
a = Vector.random(n, [(1, int(1e9))])
f = IO(file_prefix="")
f.input_writeln(n, m)
f.input_writeln(a)
for i in range(m):
    l = randint(1, int(1e5))
    f.input_writeln(2, l, randint(l, n))

f.close()