import numpy as np
import matplotlib.pyplot as plt
import sys
sys.path.append("../python")
from mazesolver import plot_soln


def main():

    M_file  = input( 'maze filepath: ' )
    IJ_file = input( 'soln filepath: ' )
    
    M  = np.genfromtxt( M_file  , delimiter=',').astype(int)
    IJ = np.genfromtxt( IJ_file , delimiter=',' ).astype(int)
    
    plot_soln( -M+1 , [IJ] , IJ[0] , IJ[-1] , plt.figure() )
    

if __name__ == '__main__':
    
    main()
    
    plt.show()
