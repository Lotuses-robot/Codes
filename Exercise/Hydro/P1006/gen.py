from cyaron import *

_n = ati([8, 8, 8, 8, 8, 8, 1e3, 1e3, 1e3, 1e3, 1e3, 1e3, 1e3, 1e3, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5])
_m = ati([10, 10, 10, 10, 10, 10, 1e4, 1e4, 1e4, 1e4, 1e4, 1e4, 1e4, 1e4, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5])

print(len(_n), len(_m))

for i in range(0, 20):
    test_data = IO(file_prefix = "seq", data_id = i + 1)

    print(i)
    n = _n[i]
    m = _m[i]
    a = []
    q = []
    for j in range(0, n):
        a.append(randint(1, 1e9))
    for j in range(0, m):
        nowques = []
        nowques.append(randint(1, 3))
        left = randint(1, n - 1)
        right = randint(left, n)
        nowques.append(left)
        nowques.append(right)
        if nowques[0] == 1 or nowques[0] == 2:
            k = randint(1, 1e9)
            nowques.append(k)
        q.append(nowques)

    # output
    test_data.input_writeln(n, m)
    for j in range(0, n):
        test_data.input_write(a[j], "")
    test_data.input_writeln("")
    for j in range(0, m):
        test_data.input_writeln(q[j])

    test_data.output_gen("D:\\Robot\\OI\\Code\\Exercise\\23118\\P1006\\P1006.exe")