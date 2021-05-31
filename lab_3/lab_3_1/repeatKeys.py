from os import write
from random import randint, shuffle;

MIN = 10000000
MAX = 99999999

seed = randint(MIN, MAX)

nums = list()
for i in range(15000):
    seed = seed + 1

    for j in range(10):
        nums.append(seed)

shuffle(nums)

with open("N410.txt", "w", encoding="utf-8") as f:
    stringCount = 0

    for num in nums:
        f.write(f"{num} ")
        stringCount = stringCount + 1

        if (stringCount == 10):
            f.write("\n")
            stringCount = 0

nums = list()
for i in range(1500):
    seed = seed + 1

    for j in range(100):
        nums.append(seed)

shuffle(nums)

with open("N4100.txt", "w", encoding="utf-8") as f:
    stringCount = 0

    for num in nums:
        f.write(f"{num} ")
        stringCount = stringCount + 1

        if (stringCount == 10):
            f.write("\n")
            stringCount = 0

nums = list()
for i in range(300):
    seed = seed + 1

    for j in range(500):
        nums.append(seed)

shuffle(nums)

with open("N4500.txt", "w", encoding="utf-8") as f:
    stringCount = 0

    for num in nums:
        f.write(f"{num} ")
        stringCount = stringCount + 1

        if (stringCount == 10):
            f.write("\n")
            stringCount = 0

nums = list()
for i in range(150):
    seed = seed + 1

    for j in range(1000):
        nums.append(seed)

shuffle(nums)

with open("N41000.txt", "w", encoding="utf-8") as f:
    stringCount = 0

    for num in nums:
        f.write(f"{num} ")
        stringCount = stringCount + 1

        if (stringCount == 10):
            f.write("\n")
            stringCount = 0