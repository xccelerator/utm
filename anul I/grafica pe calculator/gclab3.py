print("*"*50)
old_list = [[22,44,66],[11,33,55],[20,30,40]]
print(old_list)

new_list = []

for i in range(len(old_list)):
    new_list.append(old_list[i][-1])

print(new_list)

print("*"*50)

lista_mea = ['Vera', ['Ion', 'Vlad', 'Petru'], 'Ana', 'Ala'] 
print(lista_mea[1][2]) 
print(lista_mea[1]) 
print(lista_mea[-1])

print("*"*50)

lista_mea = ['Vera', ['Ion', 'Vlad', 'Petru'], 'Ana', 'Ala']

for i in lista_mea: 
	print(len(i), end=" ") 

lista_mea.append("Iulian") 

print("\n",lista_mea) 

lista_mea.pop(4); 
lista_mea.insert(0,"Iulian") 

print(lista_mea)

print("*"*50)
