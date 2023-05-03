import os
import random

id = 15
n = 100000
m = 150000

out = [0]
for i in range(0, n):
    out.append(0)

file = open("data/rev" + str(id) + ".in", "w+")
file.write(str(n) + " " + str(m) + "\n")

for i in range(0, m):
    u = random.randint(1, n)
    while out[u] >= 3:
        u = random.randint(1, n)

    v = random.randint(1, n)
    while v == u or out[v] >= 3:
        v = random.randint(1, n)

    out[u] += 1
    out[v] += 1
    file.write(str(u) + " " + str(v) + "\n")

file.close()
os.system("P1096 data/rev" + str(id))
