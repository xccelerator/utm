import numpy as np
import pandas as pd
import os

#transforma lista in matrice de adiacenta
def listToAdiacent(initGraf):
    row = initGraf.shape[0]
    adiacent = np.zeros((row, row))

    for i in range(0,row):
        for j in initGraf[i]:
            if(j != 0):
                adiacent[i][j-1] = 1

    return adiacent.astype(int) 

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

# transforma lista in matrice de incidenta
def listToIncident(initGraf):
    col = initGraf.shape[0]
    
    row = 0

    for i in range(0,col):
        row += len(initGraf[i]) - 1

    incident = np.zeros((row,col))

    u = 0

    for i in range(0,col):
        for j in initGraf[i]:
            if(j != 0):
                incident[u][i] = -1
                incident[u][j-1] = 1
                u += 1
    return incident.astype(int) 

#matricea adiacenta in incidenta
def adiacentaToIncidenta(initGraf):
    col = np.count_nonzero(initGraf == 1)
    
    row = initGraf.shape[0]

    incident = np.zeros((col,row))
    
    u = 0
    for i in range(0,row):
        for j in range(0,row):
            if(initGraf[i][j] == 1):
                incident[u][i] = -1
                incident[u][j] = 1
                u += 1

    return incident.astype(int)

#matricea incidenta in adiacenta
def incidentaToAdiacenta(initGraf):
    row, col = initGraf.shape

    adiacent = np.zeros((col,col))
    for i in range(0,row):
        for j in range(0,col):
            if(initGraf[i][j] == -1):
                rowA = j
            if(initGraf[i][j] == 1):
                colA = j
        adiacent[rowA][colA] = 1

    return adiacent.astype(int) 

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
    
#afisarea matricei de adiacenta
def afisAdiacent(adiacent):
    row = adiacent.shape[0]
    print("\nMatrice de adiacenta:")

    column = []

    for i in range(1,row+1):
        column.append('x'+str(i))

    adiacent = pd.DataFrame(adiacent, columns = column,index=column)

    print(adiacent)

#afisarea matricei de incidenta
def afisIncident(incident):
    print("\nMatrice de incidenta:")
    
    row, col = incident.shape 

    column = []
    for i in range(1,col+1):
        column.append('x'+str(i))

    rows = []
    for i in range(1,row+1):
        rows.append('u'+str(i))

    incident = pd.DataFrame(incident, columns = column, index = rows) 
    
    print(incident)

#afiseaza toate 2 reprezentari ale grafului
def afisare(lista, incident, adiacent):
    afisList(lista)
    afisAdiacent(adiacent)
    afisIncident(incident)

#controleaza corectitudinea listei
def checkLista(lista):
    for i in range(0,lista.shape[0]):
        for j in range(0,len(lista[i])):
            if lista[i][j] > lista.shape[0]:
                return False

    return True

#controleaza corectitudinea matricei de incidenta
def checkIncidenta(incident):
    for i in range(0,incident.shape[0]):
        if np.sum(incident) != 0:
            return False

    return True

#controleaza corectitudinea matricei de adiacenta
def checkAdiacent(adiacent):
    if adiacent.shape[0] != adiacent.shape[1]:
        return False

    for i in range(0, adiacent.shape[0]):
        for j in range(0, adiacent.shape[0]):
            if not(adiacent[i][j] == 0 or adiacent [i][j] == 1):
                return False

    return True

def initializare(option):
    with open('graf'+option+'.in','r') as f:
        initGraf = [[int(num) for num in line.split(' ')] for line in f]

    initGraf = np.asarray(initGraf, dtype = object)

    match option:
    #matrice adiacenta
        case "1":
            if checkAdiacent(initGraf):
                adiacent = initGraf
                incident = adiacentaToIncidenta(initGraf)
                lista = adiacentToList(initGraf)
                return adiacent, incident, lista
            else:
                return False
    #matrice incidenta
        case "2":
            if checkIncidenta(initGraf):
                incident = np.asarray(initGraf)
                adiacent = incidentaToAdiacenta(initGraf)
                lista = adiacentToList(adiacent)
                return adiacent, incident, lista
            else:
                return False
    #lista
        case "3":
            if checkLista(initGraf):
                adiacent = listToAdiacent(initGraf)
                incident = listToIncident(initGraf)
                return adiacent, incident, initGraf
            else:
                return False

#main
os.system('cls')

option = input("1.Matricea de adiacenta 2. Matricea de incidenta 3. Lista\nAlegeti tipul de citire a grafului:")

if initializare(option) == False:
    print("\nVerificati corectitudinea datelor introduse in fisier")
else:
    adiacent, incident, lista = initializare(option)

    option = "-1"

    while option != "0":
        os.system('cls')

        afisare(lista, incident, adiacent)
        print("\n1. Adauga un varf nou\n2. Sterge un varf\n3. Adauga legatura intre doua varfuri\n4. Sterge legatura intre doua varfuri\n0. Iesirea din program")
    
        option = input("\nChoose:")


        match option:
            #adauga un varf nou
            case "1":
                #adaugarea in lista
                lista = np.array(lista.tolist() + [[0]], dtype = object)

                #adaugarea in matricea adiacenta
                adiacent = np.vstack((adiacent, np.zeros(adiacent.shape[0], dtype = int)))
                adiacent = np.hstack((adiacent, np.zeros((adiacent.shape[0], 1), dtype = int)))

                #adaugarea in matricea incidenta
                incident = np.hstack((incident, np.zeros((incident.shape[0],1), dtype = int) ))

            #sterge un varf
            case "2":    
                num = input("\nDati varful care doriti sal stergeti: ")

                #stergerea din lista
                lista = np.delete(lista, int(num) - 1, 0)

                for i in range(0,lista.shape[0]):
                    if int(num) in lista[i]:
                        lista[i].pop(lista[i].index(int(num)))

                for i in range(0, lista.shape[0]):
                    for j in range(0,len(lista[i])):
                        if lista[i][j] > int(num):
                            lista[i][j] -= 1

                #stergerea din matricea de adiacenta
                adiacent = np.delete(adiacent, int(num) - 1, 0)
                adiacent = np.delete(adiacent, int(num) - 1, 1)

                #stergerea din matricea de incidenta
                i = 0
                while i != incident.shape[0]:
                    if incident[i][int(num) - 1] != 0:
                        incident = np.delete(incident, i, 0)
                    else:
                        i += 1
                incident = np.delete(incident, int(num) - 1, 1)

            #adauga legatura intre doua varfuri
            case "3":    
                first, second = map(int, input("\nDati legaturile care doriti sa le uniti:").split())
                if(adiacent[first - 1][second - 1] == 0):

                    #legatura in lista
                    lista[first - 1].pop()
                    lista[first - 1].extend([second,0])

                    #legatura in matricea de adiacenta
                    adiacent[first - 1][second - 1] = 1

                    #legatura in matricea de incidenta
                    incident = np.vstack(( incident, np.zeros((incident.shape[1],), dtype = int) ))
                    incident[incident.shape[0] - 1][first - 1] = -1
                    incident[incident.shape[0] - 1][second - 1] = 1

            #sterge legatura intre doua varfuri    
            case "4":
                first, second = map(int, input("\nDati nodurile intre care doriti sa stergeti legatura:").split())
                if(adiacent[first - 1][second - 1] != 0):

                    #stergerea din lista
                    lista[first - 1].pop(lista[first - 1].index(second))

                    #stergerea din matricea de adiacenta
                    adiacent[first - 1][second - 1] = 0

                    #stergerea din matricea de incidenta
                    u = 0
                    while incident[u][first - 1] != -1 or incident[u][second - 1] != 1:
                        u += 1
                    incident = np.delete(incident, u, 0)
