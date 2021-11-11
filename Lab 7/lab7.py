import numpy as np

# 2. Write Python code to find the cost of the minimum-energy seam in a list of lists.

# energies = [[24,      22,      30,      15,      18,      19],
#             [12,      23,      15,      23,      10,     15],
#             [11,      13,      22,      13,      21,      14],
#             [13,      15,      17,      28,      19,      21],
#             [17,      17,      7,       27,      20,      19]]
     
#     The correct output for the given energies data is 15+10+13+17+7 = 62.

energies = [[24,      22,      30,      15,      18,      19],
            [12,      23,      15,      23,      10,     15],
            [11,      13,      22,      13,      21,      14],
            [13,      15,      17,      28,      19,      21],
            [17,      17,      7,       27,      20,      19]]


def dynamic_seam(energy):
    n_row = len(energy)
    n_col = len(energy[0])
    
    row_energy=[]
    row_energy.append(energy[0])

    for i in range(1, n_row):
        temp = []
        for j in range(n_col):
            #print('i,j', i,j)
            if j == 0:
                temp.append(energy[i][j] + min(row_energy[i-1][j], row_energy[i-1][j+1]))
            elif j == n_col - 1:
                temp.append(energy[i][j] + min(row_energy[i-1][j], row_energy[i-1][j-1]))
            else:
                temp.append(energy[i][j] + min(row_energy[i-1][j-1], row_energy[i-1][j], row_energy[i-1][j+1]))
        row_energy.append(temp)
        
        print('Current status of row_energy:')
        print(np.matrix(row_energy))
        print('\n')

    print('All row energies have been calculated:')
    print(np.matrix(row_energy))
    print('\n')

    #Minimum energy of last row corresponds to the minimum vertical seam
    min_energy = min(row_energy[n_row-1])

    return min_energy

print("Minimum energy is: ", dynamic_seam(energies))

