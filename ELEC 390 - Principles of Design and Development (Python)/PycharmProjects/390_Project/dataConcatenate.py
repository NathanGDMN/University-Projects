import pandas as pd

#-----Read Data-----
NathanWalking = pd.read_csv('Walking.csv')
NathanJumping = pd.read_csv('Nathan-Jumping.csv')

#-----Concatenate Data into one file-----
all_data = pd.concat([NathanWalking, NathanJumping])
# create csv file from concatenated data
all_data.to_csv('all_data.csv', index=False)
