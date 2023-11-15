from cyaron import *

f = IO(file_prefix="B10")

T = 10
f.input_writeln(T)
for _ in range(T):
    n = int(1e5)
    m = randint(1e8, 1e9)

    v = Vector.random(n, [(1, int(1e9))])
    f.input_writeln(n, m)
    f.input_writeln(v)

f.output_gen(".\\B.exe")
