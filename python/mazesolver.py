import numpy as np
import matplotlib.pyplot as plt
import itertools
from maze_examples import *
import copy
import matplotlib.animation as animation
import matplotlib.cm as cm

from utils import *


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
    
    while( np.all(ij != ij_f) ):
        
        IJ[-1].append(ij)
        IJ_all.append( copy.deepcopy( IJ ) )
                
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
    
    ani = animation.ArtistAnimation(fig, frames, interval=50, blit=True,
                                repeat_delay=1000)
    ani.save('movie.mp4')



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
        
    fig = plt.figure()
    
    make_movie_of_maze_solve( -M+1 , IJ_all , entrance_ij , exit_ij , fig )
    
    plt.show()
    
    

    
if __name__ == '__main__':
    
    main( make_test_maze_6() )
