from cyaron import *

f = IO(file_prefix="")
_n = 1000000
f.input_writeln(_n)
for i in range(_n):
    x = randint(1, _n)
    while x == i:
        x = randint(1, _n)
    f.input_writeln(x)

f.close()