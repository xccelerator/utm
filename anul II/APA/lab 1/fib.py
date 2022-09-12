import time
import math
import matplotlib.pyplot as plt

fib_num = [1,10,100,1000,10000,100000,150000, 200000,250000, 300000,350000, 400000, 450000, 500000, 550000, 600000, 650000, 700000,750000, 800000, 850000, 900000, 950000, 1000000]
fib_list = []
fib3_list = []

def fib(num):
    a = 0
    b = 1;
    start = time.time()
    for i in range(0,num):
        b = a + b
        a = b - a
        if i in fib_num:
            fib_list.append(time.time() - start)
    fib_list.append(time.time() - start)
    return b

fib(1000000)
plt.plot(fib_num, fib_list)
plt.show()
