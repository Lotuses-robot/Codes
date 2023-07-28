from cyaron import *

inputIO = IO()
with open(".in", "r") as f:
    w = f.read()
inputIO.input_write(w)
Compare.program("P2700.exe", input=inputIO, std_program="std.exe")