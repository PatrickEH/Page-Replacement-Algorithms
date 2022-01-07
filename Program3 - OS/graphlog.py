import matplotlib.pyplot as plt
import pandas as pd

plt.style.use('ggplot')

#graphs the logged graphData
#plt.style.use('fivethirtyeight')
plt.figure(figsize=(5.5, 3))
data = pd.read_csv('plotlog.csv')
x = data['Frames']
y1 = data['Fifo']
y2 = data['Lru']
y3 = data['Opt']

line1, = plt.plot(x, y1, "-o", label='FIFO')
line2, = plt.plot(x, y2, "-o", label='LRU')
line3, = plt.plot(x, y3, "-o", label='OPT')

legend = plt.legend(loc='best')
plt.xticks(x[::1], rotation=90)

plt.xlabel("Available Number of Frames")  
plt.ylabel("Number of Page Faults")
plt.title('Program 3 Algorithms Plot - Peh39')
plt.tight_layout()
plt.show()


