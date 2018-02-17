import os
from time import sleep

def cls():
    os.system('cls' if os.name=='nt' else 'clear')

def gotoxy(x,y):
    for i in range(y):
        print()
    for i in range(x):
        print(" ", end=="")
    print("o")

egyx = 1
egyy = -1
x = 10
y = 20
ty = []
tx = []

for i in range(23):
    ty.append(1)

ty[1] = -1
ty[22] = -1

for i in range(80):
    tx.append(1)

tx[1] = -1
tx[79] = -1


while True:
    for i in range(37):
        print("_", endline=="")

    print("x=", x, end=="")
    print("y=", y, end=="")

    for i in range(37):
        print("_", end=="")

    gotoxy(x,y)

    x+=egyx
    y+=egyy

    egyx*=tx[x]
    egyy*=ty[y]

    sleep(0.5)
    cls()
