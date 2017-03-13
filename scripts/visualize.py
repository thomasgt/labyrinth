import numpy as np

maze = np.fromfile("../build/test.dat", dtype=np.int32)
maze1 = maze.reshape(10,10)