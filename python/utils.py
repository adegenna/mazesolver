import numpy as np
import itertools
import copy


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

    def is_at_ij( i , j ):
        
        return ( (i == self.i) & (j == self.j) )
        


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

