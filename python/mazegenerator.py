import numpy as np
import matplotlib.pyplot as plt


def easy_random_maze_gen( n , m ):
    
    if (n%2 == 0):
        n += 1
    if (m%2 == 0):
        m += 1
    
    M = np.ones( [ n , m ] )
    
    nsew = np.array( [ [-1,0] , [1,0] , [0,1] , [0,-1] ] )
    
    for i in range((n-1)//2):
        for j in range((m-1)//2):
            i0 = 2*i + 1
            j0 = 2*j + 1
            path = nsew[ np.random.choice(np.arange(4)) ]
            I = np.minimum( np.maximum( i0 + path[0] , 0 ) , n-1 )
            J = np.minimum( np.maximum( j0 + path[1] , 0 ) , m-1 )
            M[ I , J ] = 0
            M[ i0 , j0 ] = 0
    
    M = -M + 1
    for i in range( m*n//12 ):
        M[ np.random.choice( np.arange(n) ) , np.random.choice( np.arange(m) ) ] = 1
    M[0] = 0; M[-1] = 0; M[:,0] = 0; M[:,-1] = 0
    M[0] = 1; M[-1] = 1
    
    Mpad = np.ones( [ n+2 , m+2 ] )
    Mpad[ 1:-1 , 1:-1 ] = M.copy()
    Mpad[ (n+1)//2 , 0 ] = 0
    Mpad[ (n+1)//2 , -1 ] = 0
    
    return Mpad
    
    
if __name__ == '__main__':
    
    M = easy_random_maze_gen( 32 , 32 )

    print( M )
    
    plt.imshow( -M+1 , vmin=0 , vmax=3 , cmap='afmhot' )
    
    plt.show()
