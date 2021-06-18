import numpy as np
import matplotlib.pyplot as plt
import itertools
from maze_examples import *



class Node( ):
    
    def __init__( self , i , j , last_ij=[-1,-1] ):
        
        self.i    = i
        self.j    = j
        self.last_ij = last_ij
        self.nxt_index = 0
        self.valid_nxt_moves = None
        
    def calculate_valid_nxt_move( self , M ):
        
        if self.valid_nxt_moves is None:
            
            self.valid_nxt_moves = []
            moves   = find_possible_moves( self.i , self.j , M )
            moves   = [ mi for mi in moves if mi != self.last_ij ]
            self.valid_nxt_moves = moves
        
        return self.valid_nxt_moves[ self.nxt_index ]
        

    

        

def find_exit_points_of_maze( M ):
    
    n1,n2 = M.shape
    zeros = np.argwhere( M == 0 )
    exits = []
    exits = [ list(zi) for zi in zeros if ( (zi[0]==0) | (zi[0]==n1-1) | (zi[1]==0) | (zi[1]==n2-1) ) ]
    
    return exits


def find_possible_moves( i , j , M ):
    
    moves = []
    
    n,m = M.shape
    
    if ( i-1 >= 0 ):
        if ( M[i-1,j] == 0 ):
            moves.append( [ i-1 , j   ] )
    
    if ( i+1 < n ):
        if ( M[i+1,j] == 0 ):
            moves.append( [ i+1 , j   ] )
    
    if ( j-1 >= 0 ):
        if ( M[i,j-1] == 0 ):
            moves.append( [ i   , j-1 ] )
    
    if ( j+1 <  m ):
        if ( M[i,j+1] == 0 ):
            moves.append( [ i   , j+1 ] )
    
    return moves


def check_if_i0j0_is_maze_node( M , i0 , j0 , last_ij ):

    # Boundary
    if ( (i0 == 0) | (i0 == M.shape[0]-1) | (j0 == 0) | (j0 == M.shape[1]-1) ):
        if ( M[i0,j0] == 0 ):
            return True
        else:
            return False
    
    # Interior
    else:
        moves_ij = find_possible_moves( i0 , j0 , M )
        moves_ij = [ mi for mi in moves_ij if ( mi != last_ij ) ]
        if len(moves_ij) > 1:
            return True
        else:
            return False


def depth_first_solve( M , ij_0 , ij_f ):
    
    maze_nodes = []
    maze_nodes.append( Node( ij_0[0] , ij_0[1] ) )
    
    first_move = find_possible_moves( ij_0[0] , ij_0[1] , M )
    assert( len(first_move) == 1 )   # assuming entrance is not a split...
    first_move = first_move[0]
    
    ij = first_move
    last_ij = ij_0
    
    IJ = []
    IJ.append( [last_ij] )
    IJ.append( [] )

    IJ_all = []
    IJ_all.append( IJ.copy() )
    
    while( np.all(ij != ij_f) ):
        
        IJ[-1].append(ij)
        IJ_all.append( IJ.copy() )
        
        if ( check_if_i0j0_is_maze_node( M , ij[0] , ij[1] , last_ij ) == True ):
                            
            maze_nodes.append( Node( ij[0] , ij[1] , last_ij ) )
            
            last_ij = [ maze_nodes[-1].i , maze_nodes[-1].j ]
            ij      = maze_nodes[-1].calculate_valid_nxt_move( M )
            
            IJ.append( [] )
            
        else:
            
            moves   = find_possible_moves( ij[0] , ij[1] , M )
            
            if ( len(moves) == 2 ): # not a dead end
                
                ij_save = ij
                ij      = [ mi for mi in moves if mi != last_ij ][0]
                last_ij = ij_save
                
            elif ( len(moves) == 1 ): # dead end case
                                
                maze_nodes[-1].nxt_index += 1
                IJ = IJ[0:-1]
                IJ.append([])
                
                while(True):
                    
                    if ( maze_nodes[-1].nxt_index >= len(maze_nodes[-1].valid_nxt_moves) ):
                        maze_nodes = maze_nodes[0:-1]
                        maze_nodes[-1].nxt_index += 1
                        IJ = IJ[0:-2]                        
                        IJ.append([])
                    else:
                        break
                
                last_ij = [ maze_nodes[-1].i , maze_nodes[-1].j ]
                ij      = maze_nodes[-1].calculate_valid_nxt_move( M )
                
            else:
                
                print( 'error' )
                break
    
    return maze_nodes , IJ , IJ_all


def main( M ):
    
    exits = find_exit_points_of_maze( M )
    assert( len(exits) == 2 ) # assume only 2 exit points of maze...
    entrance_ij = exits[0]
    exit_ij     = exits[1]
    
    maze_nodes , IJ , IJ_all = depth_first_solve( M , entrance_ij , exit_ij )
    
    print( 'COMPUTED NODAL PATH: ' )
    for n in maze_nodes:
        print( [n.i , n.j] )
    print( exit_ij )
    print('')
    
    M_node = M.copy()
    
    for ij_set in IJ:
        for ij in ij_set:
            M_node[ ij[0] , ij[1] ] = 2
    
    for n in maze_nodes:
        M_node[ n.i , n.j ] = 3
    M_node[ exit_ij[0] , exit_ij[1] ] = 3
    
    plt.figure(1)
    plt.imshow( M_node , vmin=0 , vmax=3 )
    plt.show()
    
    plt.figure()
    plt.ion()
    
    while( True ):
        
        for i in range( len(IJ_all) ):

            print( IJ_all[i] )
            M_node = M.copy()

            for ij_set in IJ_all[i]:
                for ij in ij_set:
                    M_node[ ij[0] , ij[1] ] = 2

            for n in maze_nodes:
                M_node[ n.i , n.j ] = 3
            M_node[ exit_ij[0] , exit_ij[1] ] = 3

            plt.imshow( M_node , vmin=0 , vmax=3 )
            plt.title( i+1 )
            plt.draw()
            plt.pause(0.01)
            plt.clf()
        

    

    
if __name__ == '__main__':
    
    main( make_test_maze_6() )
