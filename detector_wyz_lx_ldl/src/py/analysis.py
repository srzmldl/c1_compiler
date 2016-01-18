import numpy as np
import pandas as pd
import os

def build_matrix_df(matrix,index,column):
    df = pd.DataFrame(matrix,index = index,columns=column)
    print df
    save(df)


def save(df):
    filename = 'csvfile.csv'
    dir = os.getcwd()+'/csv/'+filename
    df.to_csv(dir,columns=df.columns)



if __name__ =="__main__":
    pass
