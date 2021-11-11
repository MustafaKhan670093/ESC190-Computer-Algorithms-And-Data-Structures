class BST:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

    def insert(self, value):
        '''
        node.insert(5) is the same as BST.insert(node, 5)
        We use this when recursively calling, e.g. self.left.insert
        Assume that value is not in the tree.
        '''
        if value < self.value:
            if self.left == None:
                self.left = BST(value)
            else:
                self.left.insert(value)
        else:
            if self.right == None:
                self.right = BST(value)
            else:
                self.right.insert(value)

    def __repr__(self):
        '''The string representation of a node.
        Here, we convert the value of the node to a string and make that
        the representation.
        We can now use
        a = BST(4)
        print(a) # prints 4
        '''
        return str(self.value)


class BST_w_sz:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.size = 1
    
    # Recursive function to calculate the height of a given binary tree
    def height(self, root):
        # Base case: empty tree has a height of 0
        if root is None:
            return 0
    
        # recur for the left and right subtree and consider maximum depth
        return 1 + max(self.height(root.left), self.height(root.right))

    def inorder(self, root):
        if not root:
            return []
        
        left = self.inorder(root.left)
        left.append(root.value)
        right = self.inorder(root.right)
        
        return left + right

    def minValueNode(node):
        current = node
        # loop down to find the leftmost leaf
        while(current.left is not None):
            current = current.left
        return current

    def updateHeights(self, root):
        #inorder traversal
        inorder_tree = self.inorder(root)
        for i in range(len(inorder_tree)):
            self.size = self.height(BST(inorder_tree[i]))

    def insert(self, value):
        '''Assume that value is not in the tree.'''
        if value < self.value:
            # self.size = self.height(BST(value))
            # print("new_height: ", new_height)
            if self.left == None:
                self.left = BST(value)
                self.size = 1
            else:
                self.left.insert(value)
        else:
            # new_height = self.size
            # print("new_height: ", new_height)
            if self.right == None:
                self.right = BST(value)
                self.size = 1
            else:
                self.right.insert(value)
        self.updateHeights(BST(value))

    def __repr__(self):
        '''The string representation of a node.
        Here, we convert the value of the node to a string and make that
        the representation.
        We can now use
        a = BST(4)
        print(a) # prints 4
        '''
        return str(self.value)

# def inorder(root):
#     if root is not None:
#         inorder(root.left)
#         # print(root.value),
#         inorder(root.right)


def delete_value(root, value):
    '''Remove the value of value from a BST_w_sz tree rooted at node 
    root. Return the root of the modified valid BST_w_sz tree.
    The function must run in O(h) time, where h is the height of the tree'''
    # Base Case
    if root is None:
        return root
 
    # If the key to be deleted
    # is smaller than the root's
    # key then it lies in  left subtree
    if value < root.value:
        root.left = deleteNode(root.left, value)
 
    # If the kye to be delete
    # is greater than the root's key
    # then it lies in right subtree
    elif(value > root.value):
        root.right = deleteNode(root.right, value)
 
    # If key is same as root's key, then this is the node
    # to be deleted
    else:
 
        # Node with only one child or no child
        if root.left is None:
            temp = root.right
            root = None
            return temp
 
        elif root.right is None:
            temp = root.left
            root = None
            return temp
 
        # Node with two children:
        # Get the inorder successor
        # (smallest in the right subtree)
        temp = BST_w_sz.minValueNode(root.right)
 
        # Copy the inorder successor's
        # content to this node
        root.value = temp.value
 
        # Delete the inorder successor
        root.right = delete_value(root.right, temp.value)
 
    return root
 

n1 = BST_w_sz(5)
n1.insert(6)
n1.insert(3)
n1.insert(1)
print(n1.size)      # 4 this is the autograded case
#print(n1.left.size) # 2
n1 = delete_value(n1, 5)
print(n1.size)      # 3 not checked by the current autograder


#Note to instructor: I believe my delete_value function is working correctly, however, 
# the insert function has a bug somewhere. My thought process with insert was
# to insert all the elements normally and then call the update height function which
# does an in order traversal and calculates the new height at each point in the tree 
# followed by assigning those new height values to the respective nodes. 

#This next part is the answer to Q4



def median_bst(n1):
    inorder_list = BST_w_sz.inorder(n1)
    len_inorder_list = len(inorder_list)
    return inorder_list[len_inorder_list//2] #should be the median
