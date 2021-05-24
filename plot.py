import matplotlib.pyplot as plt
import math

# x axis values
x = []
# corresponding y axis values
y = []

xori = []
yori = []
  
x2 = []
y2 = []

f = open("out.dat", "r")  
n = int(f.readline())
print(n)

for i in range(1, 100):
    val = int(f.readline())
    if val > 0:
        xori.append(i)
        yori.append(val)
        x.append(math.log(i))
        y.append(math.log(val))

plt.plot(x, y, color='green', linewidth = 1,
         marker='o', markerfacecolor='blue', markersize=5)

# plt.plot(xori, yori, color='red', linewidth = 1,
#          marker='o', markerfacecolor='blue', markersize=5)

a0 = 0
a1 = 0

ax = 0
ay = 0
axy = 0
axs = 0
ns = 0
for i in range(0, len(x)-1):
    if y[i] > 0:
        ax += x[i]
        ay += y[i]
        axy += x[i]*y[i]
        axs += x[i]*x[i]
        ns += 1

a1 = (ns * axy - ax * ay)/(ns * axs - ax*ax)
a0 = (ay/ns) - a1 * (ax/ns)

for i in range(0, len(x) - 1):
    x2.append(x[i])
    y2.append(a0 + a1*x[i])
plt.plot(x2, y2)

print(a1)

plt.legend()

# plotting the points 
# plt.plot(x, y)
  
# naming the x axis
plt.xlabel('k')
# naming the y axis
plt.ylabel('P(k)')
  
# giving a title to my graph
plt.title('Power Law Degree Distribution!')
  
# function to show the plot
plt.show()