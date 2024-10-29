# # Question 1
# list_1 = [-1, 2, 3, 9, 0]
# list_2 = [1, 2, 7, 10, 14]
# print(list_1 + list_2)
# #The python '+' operator does not do list addition it simply stiches the second list
# # arguement on the end of the first to create a combined list.
#
# # Question 2
# empty_list = []
# for i in range(0, len(list_1)):
#     empty_list.append(list_1[i] + list_2[i])
# print(empty_list)

# # Question 3
# import numpy as np
# my_1d_array = np.array([1, 2, 3, 4, 5])
# print(my_1d_array.shape)
# my_2d_array = np.array([[1, 2, 3], [4, 5, 6]])
# print(my_2d_array.shape)
# my_3d_array = np.array([[[1, 2], [3, 4]], [[5, 6], [7, 8]]])
# print(my_3d_array.shape)
#
# my_4d_array = np.array([
#     [
#         [[1], [2]], [[3], [4]], [[5], [6]]
#     ],
#     [
#         [[1], [2]], [[3], [4]], [[5], [6]]
#     ]
# ])
# print(my_4d_array.shape)

# # Question 4
# import numpy as np
# my_3d_array = np.arange(27).reshape(3, 3, 3)
# #print(my_3d_array)
# print(my_3d_array[:, :, 0])
# print(my_3d_array[1, 1, :])
# print(my_3d_array[:, 0::2, 0::2])

# # Question 5
# import numpy as np
# my_3d_array = np.arange(27).reshape(3, 3, 3)
# print(my_3d_array[[0,1,2], [1,2,0], [1,2,0]])
# print(my_3d_array[1, [0,2], [0,2]])

# Question 6
import numpy as np
my_2d_array = np.arange(-10,20).reshape(5, 6)
#print(my_2d_array)
sum_of_columns = my_2d_array.sum(axis=0)
print(sum_of_columns)
indexing_array = sum_of_columns % 10
print(indexing_array)
print(my_2d_array[:, indexing_array==0])