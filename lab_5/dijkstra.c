// I'm gonna try to write everything in one file. This is bad practice so please DON'T try this at home

/* Objective: To create an algorithm that can find the shortest path between any two points of a graph in
 * O(|E|+|V|log|V|) time.
 * 
 * Approach: Using a min-heap based priority queue approach to Dijkstra's algorithm and using an adjacency list for the graph
 * 
 * Formatting: The first part of this document will introduce all the necessary macros, types, structures, and functions that is used in the implementation,
 *             similar to what one would see in a (.hpp) header file.
 *			   The second part of this document consists of a main function that takes command line arguments used as a preliminary test
 *             for the various aspects of the requirements.
 *			   The third part of this document consists of the specific implementation of every function introduced in the first part.
 *			   If one wants to see the methodology behind some of the operations or improve or readapt this program, this would be the part of interest.
 *			   This document will end with a conclusion, in particular, of one blank line or (char)10.
 * 
 * Date: 2021.02.27
 * Course: CSC190
 * Student ID: ************
 * Instructor: Michael Guerzhoy
 * 
 * Author's notes: Gumboots deserves a C/C++ plushie. 
 * C++ ~ C# > C > Java > Python > HTML
 * In comparison, this implementation can be written, without loss of generality, in ~100-150 lines in C++. 
 * 
 * Dedication: Patricia Sheridan (patricia.sheridan@utoronto.ca), Robert Irish (r.irish@utoronto.ca), Philip Asare (philip.asare@utoronto.ca)
 * 
 */


///////////////////////////////////////////////////////////////////////////////////////////
// I will used fixed width types
#include <stdint.h>
typedef uint32_t weight_t; // this will be used to store the weights of the graph to ensure there are no negative weights

#define INF UINT32_MAX // this will be used as infinity in the algorithm. all weights MUST be less than this

typedef int32_t iid_t; // these are the identifiers. just using this type as a placeholder but it doesn't really matter

#include <stdlib.h> // malloc, calloc, realloc, NULL, srand, rand
#include <assert.h> // assertions to check for bad behavior
#include <string.h> // memcpy, memset
#include <stdio.h> // Used for testing 

///////////////////////////////////////////////////////////////////////////////////////////
// For representation of the graph

// The edges that are stored in the adjacency list
typedef struct edge
{
	weight_t weight; // the weight of this edge
	iid_t id; // the id of the outgoing node
} edge_t;

#define EMPTY_EDGE (edge_t){INF,-1}

// For each node of the graph, there must be a linked list of edges.

// The linked list of edges
struct elem
{
	edge_t edge;
	struct elem* next;
};

typedef struct node
{
	struct elem* first;
	struct elem* last;
} node_t;

/* Constructor(s) and destructor(s) */
node_t* create_node(void); // need to create the linked list of edges connected to the node
void destroy_node(node_t*); // destroy it

/* Methods */
void push_back(node_t*, const edge_t); // push an element to the back

///////////////////////////////////////////////////////////////////////////////////////////
// currently all the adjacency list is just an array of edges

typedef struct adj_list
{
	node_t* nodes;
	size_t size; // size denotes the number of nodes of the graph
} adj_list_t;

/* Constructor(s) and destructor(s) */
adj_list_t* create_adj_list(size_t); // create an adjacency list of a specified number of nodes
void destroy_adj_list(adj_list_t*); // destroy the adjacency list

/* Methods */
void add_edge(adj_list_t*, iid_t, iid_t, weight_t); // add an edge between two nodes with respective weight and ids
void add_biedge(adj_list_t*, iid_t, iid_t, weight_t); // add an bidirectional edge

///////////////////////////////////////////////////////////////////////////////////////////
// For the priority queue
typedef struct pq_item
{
	weight_t priority;
	iid_t id;
} pq_item_t;

typedef struct priority_queue
{
	pq_item_t* container;
	size_t size; // the number of elements stored
	size_t max_size; // the max number of elements (note that the size of the container is actually 1 more than this)
} pq_t;

#define PQ_DEF_SIZE 20

/* Constructor(s) and destructor(s) */
pq_t* create_pq(void); // create an empty priority queue with default size and nothing in it
void destroy_pq(pq_t*); // delete the priority queue

/* Methods */

void push_with_priority(pq_t*, const iid_t, const weight_t); // push an item with priority 
pq_item_t pop(pq_t*); // pop the most important item

///////////////////////////////////////////////////////////////////////////////////////////
// Graph algorithms

struct Answer
{
	weight_t* dist;
	iid_t* prev;
};

typedef struct path_element
{
	iid_t id;
	struct path_element* prev;
} path_elem_t;

typedef struct path
{
	path_elem_t* tail; // pointer to the last element (destination)
	weight_t length; // length of this path
	size_t steps; // number of nodes it passes through
} path_t;

void print_path(const path_t);
void delete_path(path_t*);

struct Answer dijkstra(adj_list_t, const iid_t); // perform dijkstra algorithm from a start node

path_t shortest_path(adj_list_t, const iid_t, const iid_t); // using dijkstras algorithm, find the shortest path from a start to a end node.

///////////////////////////////////////////////////////////////////////////////////////////
// Main. Testing.

int main(int argc, char* argv[])
{
	// First start with a simple graph

	adj_list_t simp = *create_adj_list(10);
	add_biedge(&simp, 0, 1, 10);
	add_biedge(&simp, 0, 3, 15);
	add_biedge(&simp, 2, 3, 50);
	add_biedge(&simp, 0, 2, 5);
	add_edge(&simp, 3, 4, 10);
	add_edge(&simp, 4, 3, 20);
	add_biedge(&simp, 1, 5, 45);

	// you can find a the shortest path between two nodes like this

	path_t path = shortest_path(simp, 2, 3);
	print_path(path);
	delete_path(&path);

	// you can find the shortest path to all nodes. 
	// for nodes that aren't connected, the maximum integer, or infinity, will be displayed

	struct Answer simp_ans = dijkstra(simp, 1);

	printf("Distance from node 1 to node:\n");
	for (int i = 0; i < 10; ++i)
		printf("%d:%u ", i, simp_ans.dist[i]);
	printf("\n");
	
	free(simp_ans.dist);
	free(simp_ans.prev);

	destroy_adj_list(&simp);

	
	// let's create a bigger graph with 100 nodes and 1000 edges

	adj_list_t graph = *create_adj_list(100);

	srand(69);
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			if (i != j && rand() < RAND_MAX / 10)
				add_edge(&graph, i, j, 50 + rand() / (RAND_MAX / 2000)); // making the weight being random between 50 to ~2000
		}
	}
	
	// I will print out the graph for anyone to validate the shortest paths
	for (int i = 0; i < 100; ++i)
	{
		printf("\nNode %d\n", i);
		struct elem* n = (graph.nodes+i)->first;
		while (n)
		{
			printf("%d,%d;", n->edge.id, n->edge.weight);
			n = n->next;
		}
	}
	printf("\n\n");
	
	struct Answer ans = dijkstra(graph, 3);

	printf("Distance from node 3 to node:\n");
	for (int i = 0; i < 100; ++i)
		printf("%d:%d ", i, ans.dist[i]);
	printf("\n\n");

	// find a few shortest paths through this graph
	path_t path1 = shortest_path(graph, 10, 55), path2 = shortest_path(graph, 32, 88), path3 = shortest_path(graph, 7, 11), path4 = shortest_path(graph, 42, 43);

	print_path(path1); print_path(path2); print_path(path3); print_path(path4);
	delete_path(&path1); delete_path(&path2); delete_path(&path3); delete_path(&path4);

	destroy_adj_list(&graph);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
// implementation


/* Objective: create a empty linked list for a node.
 * Approach: Allocate sufficient amount of memory to store the struct. Then set the first and last elements to NULL pointer.
 * Exceptions: Assertion failure if memory allocation fails.
 * Runtime: O(1)
 */
node_t* create_node()
{
	node_t* node = (node_t*)malloc(sizeof(node_t));
	assert(node);

	node->first = NULL;
	node->last = NULL;

	return node;
}

/* Objective: Free all memory used by the node.
 * Approach: start from the head until hitting a null terminator, freeing each element along the way.
 * Runtime: O(n)
 */
void destroy_node(node_t* node)
{
	struct elem* head = node->first, *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

/* Objective: Push an element to the back of the linked list (representing the node).
 * Approach: Taking advantage of the "last" member, link the new element to it and update "last".
 * Exceptions: Assertion failure if memory allocaton fails.
 * Runtime: O(1)
 */
void push_back(node_t* node, const edge_t edge)
{
	struct elem* tail = node->last;
	struct elem* new_elem = (struct elem*)malloc(sizeof(struct elem)); // this is the new element that will be stored
	
	assert(new_elem); // check for success
	
	// create the new element as the last element
	new_elem->edge = edge; 
	new_elem->next = NULL;

	if (tail) // if the linked list has at least 1 element, add point the last element to the new one.
		tail->next = new_elem;
	else // if the linked list has no elements, this would be the first element also
		node->first = new_elem;
	
	node->last = new_elem;
}

/* Objective: Create a new adjacency list to store a graph with a given number of nodes.
 * Approach: First allocate the memory for the adjancency list structures, then an array of all the nodes
 *			 Initialize the nodes by setting the memory for that entire block to zero.
 * Exceptions: Assertion failure if memory allocation fail.
 * Runtime: O(n)
 */
adj_list_t* create_adj_list(size_t num_nodes)
{
	adj_list_t* adj_list = (adj_list_t*)malloc(sizeof(adj_list_t));
	assert(adj_list);

	adj_list->size = num_nodes;
	adj_list->nodes = (node_t*)calloc(num_nodes, sizeof(node_t));

	assert(adj_list->nodes);

	// setting the memory to zero makes all the pointers null, as required.
	memset(adj_list->nodes, 0, num_nodes * sizeof(node_t));
	return adj_list;
}

/* Objective: Destroy the adjacency list and deallocate its memory.
 * Approach: Using the function to free each node of the adjacency list, free it seperately. Then free the array that stores the pointers.
 * Runtime: O(|V|+|E|)
 */
void destroy_adj_list(adj_list_t* adj_list)
{
	for (size_t i = 0; i < adj_list->size; ++i)
		destroy_node(adj_list->nodes+i);
	free(adj_list->nodes);
}

/* Objective: Add a unidirectional edge with a weight to the graph from a source to destination.
 * Approach: Use the push_back function for the linked list .
 * Runtime: O(1)
 */
void add_edge(adj_list_t* graph, iid_t src, iid_t dest, weight_t weight)
{
	push_back(graph->nodes + src, (edge_t) { weight, dest });
}

/* Objective: Add a bidirectional edge with a weight to the graph between nodes a and b
 * Approach: Naive
 * Runtime: O(1)
 */
void add_biedge(adj_list_t* graph, iid_t a, iid_t b, weight_t weight)
{
	add_edge(graph, a, b, weight);
	add_edge(graph, b, a, weight);
}

/* Objective: Create a new min priority queue with the default parameters.
 * Approach: Allocate the memory for the container and initialize the other values to their default values.
 * Exceptions: Assertion failure if memory allocation fail.
 * Runtime: O(1)
 */
pq_t* create_pq()
{
	pq_t* pq = (pq_t*)malloc(sizeof(pq_t));
	assert(pq);

	pq->max_size = PQ_DEF_SIZE;
	pq->size = 0;
	pq->container = (pq_item_t*)calloc(pq->max_size + 1, sizeof(pq_item_t));
	assert(pq->container);

	return pq;
}

void destroy_pq(pq_t* pq)
{
	free(pq->container);
}

/* Objective: Add an element with a given priority queue without disrupting the heap order. Also allocate new memory if needed.
 * Approach: First check if new memory is needed. Then, add the item to end of the heap and percolate up.
 * Exceptions: Assertion failure if memory allocation fails.
 * Runtime: O(log n)
 */
void push_with_priority(pq_t* pq, const iid_t id, const weight_t priority)
{
	// reallocate memory if there is not enough memory
	if (++pq->size > pq->max_size)
	{
		pq->max_size <<= 1;
		pq_item_t* tmp = (pq_item_t*)realloc(pq->container, sizeof(pq_item_t) * (pq->max_size + 1));
		assert(tmp);
		pq->container = tmp;
	}

	// add to the last element of the container and percolate up
	size_t I = pq->size;
	while (I > 1 && (pq->container + (I >> 1))->priority > priority)
	{
		(pq->container)[I] = (pq->container)[I >> 1];
		I >>= 1;
	}
	(pq->container)[I] = (pq_item_t){ priority, id };
}

/* Objective: Return the most important element and remove it from the priority queue without disrupting the heap order.
 * Approach: Remove the first element and replace it with the final element. Then percolate down to restore heap order. 
 * Exceptions: Assertion failure if the container is empty.
 * Runtime: O(log n)
 */
pq_item_t pop(pq_t* pq)
{
	assert(pq->size); // make sure there is something

	pq_item_t popped_item, tmp;
	
	// memcpy may be needed. 
	popped_item = (pq->container)[1];
	
	// set the top as the last node, decrement the size
	pq->container[1] = pq->container[pq->size--];

	// percolate down
	size_t I = 1;
	while (I << 1 <= pq->size)
	{
		if ((I << 1) + 1 > pq->size || (pq->container + (I << 1))->priority < (pq->container + ((I << 1) + 1))->priority)
		{
			if ((pq->container + I)->priority > (pq->container + (I << 1))->priority)
			{
				// swap with left child
				tmp = (pq->container)[I];
				(pq->container)[I] = (pq->container)[I << 1];
				(pq->container)[I << 1] = tmp;

				I <<= 1;
			}
			else
				return popped_item;
		}
		else
		{
			if ((pq->container + I)->priority > (pq->container + ((I << 1) + 1))->priority)
			{
				// swap with right child
				tmp = (pq->container)[I];
				(pq->container)[I] = (pq->container)[(I << 1) + 1];
				(pq->container)[(I << 1) + 1] = tmp;

				I = (I << 1) + 1;
			}
			else
				return popped_item;
		}
	}
	return popped_item;
}

// for debugging purposes
void print_heap(const pq_t pq)
{
	for (unsigned int i = 1; i <= pq.size; ++i)
	{
		printf("%u ", (pq.container + i)->priority);
		if ((i & (i + 1)) == 0)
			printf("\n");
	}
	printf("\n\n");
}

/* Objective: Find the shortest distance between a source node to all possible nodes, as well as information on the respective paths.
 * Approach: Dijkstra's algorithm using priority queue.
 * Exceptions: Assertion failure if memory allocation fails.
 * Runtime: O(|V|+|E|log(|E|))
 * Memory: O(|V|+|E|)
 * Notes: The members of the returned struct Answer (prev, dist) MUST be freed.
 */
struct Answer dijkstra(adj_list_t graph, const iid_t src)
{
	// initialize the distance and previous arrays

	weight_t* dist;
	iid_t* prev;

	dist = (weight_t*)calloc(graph.size, sizeof(weight_t));
	prev = (iid_t*)calloc(graph.size, sizeof(iid_t));

	assert(dist && prev);

	for (int i = 0; i < graph.size; ++i)
	{
		dist[i] = INF;
		prev[i] = -1;
	}

	pq_t Q = *create_pq();

	dist[src] = 0;
	push_with_priority(&Q, src, 0);

	while (Q.size)
	{
		pq_item_t u = pop(&Q);
		struct elem* e = ((graph.nodes)[u.id]).first;
		while (e)
		{
			iid_t e_id = (e->edge).id;
			weight_t e_weight = (e->edge).weight;

			weight_t dist2e = dist[u.id] + e_weight; // distance to e using this path
			if (dist2e < dist[e_id])
			{
				dist[e_id] = dist2e;
				prev[e_id] = u.id;
				push_with_priority(&Q, e_id, dist2e);
			}

			e = e->next;
		}
	}

	destroy_pq(&Q);

	return (struct Answer) { dist, prev };
}

/* Objective: Find the shortest path between a source and destination node in a graph.
 * Approach: Dijkstra's algorithm using priority queue.
 * Exceptions: Assertion failure if memory allocation fails.
 * Runtime: O(|V|+|E|log(|E|))
 * Memory: O(|V|+|E|)
 * Notes: The returned value path_t MUST be freed.
 */
path_t shortest_path(adj_list_t graph, const iid_t src, const iid_t dest)
{
	struct Answer ans = dijkstra(graph, src);
	path_elem_t* tail, * tmp;

	weight_t length = ans.dist[dest];
	free(ans.dist);

	size_t steps = 0;
	
	tail = (path_elem_t*)malloc(sizeof(path_elem_t));
	assert(tail);

	tail->id = dest;
	tail->prev = NULL;

	tmp = tail;

	while (ans.prev[tmp->id] >= 0)
	{
		tmp->prev = (path_elem_t*)malloc(sizeof(path_elem_t));
		assert(tmp->prev);
		tmp->prev->id = ans.prev[tmp->id];
		tmp = tmp->prev;
		steps++;
	}
	tmp->prev = NULL;

	free(ans.prev);
	
	return (path_t){tail, length, steps};
}

/* Objective: Print a path to the console
 * Approach: Go through the linked list, print each element from back to front and terminate with a new line
 * Runtime: O(n)
 */
void print_path(const path_t path)
{
	printf("Path Length: %u, Steps: %u\n", path.length, path.steps);
	path_elem_t* cur = path.tail;
	while (cur)
	{
		printf("%u <- ", cur->id);
		cur = cur->prev;
	}
	printf("\n");
}

/* Objective: Delete a path by freeing the memory it uses
 * Approach: Go through the linked list, frees each element
 * Runtime: O(n)
 */
void delete_path(path_t* path)
{
	path_elem_t* cur = path->tail, * tmp;
	while (cur)
	{
		tmp = cur;
		cur = cur->prev;
		free(tmp);
	}
}