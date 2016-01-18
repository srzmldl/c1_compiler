from __future__ import division

def public_sequence(matrix,index_x,index_y,min_length,threshhold,skip):
    limit_x = len(matrix)
    limit_y = len(matrix[0])
    collection =[]

    for k in range(limit_x):
        skip_count = skip
        seq = []
        i = k
        j = 0
        while(i<limit_x and j<limit_y):
            #print "(%d\t,%d\t,%.3f)"%(i,j,(1/(1+matrix[i][j])))
            if (1/(1+matrix[i][j]))>=threshhold:
                skip_count = skip
                seq.append([i,j])
            else:
                if skip_count:
                    if seq:
                        skip_count -= 1
                else:
                    skip_count = skip
                    if len(seq)>= min_length:
                        collection.append(seq)
                    seq = []
            i += 1
            j += 1
        if len(seq)>min_length:
            collection.append(seq)

    for k in range(1,limit_y):
        skip_count = skip
        seq = []
        i = 0
        j = k
        while(i<limit_x and j<limit_y):
            if (1/(1+matrix[i][j]))>=threshhold:
                skip_count = skip
                seq.append([i,j])
            else:
                if skip_count:
                    if seq:
                        skip_count -= 1
                else:
                    skip_count = skip
                    if len(seq)>= min_length:
                        collection.append(seq)
                    seq = []
            i += 1
            j += 1


    simi_mat = similar_matrix(limit_x,limit_y,collection)


    print_public_seq(collection,index_x,index_y)
    return simi_mat

def print_public_seq(collection,index_x,index_y):
    if collection:
        length = []
        for seq in collection:
            length.append(len(seq))

        print "The longest public sequence length: "+str(max(length))
        seq = collection[length.index(max(length))]
        for pair in seq:
            print index_x[pair[0]]+'\t'+index_y[pair[1]]
        print '\n'
    else:
        print "There is no similay sequence between two functions."

def similar_matrix(limit_x,limit_y,collection):
    matrix = []
    for i in range(limit_x):
        line=[]
        for j in range(limit_y):
            line.append(0)
        matrix.append(line)

    for seq in collection:
        for (i,j) in seq:
            matrix[i][j] = 1

    #for line in matrix:
    #    print line
    return matrix
