from cyaron import *

_n = ati([1e3, 1e3, 1e3, 1e3, 1e4, 1e4])
_m = ati([1e5, 1e5, 1e5, 1e5, 1e5, 1e5])
low = ati([5, 10, 5, 25, 25, 25])

# for i in range(0, 6):
#     test_data = IO(file_prefix = "money", data_id= i + 10)

#     n = _n[i]
#     m = _m[i]
#     s = randint(1, n)
#     t = randint(1, n)
#     l = low[i]

#     g = Graph.graph(n, m, weight_limit = (l, 99))
#     test_data.input_writeln(n, m)
#     test_data.input_writeln(g)
#     test_data.input_writeln(s, t)

#     test_data.output_gen("D:\\Robot\\OI\\Code\\Exercise\\23118\\P1001\\P1001.exe")

for i in range(8, 9):
    test_data = IO(file_prefix = "money", data_id= i + 10)

    n = int(1e5)
    m = 0
    s = randint(1, n)
    t = randint(1, n)
    l = 25

    g = Graph.hack_spfa(n, weight_limit = (1, 1))
    for ss in g.edges:
        m += len(ss)
    test_data.input_writeln(n, m // 2)
    test_data.input_writeln(g)
    test_data.input_writeln(s, t)

    # print(s, t)

    test_data.output_gen("D:\\Robot\\OI\\Code\\Exercise\\23118\\P1001\\P1001.exe")