wins = sum([input() == 'W' for v in range(6)])

print((-1, 3, 3, 2, 2, 1, 1)[wins])