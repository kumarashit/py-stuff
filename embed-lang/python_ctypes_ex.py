from threading import Thread
from ctypes import *

# Locatoion of the C Library
so_file = "./getcpuid.so"
c_function = CDLL(so_file)

#https://stackoverflow.com/questions/24912065/how-to-access-data-from-pointer-in-struct-from-python-with-ctypes
class object_t(Structure):
    _fields_ = [
            ('cpu', c_int),
            ('thread', c_long),
            ('message', c_char_p),
    ]

def take_to_delhi():
    print("Welcome to New Delhi!!")
    ret  = res()
    print(ret.contents.message)
    print("The cpu id:", ret.contents.cpu)
    print("The thread id:", ret.contents.thread)

def take_to_patna():
    print("Welcome to Patna!!")
    ret  = res()
    print(ret.contents.message)
    print("The cpu id:", ret.contents.cpu)
    print("The thread id:", ret.contents.thread)

res = c_function.cpu_thread_func
res.argtypes = None
res.restype = POINTER(object_t)

t1 = Thread(target=take_to_delhi)
t2 = Thread(target=take_to_patna)

t1.start()
t2.start()
t1.join()
t2.join()

