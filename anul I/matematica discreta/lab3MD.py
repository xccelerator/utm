import numpy as np
import os


def fordBellman(nodes, lista, start):
    dist = [float("Inf")] * nodes
    dist[start] = 0

    for _ in range(nodes - 1):
        for u, v, w in lista:
            if dist[u-1] != float("Inf") and dist[u-1] + w < dist[v-1]:
                dist[v-1] = dist[u-1] + w
    return dist

def initializare():
    with open('grafLab2.in','r') as f:
        lista = [[int(num) for num in line.split(' ')] for line in f]

    nodes = lista[0][0]
    lista = np.asarray(lista[1:len(lista)], dtype = object)

    return nodes, lista

nodes, lista = initializare()

os.system('cls')

init = int(input("Dati nodul de la care se va calcula drumul minim: "))

distanta = fordBellman(nodes, lista, init - 1)

os.system('cls')

print("Nodul initial este : ",init)

for i in range(0, len(distanta)):
    if i != init - 1:
        print("Cel mai scurt drum din nodul ",init," pana in nodul ",i+1," este ", distanta[i])
