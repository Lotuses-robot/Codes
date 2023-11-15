from cyaron import *

for sub in range(9, 11):
    f = IO(file_prefix=("C" + str(sub)))

    T = 4
    f.input_writeln(T)
    for _ in range(T):
        n = int(1e5)
        m = randint(1, 2)

        v = Vector.random(n, [(int(-1e9), int(1e9))])
        f.input_writeln(n, m)
        f.input_writeln(v)

    f.output_gen(".\\C.exe")
    f.close()
