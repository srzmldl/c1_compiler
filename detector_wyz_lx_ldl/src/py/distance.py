from __future__ import division
import cmath


def Euclidean(list1,list2):
    dist = 0
    for i in range(len(list1)):
        dist += (list1[i]-list2[i])**2
    return cmath.sqrt(dist).real

def Jaccard_like(list1,list2):
    molecular = 0
    denominator = 0
    for i in range(len(list1)):
        if list1[i] < list2[i]:
            molecular += list1[i]
            denominator += list2[i]
        else:
            molecular += list2[i]
            denominator += list1[i]

    if molecular==0 or denominator ==0:
        return 0
    else:
        e = molecular/denominator
        return e.real

def Consin(list1,list2):
    molecular = 0
    factor1 = 0
    factor2 = 0
    for i in range(len(list1)):
        molecular += list1[i]*list2[i]
        factor1 += list1[i]**2
        factor2 += list2[i]**2



    if molecular==0 or (factor1==0 and factor2==0):
        return 0
    else:
        denominator = cmath.sqrt(factor1)*cmath.sqrt(factor2)
        e = molecular/denominator
        return e.real

