from itertools import combinations
import random

print("100 8 10")
for i in range(100):
    s = random.randint(1, 3)
    e = random.randint(8, 9)
    d = random.randint(1, 3)

    string = ""
    
    for j in range(s, e, d):
        string = string + str(j) 
    
    c = combinations(string, len(string))
    
    print("%d       %d       %s" % (i, len(string), ' '.join(next(c))))

