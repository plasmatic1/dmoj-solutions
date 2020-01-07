# Test thing

babyBowl = int(input())
mamaBowl = int(input())
papaBowl = int(input())

mama = babyBowl+mamaBowl+papaBowl - max(babyBowl,mamaBowl,papaBowl) - min(babyBowl,mamaBowl,papaBowl)
print(mama)