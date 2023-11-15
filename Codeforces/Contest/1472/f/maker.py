from cyaron import *
f = IO(file_prefix="")
t = 100
f.input_writeln(t)
for _ in range(t):
    n = 10
    m = randint(5, 8)
    f.input_writeln(n, m)
    for __ in range(m):
        f.input_writeln(randint(1, 2), randint(1, n))
    
f.output_gen("f.exe")
