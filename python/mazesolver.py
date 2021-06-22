import numpy as np
import matplotlib.pyplot as plt
import itertools
from maze_examples import *
import copy
import matplotlib.animation as animation
import matplotlib.cm as cm

from mazegenerator import *
from utils import *


def backtrack( stack_nodes , list_IJ ):
    
    stack_nodes[-1].nxt_index += 1
    _ = list_IJ.pop()
    list_IJ.append([])
    
    while(True):
        
        if ( stack_nodes[-1].nxt_index >= len(stack_nodes[-1].valid_nxt_moves) ):
            _ = stack_nodes.pop()
            stack_nodes[-1].nxt_index += 1
            _ = list_IJ.pop()
            _ = list_IJ.pop()
            list_IJ.append([])
        else:
            break
    
    return stack_nodes , list_IJ



def depth_first_solve( M , ij_0 , ij_f ):
    
    maze_nodes = []
    maze_nodes.append( Node( ij_0[0] , ij_0[1] ) )
    
    first_move = find_possible_moves( ij_0[0] , ij_0[1] , M )
    #assert( len(first_move) == 1 )   # assuming entrance is not a split...
    first_move = first_move[0]
    
    ij = first_move
    last_ij = ij_0
    
    IJ = []
    IJ.append( [last_ij] )
    IJ.append( [] )
    
    IJ_all = []
    
    while( np.all(ij != ij_f) ):
        
        IJ[-1].append(ij)
        IJ_all.append( copy.deepcopy( IJ ) )
                
        if ( check_if_i0j0_is_maze_node( M , ij[0] , ij[1] , last_ij ) == True ):

            if ( ij not in [ [mi.i , mi.j] for mi in maze_nodes ] ): # if you haven't been at this node before...
                
                maze_nodes.append( Node( ij[0] , ij[1] , last_ij ) )
                
                last_ij = [ maze_nodes[-1].i , maze_nodes[-1].j ]
                ij      = maze_nodes[-1].calculate_valid_nxt_move( M )
                
                IJ.append( [] )

            else: # you have been at this node before, so it's a loop...
                
                maze_nodes , IJ = backtrack( maze_nodes , IJ )
                
                last_ij = [ maze_nodes[-1].i , maze_nodes[-1].j ]
                ij      = maze_nodes[-1].calculate_valid_nxt_move( M )
            
        else:
            
            moves   = find_possible_moves( ij[0] , ij[1] , M )
            
            if ( len(moves) == 2 ): # not a dead end
                
                ij_save = ij
                ij      = [ mi for mi in moves if mi != last_ij ][0]
                last_ij = ij_save
                
            elif ( len(moves) == 1 ): # dead end case
                
                maze_nodes , IJ = backtrack( maze_nodes , IJ )
                
                last_ij = [ maze_nodes[-1].i , maze_nodes[-1].j ]
                ij      = maze_nodes[-1].calculate_valid_nxt_move( M )
                
            else:
                
                print( 'error' )
                break
    
    return maze_nodes , IJ , IJ_all


def make_movie_of_maze_solve( M , IJ_all , entrance_ij , exit_ij , fig ):
    
    ax = fig.gca()
    
    ax.set_xticks([])
    ax.set_yticks([])
        
    frames = []
    
    for i in range( len(IJ_all) ):

        M_node = M.copy()

        for ij_set in IJ_all[i]:
            for ij in ij_set:
                M_node[ ij[0] , ij[1] ] = 2
        
        frames.append( [ ax.imshow( M_node , vmin=0 , vmax=3 , cmap='afmhot') ] )
    
    for i in range(10):
        M_node[ exit_ij[0] , exit_ij[1] ] = 2
        frames.append( [ ax.imshow( M_node , vmin=0 , vmax=3 , cmap='afmhot') ] )
    
    ani = animation.ArtistAnimation(fig, frames, interval=5, blit=True,
                                repeat_delay=1000)
    ani.save('movie.mp4')


def plot_soln( M , IJ , entrance_ij , exit_ij , fig ):
    
    ax = fig.gca()
    
    ax.set_xticks([])
    ax.set_yticks([])
    
    frames = []
    
    M_node = M.copy()
    
    for ij_set in IJ:
        for ij in ij_set:
            M_node[ ij[0] , ij[1] ] = 2
    
    M_node[ exit_ij[0] , exit_ij[1] ] = 2
    
    ax.imshow( M_node , vmin=0 , vmax=3 , cmap='afmhot')
    


def main( M ):
    
    #exits = find_exit_points_of_maze( M )
    #assert( len(exits) == 2 ) # assume only 2 exit points of maze...
    #entrance_ij = exits[0]
    #exit_ij     = exits[1]
    
    entrance_ij = [ M.shape[0]//2 , 0 ]
    exit_ij     = [ M.shape[0]//2 , M.shape[1]-1 ]
    
    maze_nodes , IJ , IJ_all = depth_first_solve( M , entrance_ij , exit_ij )
    
    fig = plt.figure()
    print( 'solved path length: ' + str(np.shape(IJ)[0]) )
    print( 'iterations taken: '   + str(np.shape( IJ_all )) )
    
    #make_movie_of_maze_solve( -M+1 , IJ_all , entrance_ij , exit_ij , fig )
    
    plot_soln( -M+1 , IJ , entrance_ij , exit_ij , fig )
    
    plt.show()
    
    

    
if __name__ == '__main__':
    
    #main( make_test_maze_loops() )
    
    M = easy_random_maze_gen( 32 , 128 )
    plt.imshow( -M+1 , vmin=0 , vmax=3 , cmap='afmhot' )
    plt.show()
    main( M )
