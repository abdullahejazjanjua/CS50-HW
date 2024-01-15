from cs50 import get_int

while True:
    height = get_int("Height for  side: ")
    if height > 0 and height <= 8:
        break
    else:
        pass


for i in range(height, 0, -1):
    for j in range(i - 1):
        print(" ", end="")
    for k in range(0, height - i + 1):
        print("#", end="")
    for l in range(2):
        print(" ", end="")
    for m in range(0, height - i + 1):
        print("#", end="")
    print()
