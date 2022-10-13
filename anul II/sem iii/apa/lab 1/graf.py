import matplotlib.pyplot as plt

fibNum = [1,5,7,10,12,15,30,40]

fib1 = [6,30,42,60,72,90,180,240]
fib2 = [1,8,21,89,233,987,1346269,165580141]
fib3 = [22,55,66,66,66,88,99, 88]

plt.plot(fibNum, fib1, 'r',  fibNum, fib3, 'b')
plt.show()
