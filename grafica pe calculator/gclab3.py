old_list = [[22,44,66],[11,33,55],[20,30,40]]
print(old_list)

new_list = []

for i in range(len(old_list)):
    new_list.append(old_list[i][-1])

print(new_list)
