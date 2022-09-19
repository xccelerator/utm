import math
import pandas as pd

#log(1+x) + x - 1.5
def f1(x):
    return math.log10(1+x) + x - 1.5
# fi (pentru medota aproximarilor)
def f1fi(x):
    return 1.5 - math.log10(1+x)
#f1 derivat si dublu derivat pentru metoda newton
def f1d(x):
    return 1/(math.log10(10)*(x+1)) + 1
def f1dd(x):
    return -1/(math.log(10)*(x+1)**2)

#x^3 + 25x - 37
def f2(x):
    return x**3 + 25*x - 37
# fi (pentru medota aproximarilor)
def f2fi(x):
    return (x**3-37)/(-25)
#f2 derivat si dublu derivat pentru metoda newton
def f2d(x):
    return 3*x**2 + 25
def f2dd(x):
    return 6*x

def afisare(x, i, err):
    print("x =", x, "Iteratii:", i,"Eroare:",err)

#metoda injumatatirii intervalelor (bisectoarelor)
def bisect(func,a,b):
    i = 0
    x = a
    y = func(x)
    if(func(a) * func(b) < 0):
        while(abs(y) > 10**(-6)):
            x = (a+b)/2
            y = func(x)
            if(func(a)*y < 0):
                b = x
            else:
                a = x 
            i += 1
    afisare(x,i,a-b)
    return x

#metoda aproximatiilor succesive
def aprox(func, a):
    i = 0
    while True:
        x = a 
        a = func(x)

        i += 1
        if(abs(a - x) < 10**(-6)):
            afisare(x,i,a-x)
            return x

#metoda newton
def newton(func, dFunc, ddFunc, a, b):
    i = 0
    if(func(a) * ddFunc(a) > 0):
        x = x1 = a
    else:
        x = x1 = b

    while True:
        x = x1
        x1 = x - func(x) / dFunc(x)

        i += 1
        if(abs(x1-x) < 10**(-6)):
            afisare(x,i,x1-x)
            return x1


#log(1+x) + x - 1.5
print("Pentru f = log(1+x) + x - 1.5")
print("Metoda injumatatirii:")
bisect(f1,0,2)
print("Metoda aproximatiilor:")
aprox(f1fi,0)
print("Metoda Newton:")
newton(f1,f1d,f1dd,0,1)

#x^3 + 25x - 37
print("\nPentru f = x^3 + 25x - 37")
print("Metoda injumatatirii:")
bisect(f2,-2,2)
print("Metoda aproximatiilor:")
aprox(f2fi,-2)
print("Metoda Newton:")
newton(f2,f2d,f2dd,-1,1)

