import time
import math
import matplotlib.pyplot as plt

#fib_num = [1,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100]
fib_num = [1,5,10,15,20,25,30,35,40]
fib1_list = []
fib2_list = []
fib3_list = []

def fib1(num):
    a = 0
    b = 1
    start = time.time()
    for i in range(1,num):
        b = a + b
        a = b - a
        if i in fib_num:
            fib1_list.append(time.time() - start)
    fib1_list.append(time.time() - start)
    return b 

def fib2(num):
    global start
    if num <= 2:
        return 1
    return fib2(num - 1) + fib2(num - 2)

def fib3(num):
    return (((1+math.sqrt(5))/2)**num - ((1-math.sqrt(5))/2)**num)/ math.sqrt(5)
   # return 1.618**(num-4) + 4

fib1(40)

for i in fib_num:
    start = time.time()
    fib2(i)
    fib2_list.append(time.time() - start)

for i in fib_num:
    start = time.time()
    fib3(i)
    fib3_list.append(time.time() - start)

plt.plot(fib_num, fib1_list, fib_num, fib2_list, fib_num, fib3_list)
plt.show()
