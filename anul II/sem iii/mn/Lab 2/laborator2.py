import math

a = [[17.7, 0.3, 1.4, 0.9], [0.3, 20.1, -0.8, -1.2], [1.4, -0.8, 21.9, 0.8], [0.9, -1.2, 0.8, 17.6]]
b = [11.2, -20.3, 14.4, 17.9]
ab = [[17.7, 0.3, 1.4, 0.9, 11.2], [0.3, 20.1, -0.8, -1.2, -20.3], [1.4, -0.8, 21.9, 0.8, 14.4], [0.9, -1.2, 0.8, 17.6, 17.9]]

def gauss():
    def transforma1(pp, matrice):
        for i in range(len(matrice[0])):
            if matrice[pp][pp] != 1:
                q00 = matrice[pp][pp]

                for j in range(len(matrice[0])):
                    matrice[pp][j] = matrice[pp][j] / q00

    def transforma0(r, c, matrice):
        for i in range(len(matrice[0])):
            if matrice[r][c] != 0:
                q04 = matrice[r][c]

                for j in range(len(matrice[0])):
                    print('r = ', r, 'j = ', j, 'c = ', c)
                    print('matrice[r][j] = ', matrice[r][j])
                    print('matrice[c][j] = ', matrice[c][j])
                    matrice[r][j] = matrice[r][j] - ((q04) * matrice[c][j])

    print("Metoda eliminării lui Gauss: ")
    matrice = ab.copy()
    for i in range(len(matrice)):
        transforma1(i, matrice)
        arataMatrice(matrice)

        for j in range(len(matrice)):
            if j > i:
                transforma0(j, i, matrice)
                arataMatrice(matrice)
    x = list(range(len(matrice)))
    for i in range(len(matrice), 0, -1):
        x[i - 1] = matrice[i - 1][4]
        for j in range(len(matrice)):
            if j != (i - 1):
                x[i - 1] -= x[j] * matrice[i - 1][j]
    for i in range(len(x)):
        print(f"x{i + 1} = {x[i]}")
    print("\n", end="")

def cholesky():
    print("Metoda lui Cholesky: ")
    matrice = a.copy()
    l = []
    for i in matrice:
        l.append([0] * len(i))

    for i in range(len(matrice)):
        for j in range(i + 1):
            sum1 = 0;
            if (j == i):
                for k in range(j):
                    sum1 += pow(l[j][k], 2);
                l[j][j] = math.sqrt(matrice[j][j] - sum1);
            else:
                for k in range(j):
                    sum1 += (l[i][k] *l[j][k]);
                if(l[j][j] > 0):
                    l[i][j] = (matrice[i][j] - sum1) / l[j][j]
    y = []
    for i in range(len(matrice)):
        y.append(b[i] / l[i][i])
    x = []
    for i in range(len(matrice)):
        x.append(y[i] / l[i][i])
    for i in range(len(x)):
        print(f"x{i + 1} = {x[i]}")
    print("\n", end="")

def jacobi():
    print("Metoda iterativă a lui Jacobi cu o eroare 0.001: ")
    i = 0
    x = [0] * len(a)
    conditie = True
    while(conditie):
        x_temp = x.copy()
        for i in range(len(x)):
            temp = b[i]
            for j in range(len(x)):
                if i != j:
                    temp = temp - x_temp[j] * a[i][j]
            x_temp[i] = temp / a[i][i]
        conditie = abs(x_temp[0] - x[0]) > 0.001 or abs(x_temp[1] - x[1]) > 0.001 or abs(x_temp[2] - x[2]) > 0.001 or abs(x_temp[3] - x[3]) > 0.001
        x = x_temp.copy()
        i = i + 1
    for i in range(len(x)):
        print(f"x{i + 1} = {x[i]}")
    print(i)
    print("\n", end="")


def gauss_seidel(err):
    print(f"Metoda iterativă a lui Gauss-Seidel cu o eroare {err}: ")
    x0 = [0] * len(a)
    x = [0] * len(a)
    conditie = True
    while(conditie):
        x0 = x.copy()
        for i in range(len(x)):
            temp = b[i]
            for j in range(len(x)):
                if i != j:
                    temp = temp - x[j] * a[i][j]
            x[i] = temp / a[i][i]
        conditie = abs(x[0] - x0[0]) > err or abs(x[1] - x0[1]) > err or abs(x[2] - x0[2]) > err or abs(x[3] - x0[3]) > err
    for i in range(len(x)):
        print(f"x{i + 1} = {x[i]}")
    print("\n", end="")


def arataMatrice(matrice):
    print("\n")
    for i in matrice:
        for j in i:
            print(round(j, 2), end="\t\t")
        print("\n")

arataMatrice(ab)
print("\n", end="")
gauss()
cholesky()
jacobi()
gauss_seidel(0.001)
gauss_seidel(0.00001)