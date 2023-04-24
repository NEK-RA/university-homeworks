from math import *

# a = 0.34 * Pi * arctg(x) + e ^ abs(4 * x - k) + 18deg
def funcA(x,k):
  result = 0.34 * pi * atan(x) + e**abs(4*x - k)
  d2r = 18 / (180 / pi)
  result += d2r
  return result

# b = (sqrt(a*x^2 + y^2) / (2.5*a)) + 0.05 * cubicsqrt(10*y) + c * ln(x * y) + a^3 * lg(x)
def funcB(x,y,a,c):
  result = sqrt(a*(x**2) + (y**2)) / (2.5*a)
  result += 0.05 * (10*y)**(1/3)
  result += c * log(x * y)
  result += (a**3) * log10(x)
  return result

print("a =",funcA(2,6))
print("b =",funcB(3,7,2,10))