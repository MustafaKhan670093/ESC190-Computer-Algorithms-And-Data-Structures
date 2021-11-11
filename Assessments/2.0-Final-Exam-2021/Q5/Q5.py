'''
The steps for Heapsort are:
1. Call heapify(), this builds a heap from a list in O(n) operations.
2. Swap the first element of the list with the final element. Decrease the considered range of the list by one.
3. Percolate the elements. I.e. put the new first element in its appropriate index in the heap.
Go to step (2) unless the range under consideration of the list is one element.
The heapify() operation is run once, and is O(n) in performance. The percolate() function is O(log n), and is called n times. 
Therefore, the performance of this algorithm is O(n + n log n) = O(n log n).
This means heapsort is not O(n). It is in fact worse than O(n).
'''