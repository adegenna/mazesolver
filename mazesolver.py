import numpy as np
import matplotlib.pyplot as plt


def find_exit_points_of_maze( M ):
    
    n1,n2 = M.shape
    
    zeros = np.argwhere( M == 0 )
    
    exits = []
    
    exits = [ zi for zi in zeros if ( (zi[0]==0) | (zi[0]==n1-1) | (zi[1]==0) | (zi[1]==n2-1) ) ]
    
    return exits


def find_possible_moves( i , j , M ):
    
    moves = []
    
    n,m = M.shape
    
    if ( (i-1 >= 0) & (M[np.maximum(i-1,0),j] == 0) ):   moves.append( [ i-1 , j   ] )
    if ( (i+1 <  n) & (M[np.minimum(i+1,n-1),j] == 0) ): moves.append( [ i+1 , j   ] )
    if ( (j-1 >= 0) & (M[i,np.maximum(j-1,0)] == 0) ):   moves.append( [ i   , j-1 ] )
    if ( (j+1 <  m) & (M[i,np.minimum(j+1,n-1)] == 0) ): moves.append( [ i   , j+1 ] )
    
    return moves


def find_maze_nodes( M , i0 , j0 ):
    
    i = i0
    j = j0
    last_ij = [-1,-1]
    
    nodes = []
    
    while(True):
        
        moves_ij = find_possible_moves( i , j , M )
        
        moves_ij = [ mi for mi in moves_ij if ( mi != last_ij ) ]
        
        if len(moves_ij) > 1:
            nodes.append( [i,j] )
            last_ij = [i,j]
        
        elif len(moves_ij) == 0: break
        
    return nodes
        

def test_find_exits():
    
    A = np.array( [ [ np.random.choice([0,1]) for j in range(5) ] for i in range(5) ] )
    
    print(A)
    
    exits = find_exit_points_of_maze(A)
    
    print(exits)


def test_find_maze_nodes():
    
    M = np.array( [ [  1 , 1 , 1 , 0 , 1 ] ,
                    [  1 , 0 , 1 , 0 , 1 ] ,
                    [  1 , 0 , 1 , 0 , 1 ] ,
                    [  1 , 0 , 0 , 0 , 1 ] ,
                    [  1 , 0 , 1 , 1 , 1 ] ] )
    
    nodes = find_maze_nodes( M , 4 , 1 )
    
    print( M )
    print( nodes )

if __name__ == '__main__':
    
    test_find_maze_nodes()
