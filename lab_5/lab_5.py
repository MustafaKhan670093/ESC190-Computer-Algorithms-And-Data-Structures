## Mustafa Khan and Jonah Chen Lab 5 Submission

import numpy as np

class Node:
    def __init__(self, name):
        self.name = name
        self.connections = []
        self.visited = False
    
    def __str__(self): 
        return self.name;


def connect(node1, node2, weight):
    node1.connections.append({"node": node2, "weight": weight})
    node2.connections.append({"node": node1, "weight": weight})


def BFS(node):
    q = [node]
    node.visited = True
    while len(q) > 0:
        cur = q.pop(0) # remove q[0] from q and put it in cur
        print(cur.name)
        for con in cur.connections:
            if not con["node"].visited:
                q.append(con["node"])
                con["node"].visited = True


################################################################################

def get_all_nodes(node):
    '''Return a list of the nodes in the graph of nodes connected to node
    (N.B., the nodes can be indirectly connected as well)'''
    q = [node]
    all_nodes = []
    node.visited = True
    while len(q) > 0:
        cur = q.pop(0) # remove q[0] from q and put it in cur
        all_nodes.append(cur);
        for con in cur.connections:
            if not con["node"].visited:
                q.append(con["node"])
                con["node"].visited = True
    return all_nodes


# Add the starting node to the queue
# deque (get node n) -> n is visited, add all unvisited nodes from n to the queue
# keep going until queue is empty
################################################################################

def unvisit_all(node):
    '''Change all n.visited to False in all the nodes in the graph of nodes
    connected to node. Use BFS to find all the nodes'''
    q = [node]
    node.visited = False
    while len(q) > 0:
        cur = q.pop(0) # remove q[0] from q and put it in cur
        for con in cur.connections:
            if con["node"].visited:
                q.append(con["node"])
                con["node"].visited = False


###############################################################################

def DFS_rec(node):
    '''Print out the names of all nodes connected to node using a
    recursive version of DFS'''
    node.visited = True
    print(node.name)
    for con in node.connections:
        if con["node"].visited == False:
            DFS_rec(con["node"])
            


################################################################################

def DFS_nonrec(node):
    '''Print out the names of all nodes connected to node using a non-recursive
    version of DFS. Make it so that the nodes are printed in the same order
    as in DFS_rec'''
    stack = []
    stack.append(node)
    while len(stack) != 0:
        temp = stack.pop()
        if temp.visited == False:
            temp.visited = True;
            print(temp.name)
        for con in temp.connections[::-1]:
            if con["node"].visited == False:
                stack.append(con["node"])

################################################################################
#
# OPTIONAL
#

# def dijsktra_slowish(node):
#     '''Implement Dijkstra's algorithm as discussed in class (i.e., you don't
#     need to use a priority queue'''
#     S = [node]
#     d = {node.name: 0}

#     unexplored = get_all_nodes(node)
#     unexplored.remove(node)

#     while len(unexplored) > 0:
#         # your code here
#         pass

#     return d




if __name__ == '__main__':
    TO = Node("TO")
    NYC = Node("NYC")
    DC = Node("DC")
    CDMX = Node("CDMX")
    SF = Node("SF")

    connect(TO, NYC, 3)
    connect(TO, SF, 6)
    connect(TO, CDMX, 7)
    connect(NYC, DC, 2)
    connect(SF, DC, 5)
    
    # L = get_all_nodes(TO)
    # unvisit_all(TO)
    # # print(L)
    # L_list = []
    # for i in L:
    #     L_list.append(i.visited)
    # print(L_list)
    
    DFS_rec(NYC)
    unvisit_all(NYC)
    print(" ")
    DFS_nonrec(NYC)

    # DFS(TO)
    # #DFS_rec(TO)
    # unvisit_all(TO)
    # DFS(TO)
    # print(dijsktra_slowish(TO))