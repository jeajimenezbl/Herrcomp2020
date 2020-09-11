import numpy as np
import matplotlib.pyplot as plt

datax,datay = np.loadtxt('datos.txt',unpack=True)

fig, ax=plt.subplots()
ax.plot (datax,datay,'r-.',label='Data')

ax.set_xlabel('Nmax')
ax.set_ylabel('Error')
ax.set_title('Errores Numericos I')

plt.legend()
plt.grid()

fig.savefig("Grafica.pdf")
