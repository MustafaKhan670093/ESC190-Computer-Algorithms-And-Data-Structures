def find(L, e):
    min = 0
    max = len(L) - 1
    mid = 0

    while min <= max:
        mid = (min + max) // 2

        # if e is greater than mid, ignore left half of mid in list
        if L[mid] < e:
            min = mid + 1
        # if e is smaller than mid, ignore right half of mid in list
        elif L[mid] > e:
            max = mid - 1
        #when L[mid] == e
        elif mid==0 or L[mid-1]!=L[mid] :
            return mid;
        else: ## [1,1]
            max = mid - 1;
    #exiting while loop means e not present in L
    return -1

def find_right(L, e):
    min = 0
    max = len(L) - 1
    mid = 0

    while min <= max:
        mid = (min + max) // 2

        # if e is greater than mid, ignore left half of mid in list
        if L[mid] < e:
            min = mid + 1
        # if e is smaller than mid, ignore right half of mid in list
        elif L[mid] > e:
            max = mid - 1
        #when L[mid] == e
        elif mid == len(L) - 1 or L[mid]!=L[mid+1]:
            return mid
        else:
            min = mid + 1
    #exiting while loop means e not present in L
    return -1

###Testing Code###
A = [1, 2, 2, 2, 3, 4, 5]
print("Finding the first occurance of 2 at index:", find(A, 2))
print("Finding the last occurance of 2 at index:", find_right(A, 2))
print(' ')
B = [1, 1, 1, 2, 2, 3, 4, 5]
print("Finding the first occurance of 1 at index:", find(B, 1))
print("Finding the last occurance of 1 at index:", find_right(B, 1))