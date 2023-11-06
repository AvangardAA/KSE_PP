def encrypt(txt, key):
    encr_out = ""
    for c in txt:
        if c.isalpha():
            cInUp = c.isupper()
            c = c.lower()
            encC = chr(((ord(c) - ord('a') + key) % 26) + ord('a'))
            if cInUp:
                encC = encC.upper()
            encr_out += encC
        else:
            encr_out += c
    return encr_out

def decrypt(txt, key):
    return encrypt(txt, -key)

def enc_file(inp, outp, key):
    with open(inp, 'r') as f:
        txt = f.read()
    encr = encrypt(txt, key)
    with open(outp, 'w') as f:
        f.write(encr)

def decr_file(inp, outp, key):
    with open(inp, 'r') as f:
        txt = f.read()
    decr = decrypt(txt, key)
    with open(outp, 'w') as f:
        f.write(decr)

def main():
    c = input("1 encrypt, 2 decrypt: ")
    key = int(input("input key: "))
    inpfile = "input.txt"
    outfile = "output.txt"

    if c == "1":
        enc_file(inpfile, outfile, key)
    elif c == "2":
        decr_file(inpfile, outfile, key)
    else:
        print("invalid option")


if __name__ == "__main__":
    main()
