from cyaron import *

f = IO(file_prefix="5")

n = int(5e5)
m = int(5e5)
k = randint(1e6, 1e8)
d = randint(5e3, 1e5)
f.input_writeln(n, m, k, d)
arr = [0] * (n + 10)
cnt = 0
_ = 0
while _ < m:

    if randint(0, 80000) == 50 and _ + cnt < m:
        for i in range(n + 10):
            if (arr[i] != 0):
                f.input_writeln(i, -arr[i])
                arr[i] = 0
                _ += 1
        cnt = 0


    ch = randint(0, 100000)
    if ch == 0:
        ch = -1
    else:
        ch = 1
    x = randint(1, n - d)
    while arr[x] == 0 and ch == -1:
        x = randint(1, n - d)

    if ch == -1:
        y = randint(0, arr[x] // 1000)
    else:
        y = randint(5e8, 1e9)
    
    if arr[x] == 0 and ch * y > 0:
        cnt += 1
    if arr[x] != 0 and arr[x] + ch * y == 0:
        cnt -= 1
    arr[x] = arr[x] + ch * y
    f.input_writeln(x, y)
    _ += 1

f.output_gen("..\\B.exe")

