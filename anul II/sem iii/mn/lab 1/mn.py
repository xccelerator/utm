import math

#2^x+3x-0.5
def f1(x):
    return 2**x +3*x-0.5
# fi (pentru medota aproximarilor)
def f1fi(x):
    return (0.5-2**x)/3
#f1 derivat si dublu derivat pentru metoda newton
def f1d(x):
    return math.log(2)*2**x+3

#x^3-37x-52
def f2(x):
    return x**3-37*x-52
# fi (pentru medota aproximarilor)
def f2fi(x):
    return (52-x**3)/(-37)
#f2 derivat si dublu derivat pentru metoda newton
def f2d(x):
    return 3*x**2 -37 

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

#log(1+x) + x - 1.5
print("Pentru f = log(1+x) + x - 1.5")
print("Metoda injumatatirii:")
bisect(f1,0,2)
print("Metoda aproximatiilor:")
aprox(f1fi,0)

#x^3 + 25x - 37
print("\nPentru f = x^3 + 25x - 37")
print("Metoda injumatatirii:")
bisect(f2,-2,2)
print("Metoda aproximatiilor:")
aprox(f2fi,-2)

