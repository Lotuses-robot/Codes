from cyaron import *

f = IO(file_prefix="")
f.input_writeln(5)
for i in range(5):
    f.input_write(randint(1, 100))

f.input_writeln()

for i in range(5):
    f.input_write(randint(1, 5))