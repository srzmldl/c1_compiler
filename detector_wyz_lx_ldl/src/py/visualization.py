import numpy as np
import matplotlib.pyplot as plt

save_path = "./output/"

def draw_matrix(value, limit_x,limit_y, max, simi_mat):
    for i in range(limit_x):
        for j in range(limit_y):
            plt.scatter(i,j,s = np.pi * (5 * 1/(1+value[i][j]))**2,c =('b' if simi_mat[i][j]==0 else 'k'),marker='+'  ,alpha = 1)
            #plt.scatter(i,j,s = np.pi * (5 * value[i][j])**2,c =1 ,alpha = 0.3)

    plt.show()

def dump_matrix(value, limit_x,limit_y, max, simi_mat,members1,members2):
    for i in range(limit_x):
        for j in range(limit_y):
            plt.scatter(i,j,s = np.pi * (5 * 1/(1+value[i][j]))**2,c =('w' if simi_mat[i][j]==0 else 'k'),marker='+'  ,alpha = 1)
            #plt.scatter(i,j,s = np.pi * (5 * value[i][j])**2,c =1 ,alpha = 0.3)

    plt.xlabel(members1)
    plt.ylabel(members2)


    plt.savefig(save_path+members1+" "+members2+".png",dpi =200 )

if __name__ =='__main__':


    N = 50
    x = np.random.rand(N)
    y = np.random.rand(N)
    colors = np.random.rand(N)
    area = np.pi * (15 * np.random.rand(N))**2  # 0 to 15 point radiuses
    print colors
    plt.scatter(x, y, s=area, c=colors, alpha=0.5)
    plt.show()