numar = int(input("Dati numarul:"))

if numar >= 0:
    print("Numarul dat de dumneavoastra are",len(str(numar)),"cifre")
else :
    print("Numarul dat de dumneavoastra are",len(str(numar)) - 1,"cifre")
