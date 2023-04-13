import random

file = open(".in", "w+") 

n = 3
file.write(str(n - 1) + '\n')
for i in range(0, n):
    file.write(str(random.randint(0, 5)) + " ")

file.write("\n")

for i in range(0, n - 1):
    file.write(str(random.randint(-5, 5)) + " ")

file.write("\n")
file.close()