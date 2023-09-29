from cyaron import *

io = IO(file_prefix="")
v = Vector.random(15, [(1, 15)])
io.input_writeln(15, randint(1, 15))
io.input_writeln(v)
io.output_gen("std.exe")