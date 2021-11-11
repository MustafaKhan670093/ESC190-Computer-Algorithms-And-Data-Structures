
user_input = '''4
3 5
3 3
1 2
3 100'''

candy_info = list(map(int, user_input.split()))

total_num_candy = 0
quantity_of_individual_candy = []
calories_of_individual_candy = []

for i in range(len(user_input)):
    total_num_candy = user_input[0]
    if i%2 != 0:
        quantity_of_individual_candy.append(user_input[i])
    elif i%2 == 0 and i>0:
        calories_of_individual_candy.append(user_input[i])


print(' ')
print(candy_info)


def cost(caloriesOfPersonOne, caloriesOfPersonTwo):
    return caloriesOfPersonTwo - caloriesOfPersonOne

def min_calories(candy_info, i):


    i = 0
    while i < 4:


