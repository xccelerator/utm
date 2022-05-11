import numpy as np 

def afisList(lista):
    num = lista.shape[0]
    for i in range(1,num+1):
        print(i,'- ',end='')
        for j in lista[i-1]:
            if(j != 0):
                print(str(j)+'_',end = '')
            else:
                print(j)

def initializare():
    with open('graf3.in','r') as f:
        initGraf = [[int(num) for num in line.split(' ')] for line in f]

    return np.asarray(initGraf, dtype = object)

def checkN(node):
    for i in node:
        if i == 0:
            return True

    return False

def grafAcoperire(lista, start):
    FA1 = []
    FA2 = []
    num = lista.shape[0]

    node = [0] * num
    node[start - 1] = 1
    FA1.append(start)

    while checkN(node):
        if FA1:
            current = FA1.pop(0)
            node[current - 1] = 1

            for i in lista[current - 1]:
                if i != 0 and node[i - 1] == 0 and i not in FA2:
                    FA2.append(i)

            #sterge muchiile care leaga nodurile din FA2
            for i in FA2:
                lista[i - 1] = [x for x in lista[i - 1] if x not in FA2]

            #sterge toate muchiile in afara de una care leaga fiecare varf din FA2 cu varfurile din FA1
            for i in FA2:
                lista[i - 1] = [x for x in lista[i - 1] if x not in FA1]

            for i in FA1:
                lista[i - 1] = [x for x in lista[i - 1] if x not in FA2]

        else :
            t = FA1
            FA1 = FA2
            FA2 = t

        if not FA1 and not FA2:
            for i in range(len(node)):
                if node[i] == 0:
                    FA1.append(i+1)

lista = initializare()

print("Lista de adiacenta:")
afisList(lista)

grafAcoperire(lista, 1)

print("\nGraful de acoperie:")
afisList(lista)
