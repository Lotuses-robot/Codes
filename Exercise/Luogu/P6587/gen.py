from cyaron import *
f = IO(input_suffix="")
n = 10
m = 10
a = Vector.random(num=n)
f.input_writeln(n, m)
f.input_writeln(a)
for i in range(0, m):
    op = randint(1, 2)
    if op == 1:
        l = randint(0, 4)
        r = randint(0, 2**l - 1)
        x = randint(0, 1e3)
        f.input_writeln(op, l, r, x)
    else:
        l = randint(0, 4)
        r = randint(0, 2**l - 1)
        f.input_writeln(op, l, r)

