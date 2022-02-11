import math

print("||||||||||Program||||||||||")
print("\tCercul")
print("    Lungime & aria")

r = int(input("Care este aria cercului?: "))

print("\nDiametrul cercului este: ",r * 2)
print("Lungimea cercului este: ", 2 * math.pi * r)
print("Aria cercului este: ", math.pi * math.pow(r, 2))

