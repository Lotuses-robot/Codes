from cyaron import *

f = IO(file_prefix="")
f.input_writeln(100000)
for i in range(100000):
    f.input_writeln(100, randint(1, 100))
    f.input_writeln(Vector.random(100, [(1, 100)]))