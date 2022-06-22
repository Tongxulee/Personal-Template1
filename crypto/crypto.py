from Crypto.Cipher import AES
import hashlib
import os

file = './tmp.hex'
file2 = './FVC2cal.hex'
with open(file,'rb') as fp:
    content = fp.read()
    s=hashlib.sha256()
    s.update(content)
    b=s.digest()
    print('tmp.hex:\n'+b.hex().upper())
with open(file2,'rb') as fp:
    content = fp.read()
    s=hashlib.sha256()
    s.update(content)
    b=s.digest()
    print('FVC2cal.hex:\n'+b.hex().upper())

# tmparry=(0x6816b4d5).to_bytes(4, 'big')
# s=hashlib.sha256()
# s.update(tmparry)
# b=s.digest()
# print(b.hex().upper())
# print(tmparry.hex())