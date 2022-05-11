import matplotlib.pyplot as plt


elemente=[100,1000,10000,100000]
bublesort=[]
mergesort=[]
file=open(r'C:\Users\xccelerator\Desktop\Rezultate sortari.txt')
data=file.readlines()

bublesort = data[0].split()
mergesort = data[1].split()

#fig, axs = plt.subplots(nrows = 2, ncols = 1)

plt.plot(elemente, bublesort)
plt.plot(elemente, mergesort)

#axs[0].plot(elemente, bublesort)
#axs[1].plot(elemente, mergesort)

plt.show()

file.close()



