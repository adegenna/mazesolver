import numpy as np
import matplotlib.pyplot as plt

from utils import *




def depth_first_generate( n_rows , n_cols , ij_0 , ij_f ):
    
    M = np.ones( [ n_rows , n_cols ] ) # one means wall, zero means empty space
    M_visited = np.zeros( [ n_rows , n_cols ] ) # one means visited
    
    M[ ij_0[0] , ij_0[1] ] = 1
    M[ ij_f[0] , ij_f[1] ] = 1
    M_visited[ ij_0[0] , ij_0[1] ] = 1
    M_visited[ ij_f[0] , ij_f[1] ] = 1
    
    maze_nodes = []
    maze_nodes.append( Node( ij_0[0] , ij_0[1] ) )
    
    first_move = find_possible_moves( ij_0[0] , ij_0[1] , M , 1 )
    first_move = np.random.choice( np.arange( len(first_move) ) )
    
    ij = first_move
    last_ij = ij_0
    
    IJ = []
    IJ.append( [last_ij] )
    IJ.append( [] )
    
    IJ_all = []
    
    # while( np.all(M_visited != 1) ):
        
    #     IJ[-1].append(ij)
    #     IJ_all.append( copy.deepcopy( IJ ) )
        
    return 
