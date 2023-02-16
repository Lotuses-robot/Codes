def main():
    n = int(input().strip())
    t = input().strip()
    s = ['' for i in range(n)]

    for i in range(0, len(t), 8):
        k = chr(int(t[i:i + 8], 2))
        if s[i // 8] == '':
            s[i // 8] = k
        elif s[i // 8] != k:
            print('NIE')
            return

    print(''.join(s))

if __name__ == '__main__':
    main()
