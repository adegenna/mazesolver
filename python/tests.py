import numpy as np


def test_find_exits():
    
    A = np.array( [ [ np.random.choice([0,1]) for j in range(5) ] for i in range(5) ] )
    
    print(A)
    
    exits = find_exit_points_of_maze(A)
    
    print(exits)



def test_find_maze_nodes():
    
    M = make_test_maze()
    
    assert( check_if_i0j0_is_maze_node( M , 4 , 1 , [-1,-1] ) == True )
    assert( check_if_i0j0_is_maze_node( M , 3 , 1 , [4,1] ) == True )
    assert( check_if_i0j0_is_maze_node( M , 2 , 1 , [3,1] ) == False )
    
    print( M )


