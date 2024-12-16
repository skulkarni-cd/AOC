import math

def det(a, b, c, d):
  return a * d - b * c

def solve(a1, b1, c1, a2, b2, c2):
  denom = det(a1, b1, a2, b2)
  numX = det(c1, b1, c2, b2)
  numY = det(a1, c1, a2, c2)

  if (denom == 0):
    return 0, 0
    
  x, y = numX / denom, numY / denom

  if (x < 0) or (y < 0):
    return 0, 0

  if (x > 100) or (y > 100):
    return 0, 0

  return math.floor(x), math.floor(y)


def main():
  f = open("AOC.txt", "r")

  lines = f.readlines()

  f.close()

  nTokens = 0  
  i = 0
  while (i < (len(lines) - 2)):
    numbersA = [int(n) for n in lines[i].split()]
    numbersB = [int(n) for n in lines[i+1].split()]
    numbersRHS = [int(n) for n in lines[i+2].split()]

    x, y = solve((numbersA[0]), (numbersB[0]), (numbersRHS[0]), (numbersA[1]), (numbersB[1]), (numbersRHS[1]))
    print(x, y)

    nTokens += 3 * x + y

    i += 4

  print(nTokens)

main()
