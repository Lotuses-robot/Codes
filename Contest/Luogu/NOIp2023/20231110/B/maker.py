from cyaron import *

f = IO(file_prefix="")
T = 10
f.input_writeln(T)
for _ in range(T):
    l = randint(1, int(1e12))
    r = randint(1, int(1e12))
    if r < l:
        x = l
        l = r
        r = x
    f.input_writeln(l, r)