### Hilal Ekinci - 150114057
### Project 1 - Peg Solitaire Game

from copy import deepcopy
import time
import queue
from random import shuffle
import sys

initial_state_numbers = [ #List for calculating the total numbers
    [0, 0, 1, 2, 3, 0, 0],
    [0, 0, 4, 5, 6, 0, 0],
    [7, 8, 9, 10, 11, 12, 13],
    [14, 15, 16, 17, 18, 19, 20],
    [21, 22, 23, 24, 25, 26, 27],
    [0, 0, 28, 29, 30, 0, 0],
    [0, 0, 31, 32, 33, 0, 0]]

initial_state = [
    ['X', 'X', '1', '1', '1', 'X', 'X'],
    ['X', 'X', '1', '1', '1', 'X', 'X'],
    ['1', '1', '1', '1', '1', '1', '1'],
    ['1', '1', '1', '0', '1', '1', '1'],
    ['1', '1', '1', '1', '1', '1', '1'],
    ['X', 'X', '1', '1', '1', 'X', 'X'],
    ['X', 'X', '1', '1', '1', 'X', 'X']]

goalState = [
    ['X', 'X', '0', '0', '0', 'X', 'X'],
    ['X', 'X', '0', '0', '0', 'X', 'X'],
    ['0', '0', '0', '0', '0', '0', '0'],
    ['0', '0', '0', '1', '0', '0', '0'],
    ['0', '0', '0', '0', '0', '0', '0'],
    ['X', 'X', '0', '0', '0', 'X', 'X'],
    ['X', 'X', '0', '0', '0', 'X', 'X']]


frontier = []
board = initial_state
q = queue.Queue()  # Queue for BFS.
s = []  # Stack for DFS.

class Node: # My Class to hold attributes of elements in the frontier list
    def __init__(self, board, parent, depth = 0):
        self.board = board
        self.parent = parent
        self.depth = depth

def printboard(board):  # Print the board
    print("-" * 15)
    for i in range(7):
        for j in range(7):
            if board[i][j] == 'X':
                print("  ", end="")
            elif board[i][j] == '1':
                print(" O", end="")
            else:
                print(" X", end="")
        print("")
    print("-" * 15)


def print_board_positions(node): #Print board positions of all steps
    d = node
    while d.parent != None:
        printboard(d.board)
        d = d.parent
    printboard(initial_state)


def remaining_peg(board): #Calculates the number of remaining pegs
    remaining_peg = 0

    for x in range(0, 7):
        for y in range(0, 7):
            if board[x][y] == '1':
                remaining_peg += 1
            else:
                continue

    return  remaining_peg


def peg_movement(x, y, board): # Check for peg movement regarding to x and y position values.
    movement = False
    peg_movements = []  # [a, b, c ,d]: (a, b) -> (c, d)
    if board[x][y] == '1':
        if ((x + 1) <= 6) and ((x + 2) <= 6):
            if board[x + 1][y] == '1' and board[x + 2][y] == '0':  # Right
                movement = True
                peg_movements.append([x, y, x + 2, y])
        if ((x - 1) >= 0) and ((x - 2) >= 0):
            if board[x - 1][y] == '1' and board[x - 2][y] == '0':  # Left
                movement = True
                peg_movements.append([x, y, x - 2, y])
        if ((y + 1) <= 6) and ((y + 2) <= 6):
            if board[x][y + 1] == '1' and board[x][y + 2] == '0':  # Up
                movement = True
                peg_movements.append([x, y, x, y + 2])
        if ((y - 1) >= 0) and ((y - 2) >= 0):
            if board[x][y - 1] == '1' and board[x][y - 2] == '0':  # Down
                movement = True
                peg_movements.append([x, y, x, y - 2])

        if movement is False:
            return None
        return peg_movements
    else:
        return None


def board_movement(board): # Check and get all possible peg movements in the board.
    board_movements = []
    for x in range(0, 7):
        for y in range(0, 7):
            if board[x][y] == '1':
                found_movements = peg_movement(x, y, board)
                if found_movements:
                    board_movements.extend(found_movements)
            else:
                continue

    return board_movements

def apply_movement(movement, board):
    if len(movement) != 4:
        return board
    # (a, b) -> (c, d)
    a = movement[0]
    b = movement[1]
    c = movement[2]
    d = movement[3]
    if (a == c) and (board[c][d] != 'X') and (board[a][b] != 'X'):  # Vertical Movement
        board[c][d] = '1'
        board[a][b] = '0'
        board[a][(b + d) // 2] = '0'
        return board
    elif (b == d) and (board[c][d] != 'X') and (board[a][b] != 'X'):  # Horizontal Movement
        board[c][d] = '1'
        board[a][b] = '0'
        board[(a + c) // 2][b] = '0'
        return board
    else:
        print('Wrong movement!')
        return board


def sort_according_to_total_number(bm): #Condition of the assignment, total number calculator and sort the movements
    for i in range(len(bm)):
        sum = 0
        x = bm[i][0]
        y = bm[i][1]
        sum = sum + initial_state_numbers[x][y] #Calculate numbers in coordinate(x,y)
        x = bm[i][2]
        y = bm[i][3]
        sum = sum + initial_state_numbers[x][y] #Calculate numbers in coordinate(x,y)
        bm[i].append(sum)

    newList = []
    for i in range(len(bm)):
        newList.append(bm[i][4])
    newList.sort()

    sorted = []
    for i in range(len(newList)):
        newList.count(newList[i])
        for j in range(len(bm)):
            if newList[i] == bm[j][4]:
                a =bm[j][:-1]
                sorted.append(a)
    return sorted

def check_no_valid_moves(board): #Checks whether there is movement in the board
    remaining_movements = board_movement(board)
    if len(remaining_movements) == 0:
        return True
    else:
        return False

def node_selection(moveLists): #Node Selection Heuristic
    listOfMovements = moveLists

    # The list we put into frontier secondly
    list = [[1,2], [1,3], [1,4],
            [2,1], [3,1], [4,1],
            [2,5], [3,5], [4,5],
            [5,2], [5,3], [5,4]]

    # The list we put into frontier firstly
    list_prior = [[0,2], [0,3], [0,4],
                  [2,0], [3,0],[4,0],
                  [2,6], [3,6],[4,6],
                  [6,2], [6,3],[6,4]]

    for i in range(len(listOfMovements)):
        move = listOfMovements[i][0:2]
        if move in list:
            newMove = listOfMovements.pop(i) #Get the movements
            listOfMovements.append(newMove)  #put them to the stack again

    for i in range(len(listOfMovements)):
        move = listOfMovements[i][0:2]
        if move in list_prior:
            newMove = listOfMovements.pop(i) #Get the movements
            listOfMovements.append(newMove)  #put them to the stack again

    return listOfMovements


def DFS(board, time_limit): #DFS
    print("\nDFS started.")
    num_peg_left = 32
    best_board_ever = None
    start=time.time()
    timeout=time.time()+time_limit
    frontier = s
    nodes_generated = 0
    nodes_expanded = 0
    b = deepcopy(board)
    node_initial = Node(b, None)
    frontier.append(node_initial)
    while True:
        nodePop = frontier.pop()
        possible_movements = board_movement(nodePop.board) #Get the movements and sort the movements according to restriction of homework

        for possible_movement in reversed(sort_according_to_total_number(possible_movements)):
            par = deepcopy(nodePop)
            parx = deepcopy(nodePop.board)
            moved = apply_movement(possible_movement, parx)
            newNode = Node(board=moved, parent=par)
            if moved == goalState: # Check if it is goal state
                print('Optimum solution found!')
                print("# of nodes generated: ", nodes_generated)
                print("# of nodes expanded : ", nodes_expanded)
                print("DFS took %d seconds" % (time.time() - start))
                return  newNode

            if time.time() > timeout: #Check the time limit
                print("Timeout!!!")
                print("DFS took %d seconds" % (time.time() - start))
                print("# of nodes generated: ", nodes_generated)
                print("# of nodes expanded : ", nodes_expanded)
                print("Sub-optimum Solution Found with %d remaining pegs"  %num_peg_left)
                return  best_board_ever

            peg = remaining_peg(nodePop.board) #Calculate how many remaining peg for sub-optimum solution

            if (peg < num_peg_left): #Check the best sub-optimal solution ever
                num_peg_left = peg
                best_board_ever = nodePop

            frontier.append(newNode)
            nodes_generated += 1
        nodes_expanded += 1


def BFS(board, time_limit): #BFS
    print("\nBFS started.")
    num_peg_left = 32
    best_board_ever = None
    start=time.time()
    timeout=time.time()+ time_limit
    frontier = q
    nodes_generated = 0
    nodes_expanded = 0
    b = deepcopy(board)
    node_initial = Node(b, None)
    frontier.put(node_initial)
    while True:
        nodePop = frontier.get()
        possible_movements = board_movement(nodePop.board)

        for possible_movement in sort_according_to_total_number(possible_movements):
            par = deepcopy(nodePop)
            parx = deepcopy(nodePop.board)
            moved = apply_movement(possible_movement, parx)
            newNode = Node(board=moved, parent=par)
            if moved == goalState:
                print('Optimum solution found!')
                print("# of nodes generated: ", nodes_generated)
                print("# of nodes expanded : ", nodes_expanded)
                print("BFS took %d seconds" % (time.time() - start))
                return  newNode
            if time.time() > timeout:
                print("Timeout!!!")
                print("BFS took %d seconds" % (time.time() - start))
                print("# of nodes generated: ", nodes_generated)
                print("# of nodes expanded : ", nodes_expanded)
                print("Sub-optimum Solution Found with %d remaining pegs   " % num_peg_left)
                return  best_board_ever

            frontier.put(newNode)
            nodes_generated += 1
        peg = remaining_peg(nodePop.board)
        if peg < num_peg_left: #Check the best sub-optimal solution ever
            num_peg_left = peg
            best_board_ever = nodePop

        nodes_expanded += 1

def DFS_random_selection(board, time_limit): #DFS with random selection
    print("\nDFS with random selection started.")
    start=time.time()
    timeout=time.time()+ time_limit
    num_peg_left = 32
    best_board_ever = None
    frontier = s
    nodes_generated = 0
    nodes_expanded = 0
    b = deepcopy(board)
    node_initial = Node(b, None)
    frontier.append(node_initial)
    while True:
        nodePop = frontier.pop()
        possible_movements = board_movement(nodePop.board)
        shuffle(possible_movements)
        for possible_movement in (possible_movements):
            par = deepcopy(nodePop)
            parx = deepcopy(nodePop.board)
            moved = apply_movement(possible_movement, parx)
            newNode = Node(board=moved, parent=par)
            if moved == goalState:
                print('Optimum solution found!')
                print("# of nodes generated: ", nodes_generated)
                print("# of nodes expanded : ", nodes_expanded)
                print("DFS with random selection took %d seconds" % (time.time() - start))
                return  newNode

            if time.time() > timeout:
                print("Timeout!!!")
                print("DFS with random selection took %d seconds" % (time.time() - start))
                print("# of nodes generated: ", nodes_generated)
                print("# of nodes expanded : ", nodes_expanded)
                print("Sub-optimum Solution Found with %d remaining pegs   " % num_peg_left)
                return  best_board_ever

            peg = remaining_peg(nodePop.board)
            if peg < num_peg_left: #Check the best sub-optimal solution ever
                num_peg_left = peg
                best_board_ever = nodePop

            frontier.append(newNode)
            nodes_generated += 1
        nodes_expanded += 1

def IDS(board, time_limit): # Iterative deepeing search
    print("\nIDS started.")
    start = time.time()
    timeout = time.time() + time_limit
    num_peg_left = 32
    best_board_ever = None
    frontier = s
    b = deepcopy(board)
    node_initial = Node(b, None,0) #Holds the depth
    frontier.append(node_initial)
    tot = 0

    for i in range(32):
        d = 0
        frontier = s
        nodes_generated = 0
        b = deepcopy(board)
        node_initial = Node(b, None, 0)
        frontier.append(node_initial)

        while (len(frontier) > 0):
            nodePop = frontier.pop()
            possible_movements = board_movement(nodePop.board)
            for possible_movement in reversed(sort_according_to_total_number(possible_movements)):
                if nodePop.depth < i: # Put the nodes into frontier if the depth is less
                    par = deepcopy(nodePop)
                    parx = deepcopy(nodePop.board)
                    moved = apply_movement(possible_movement, parx)
                    newNode = Node(board=moved, parent=par, depth= (nodePop.depth + 1))
                    frontier.append(newNode)
                    nodes_generated += 1

                if time.time() > timeout:
                    print("Timeout!!!")
                    print("IDS with random selection took %d seconds" % (time.time() - start))
                    print("Sub-optimum Solution Found with %d remaining pegs   " % num_peg_left)
                    return best_board_ever

                peg = remaining_peg(nodePop.board)

                if (peg < num_peg_left): #Check the best sub-optimal solution ever
                    num_peg_left = peg
                    best_board_ever = nodePop

        tot += nodes_generated + 1
        print("At depth %d: # of nodes generated is %d,  total # of nodes generated %d" % (i, nodes_generated + 1, tot))

def DFS_with_heuristic(board, time_limit): #DFS with node selection heuristic
    print("\nDFS with node selection heuristic started.")
    num_peg_left = 32
    best_board_ever = None
    start=time.time()
    timeout=time.time()+ time_limit
    frontier = s
    nodes_generated = 0
    nodes_expanded = 0
    b = deepcopy(board)
    node_initial = Node(b, None)
    frontier.append(node_initial)
    while True:
        nodePop = frontier.pop()
        possible_movements = board_movement(nodePop.board)

        for possible_movement in node_selection(possible_movements): #Put the movements into frontier with heuristic
            par = deepcopy(nodePop)
            parx = deepcopy(nodePop.board)
            moved = apply_movement(possible_movement, parx)

            if moved == goalState:
                newNode = Node(board=moved, parent=par)
                print('Optimal solution found!')
                print("# of nodes generated: ", nodes_generated)
                print("# of nodes expanded : ", nodes_expanded)
                print("DFS with node selection heuristic took %d seconds" % (time.time() - start))
                return  newNode

            if time.time() > timeout:
                print("Timeout!!!")
                print("%d seconds" % (time.time() - start))
                print("# of nodes generated: ", nodes_generated)
                print("# of nodes expanded : ", nodes_expanded)
                print("Sub-optimum Solution Found with %d remaining pegs   " % num_peg_left)
                return  best_board_ever

            if check_no_valid_moves(board) == False: #if no movement, do not put it into frontier
                newNode = Node(board=moved, parent=par)
                frontier.append(newNode)
                nodes_generated += 1

                peg = remaining_peg(nodePop.board)

                if (peg < num_peg_left): #Check the best sub-optimal solution ever
                    num_peg_left = peg
                    best_board_ever = nodePop

        nodes_expanded += 1



if __name__ == '__main__':
   print ("a. BFS\nb. DFS\nc. IDS\nd. DFS with Random Selection\ne. DFS with a Node Selection Heuristic")
   method = input("Choose a search method: ")
   time_limit = input("Enter time limit in minutes: ")

   try:
       time_limit = int(time_limit)
       time_limit = time_limit * 60
       if time_limit <= 0:
           print("Time limit is less or equal to 0!")
           sys.exit(0)
       print("Time limit is:", time_limit / 60, "minutes")
       if (method == 'a'):
           node = BFS(initial_state, time_limit)
       elif (method == 'b'):
           node = DFS(initial_state, time_limit)
       elif (method == 'c'):
           node = IDS(initial_state, time_limit)
       elif (method == 'd'):
           node = DFS_random_selection(initial_state, time_limit)
       elif (method == 'e'):
           node = DFS_with_heuristic(initial_state, time_limit)
       else:
           print("Wrong character input for search method!")
           sys.exit(0)
       print_board_positions(node)

   except ValueError:
       print("Time limit is not an integer!")









