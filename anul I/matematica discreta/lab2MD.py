import numpy as np
import pandas as pd
import os

#Incidenta in Lista
def incidentToList(incidenta):
    rand, col = incidenta.shape
    lista = []
    for i in range(0,col):
        lista.append([])
    for i in range(0,rand):
        a = np.where(incidenta[i] == -1)
        b = np.where(incidenta[i] == 1)
        lista[a[0][0]].append(b[0][0] + 1)

    for i in range(0,col):
        lista[i].append(0)

    return np.asarray(lista, dtype = object)

#matrice adiacenta in lista
def adiacentToList(initGraf):
    row, col = initGraf.shape

    lista = []

    for i in range(0,row):
        temp = [] 
        for j in range(0,row):
            if(initGraf[i][j] == 1):
                temp.append(j+1)
        temp.append(0)
        lista.append(temp)

    return np.asarray(lista, dtype=object)

#afisarea listei
def afisList(lista):
    num = lista.shape[0]
    print("Lista adiacenta:")
    for i in range(1,num+1):
        print(i,'- ',end='')
        for j in lista[i-1]:
            if(j != 0):
                print(str(j)+'_',end = '')
            else:
                print(j)

#parcurgerea in largime
def parcLargime(lista, initial):
    vizitat = []
    asteptare = []

    print("\nParcurgerea in largime a grafului este : ", end='')

    vizitat.append(initial - 1)
    asteptare.append(initial - 1)

    while asteptare:
        nod = asteptare.pop(0)
        print(nod + 1, end =' ')

        for vecini in lista[nod][0:len(lista[nod]) - 1]:
            if vecini - 1 not in vizitat:
                vizitat.append(vecini - 1)
                asteptare.append(vecini - 1)

#parcurgerea in adancime 
vizitate = [] 

def parcAdancime(vizitate, lista, nodul):
    if nodul not in vizitate:
        print(nodul + 1, end=' ')
        vizitate.append(nodul)
        for vecini in lista[nodul][0:len(lista[nodul]) - 1]:
            parcAdancime(vizitate, lista, vecini - 1)

def initializare(option):
    with open('graf'+option+'.in','r') as f:
        initGraf = [[int(num) for num in line.split(' ')] for line in f]

    initGraf = np.asarray(initGraf, dtype = object)

    match option:
    #matrice adiacenta
        case "1":
            lista = adiacentToList(initGraf)
    #matrice incidenta
        case "2":
            lista = incidentToList(initGraf)
    #lista
        case "3":
            lista = initGraf

    return lista

#main
os.system('cls')

option = input("1.Matricea de adiacenta 2. Matricea de incidenta 3. Lista\nAlegeti tipul de citire a grafului:")

os.system('cls')

lista = initializare(option)

afisList(lista)
init = int(input("\nDati nodul de la care se va incepe parcurgerea in largime/adancime: "))
parcLargime(lista,init)

print("\nParcurgerea in adancime a grafului este : ", end='')

parcAdancime(vizitate, lista,init - 1)
