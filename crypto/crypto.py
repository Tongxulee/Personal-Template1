from Crypto.Cipher import AES
import hashlib
import binascii
import os

'''
AES CBC encrypto
key:'0123456789abcdef' or {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x61,0x62,0x63,0x64,0x65,0x66}
iv: '0000000000000000' or {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30}
padding:Nopadding
'''

file = './tmp.hex'
file2 = './FVC2cal.hex'

def get_file_hash(file):
    with open(file,'rb') as fp:
        content = fp.read()
        s=get_sha256(content)
        b=s.digest()
        print(file,':\n'+b.hex().upper())

def PKCS_Zero(text):
    if len(text.encode('utf-8')) % 16:
        add = 16 - (len(text.encode('utf-8')) % 16)
    else:
        add = 0
        text = text + ('\0' * add)
    return text.encode('utf-8')

def get_sha256(text):
    s=hashlib.sha256(text)
    return s

def AES_CBC_encrypto(text,key,iv):
    print("AES_CBC_encrypto")
    mode = AES.MODE_CBC
    # print("key:",key,len(key),type(key))
    # print("iv:",iv,len(iv),type(iv))
    # print("text:",text,len(text),type(text))
    
    iv = iv.encode('utf-8')
    key=key.encode('utf-8')
    text = PKCS_Zero(text)
    
    print("key fromhex:",key,len(key),type(key))
    print("iv fromhex:",iv,len(iv),type(iv))
    print('text fromhex:',text,len(text),type(text))
    print("key hex:",bytes.hex(key),len(key),type(key))
    print("iv hex:",bytes.hex(iv),len(iv),type(iv))
    print('text hex:',bytes.hex(text),len(text),type(text))

    cryptos = AES.new(key, mode,iv)
    cipher_text = bytes.hex(cryptos.encrypt(text))
    print('cipher:',cipher_text,type(cipher_text))
    print("*********************************")
    return cipher_text

key = '0123456789abcdef'
iv = '0000000000000000'
message = '0123456789abcdef'
AES_CBC_encrypto(message,key,iv)