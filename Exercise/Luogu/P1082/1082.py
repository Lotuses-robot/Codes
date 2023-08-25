a = int(input())
b = int(input())
mod = 19260817
print(a % mod * (b % mod) ** (mod - 2) % mod)