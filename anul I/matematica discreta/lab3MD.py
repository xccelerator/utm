import numpy as np
import os


def ford(nodes, lista, start):
    dist = [float("Inf")] * nodes
    dist[start] = 0

    for _ in range(nodes - 1):
        for u, v, w in lista:
            if dist[u-1] != float("Inf") and dist[u-1] + w < dist[v-1]:
                dist[v-1] = dist[u-1] + w
    return dist

def makeList(initList, nodes):
    lista = [] 
    for i in range(nodes):
        lista.append([])

    for i in initList:
        lista[i[0] - 1].append(i[1])

    return lista

def afisLista(lista,nodes):
    print("Lista:")
    lAdj = makeList(lista,nodes)

    for i in range(nodes):
        print(i + 1,': ',end='')
        if lAdj[i]:
            for j in range(0,len(lAdj[i])):
                print(lAdj[i][j],'_',sep='',end='')
        print(0)

    print("\nPonderele:")

    for i in lista:
        print(i[0],' -> ',i[1],'; w = ',i[2], sep = "")


def initializare():
    with open('grafLab2.in','r') as f:
        lista = [[int(num) for num in line.split(' ')] for line in f]

    nodes = lista[0][0]
    lista = np.asarray(lista[1:len(lista)], dtype = object)

    return nodes, lista

nodes, lista = initializare()

os.system('cls')

makeList(lista, nodes)
afisLista(lista,nodes)

init = int(input("\nDati nodul de la care se va calcula drumul minim: "))

distanta = fordBellman(nodes, lista, init - 1)

print("\n")

for i in range(0, len(distanta)):
    if i != init - 1:
        print("Cel mai scurt drum din nodul ",init," pana in nodul ",i+1," este ", distanta[i])
