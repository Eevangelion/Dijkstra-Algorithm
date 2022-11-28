#%%

import numpy as np
import matplotlib.pyplot as plt

x_list = []
y_list = []

with open("table.csv", "r") as file:
    for line in file.readlines():
        x_list.append(int(line.split()[0]))
        y_list.append(float(line.split()[1]))

x = np.array(x_list)
y = np.array(y_list)
fig, ax = plt.subplots(2, 1, figsize=(10,20))
ax[0].plot(x, y, 'bo')
ax[0].set_xlabel("Количество вершин n")
ax[0].set_ylabel("Время выполнения алгоритма T (мкс)")
ax[1].plot(x, x*x + x*(x-1), 'go')
ax[1].set_xlabel("Количество вершин n")
ax[1].set_ylabel("n^2 + m")
plt.show()
# %%
