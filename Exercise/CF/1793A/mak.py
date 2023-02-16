import random
f = open(".in", "w+")

T = 1000
f.write(str(T) + "\n")
for i in range(0, T):
    a = random.randint(1, 10000)
    b = random.randint(1, 10000)
    c = random.randint(1, 10000)
    d = random.randint(1, 10000)
    f.write("{} {} {} {}\n".format(a, b, c, d))