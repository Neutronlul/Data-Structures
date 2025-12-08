import random

door = 1
wins = 0
tries = 1000000
for x in range(tries):
    choice = random.randint(1, 3)
    if choice == door:
        wins += 1

print("Total Wins when not switching: ", wins / tries)


wins = 0
for x in range(tries):
    choice = random.randint(1, 3)
    if choice == door:
        pass
    else:
        wins += 1

print("Total Wins when switching: ", wins / tries)
