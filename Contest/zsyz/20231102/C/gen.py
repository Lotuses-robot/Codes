from cyaron import *
f = IO(file_prefix="")
f.input_writeln(5)
for _ in range(5):
    f.input_writeln(int(20))

    a = Vector.random(int(20), [(0, int(1e9))])
    b = Vector.random(int(20), [(0, int(1e9))])

    for i in range(int(20)):
        f.input_writeln(a[i], b[i])

f.output_gen("std.exe")