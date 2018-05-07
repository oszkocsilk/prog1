def swap(a,b):
    
    a = a ^ b
    b = a ^ b
    a = a ^ b
    return a,b


a = input("a = ")
b = input("b = ")

print "a =" , a , " b =" , b , "\nSWAP"
a,b = swap(a,b)
print "a =" , a , " b =" , b
