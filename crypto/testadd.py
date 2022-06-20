import ctypes as Ct

addlib=Ct.WinDLL("testadd")

print(addlib.myadd(3+2))