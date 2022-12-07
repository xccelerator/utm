import sympy as sym
import matplotlib.pyplot as plt
import csv

eps = 10 ** -4

def print_function(f):
    print("Polinomul lagrange:")
    # print(str(f).replace('**','^'))
    print(f"L{sym.degree(f)} = {str(f).replace('**','^')}")

def lagrange(x, y):
    v = sym.Symbol('x')
    lagrange = 0
    for i in range(len(x)):
        Ln = y[i]
        for j in range(len(x)):
            if j == i:
                continue
            Ln *= (v - x[j])/(x[i] - x[j])
        lagrange += Ln
    lagrange = sym.simplify(lagrange).evalf()
    return lagrange

def L_n(x0, x1, y0, y1):
    return (y0 * x1 - y1 * x0)/(x1-x0)

def aitken(a, x, y):
    headers = ["Xi", "Yi", "Xi - a"]
    tabel = []
    for i in range(len(x)):
        line = [x[i], y[i], round(x[i] -a,5)]
        title = "L_"
        for j in range(i,0,-1):
            if i == 0:
                continue
            title += f'i-{j}_'
            line.append(0)
        if i != 0:
            headers.append(title+'i')
        tabel.append(line)

    val = 0
    error = 0
    for i in range(len(tabel)):
        for j in range(1, len(tabel[i])):
            try:
                x0, x1, y0, y1 = tabel[i-j+2][2], tabel[i][2], tabel[i-1][j-2], tabel[i][j-2]
            except:
                pass
            if j > 3:
                y0 = tabel[i-1][j-1]
                y1 = tabel[i][j-1]
            if tabel[i][j] == 0:
                val = L_n(x0, x1, y0, y1)
                tabel[i][j] = round(val, 4)

            error = abs(tabel[i][j] - tabel[i-1][j-1]) 
            if error < eps:
                break
    
    print('\n'.join(['|'.join(['{:10}'.format(item) for item in row]).replace("_",",") +"|" for row in [headers]+tabel]))
    export([headers]+tabel)
    print("error:", error)
    print(f'f({a})≈L({a})= {val}')
    return val

var = 7
a = 0.204
x = [0.104, 0.205, 0.310, 0.401, 0.507, 0.618, 0.721]
y = [4.96713, 6.811347, 8.76712, 10.16147, 9.12347, 7.26493, 5.37149]

f = lagrange(x, y)
print(f"L{sym.degree(f)}({a}) = {f.subs('x', a)}")
#print("pentru a =",a,"Ln(",a,")=",f.subs('x', a),sym.degree(f))
print_function(f)

aitken(a, x, y)
