import matplotlib.pyplot as plt

num = [10, 50, 100,200,300,400,500,600,700,800,900,1000]

def readFile(file):
    with open(file) as f:
        data = [[int(num) for num in line.split(' ')] for line in f]
    return data[0], data[1], data[2]

"""
bubble, quick, merge= readFile("crescator.out")

print("crescator")
print(bubble)
print(quick)
print(merge)

plt.plot(num, bubble, 'r', num, quick, 'g', num, merge, 'b')
plt.title('Crescator')
plt.legend(['Bubble','Quick', 'Merge'])
plt.show()

bubble, quick, merge= readFile("descrescator.out")
print("descrescator")
print(bubble)
print(quick)
print(merge)
plt.title('Descrescator')
plt.plot(num, bubble, 'r', num, quick, 'g', num, merge, 'b')
plt.legend(['Bubble','Quick', 'Merge'])
plt.show()

"""
bubble, quick, merge= readFile("aleatoriu.out")
plt.title('Aleatoriu')
plt.plot(num, quick, 'g', num, merge, 'b')
plt.legend(['Quick', 'Merge'])
plt.show()

"""
print(crescator)
print(descrescator)
print(aleatoriu)
"""
