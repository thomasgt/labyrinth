import numpy as np
import matplotlib.pyplot as plt

maze = np.fromfile("../build/test.dat", dtype=np.int32)
maze1 = maze.reshape(1001,1001)
plt.figure()
plt.imshow(maze1)
plt.show()
