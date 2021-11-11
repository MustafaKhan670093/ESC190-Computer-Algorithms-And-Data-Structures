#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define CAPACITY 1000

typedef struct node 
{
    int value;
    struct node* left;
    struct node* right;
} node_t;

void insert (node_t *root, int value)
{
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    assert(new_node); //checks whether memory is allocated successfully
    
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    if(value > root->value){
        if(root->right==NULL){
            root->right=new_node;
            return;
        }
        insert(root->right, value);
    }
    else{
        if(root->left==NULL){
            root->left=new_node;
            return;
        }
        insert(root->left, value);
    }
}

//assume values can be repeated
// O(height of tree)
int search(node_t* const root, int value){
    if(root->value == value){
        return 1;
    }
    else if(root == NULL){
        return 0;
    }
    else{
        if(value > root->value){
            return search(root->right, value);
        }
        else{
            return search(root->left, value);
        }
    }
}

//static inline means you're not calling the function, static refers to the scope (in this translation unit/file). A translation unit is code that is passed to the compiler proper. 
static inline void min(node_t* root) 
{
    while (root->left)
        root = root->left;
    return root->value;
}

static inline void max(node_t* root) 
{
    while (root->right)
        root = root->right;
    return root->value;
}


//Assume root doesn't get deleted
node_t* delete(node_t * root, int value){
    
    if (!root) return NULL;
    
    if (value > root->value)
        root->right = delete(root->right, value);
    else if (value < root->value)
        root->left = delete(root->left, value);
    else 
    {
        // if no left and right child
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        //if no left child
        if(root->left == NULL)
        {
            node_t* tmp = root->right;
            free(root);
            return tmp;
        }
        //if no right child
        if(root->right==NULL){
            node_t* tmp = root->left;
            free(root);
            return tmp;
        }
        //if there are two children
        else{
            node_t* tmp = root->right;
            while (tmp->left)
                tmp = tmp->left;
            root->value = tmp->value;
            root->right = delete(root->right, tmp->value);
        }   
    }
    return root;
}

// Problem 1
// Draw (manually) the binary tree rooted in a.

/*
          4
        /  \
       2    5
       \   / \
        3    10
              \
              15
 */


// Problem 2
// Write code to find the height of a Binary Search Tree
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

int get_height (node_t *root)
{
    if (root==NULL)
        return 0;
    
    int lh = get_height(root->left), rh = get_height(root->right);
    return 1 + MAX(lh,rh); // the max of the left subtree and right subtree
}

typedef struct queue
{
    node_t* q[CAPACITY];
    int front, rear;
} q_t;

void enqueue(q_t* q, node_t* c)
{
    if (++q->rear > CAPACITY) q->rear = 1;
    q->q[q->rear-1] = c;
}

node_t* dequeue(q_t* q)
{
    if (q->front==q->rear) return NULL;
    if (++q->front >= CAPACITY) q->front = 0;
    return q->q[q->front-1];
}

static inline int len(const q_t q)
{
    return (q.rear-q.front) % CAPACITY;
}

void bfs(node_t* root)
{
    q_t q;
    q.front = 0;
    q.rear = 0;
    enqueue(&q, root);
    node_t* dummy;
    while (len(q))
    {
        dummy = dequeue(&q);
        printf("%d ", dummy->value);
        if (dummy->left)
            enqueue(&q, dummy->left);
        if (dummy->right)
            enqueue(&q, dummy->right);
    }
}

int main(int argc, char ** argv)
{
    node_t *A = (node_t*)malloc(sizeof(node_t));
    assert(A); //checks whether memory is allocated successfully
    
    A->value = 4;
    A->left = NULL;
    A->right = NULL;

    insert(A, 2);
    insert(A, 5);
    insert(A, 10);
    insert(A, 3);
    insert(A, 15);

    printf("height of A before deletion: %d\n", get_height(A));

    delete(A, 5);
    printf("height of A after deletion: %d\n", get_height(A));

    bfs(A);
}