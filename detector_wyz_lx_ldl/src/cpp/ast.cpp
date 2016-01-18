#include <bits/stdc++.h>
#define HASH_TOT 5
#define MAX_TREE_SIZE  1123456
//#define DEBUG
//#define COMPARE_MOSS_JPLAG
#define MAXFILE 100

using namespace std;

//multply hashes to decrease error possiblity
const long long hashBase[HASH_TOT] = {
    (int) 1e9 + 7,
    3214567,
    55566677,
    23456789,
    150054881
};

//hash power base
long long powBase[HASH_TOT][MAX_TREE_SIZE];
#ifdef DEBUG
string mpBack[MAX_TREE_SIZE];
#endif

//ast node
struct Node {
    int label, level, nodeTot, id;
    string originStr; // for debug
    long long hash[HASH_TOT];
    vector <Node*> son;
};


map < string, int > mpLabel;
map < pair <Node*, Node*> , int> similarity;
int mpId = 0, fileId = 0;
// map file and label for output

struct myclass {
    int k = 0;
    bool operator() (Node *u, Node *v) {
        return (u->hash[k] > v->hash[k]);
    }
} comObject;

const int delLowLevel = 3;

struct Tree {
public:
    Tree() {
    }

    //extract ast from clang++
    Tree(char* fileName) {
        buildFromFile(fileName);
        name = fileName;
    }

    string name = "";
    Node *root;
    vector <Node*> nodeList;
    //ignore the low level

    // debug, print new ast
    void dfsCheckTree(Node *x, int offset) {
        //for (int i = 0; i < offset; ++i) {
        //  cout << ' ';
        //}
        //cout << mpLabel["CStyleCastExpr"] << endl;
        comObject.k = 0;
        sort((x->son).begin(), (x->son).end(), comObject);
        printf("%s: %lld\n", x->originStr.c_str(), x->hash[0]);
        for (auto it = (x->son).begin(); it != (x->son).end(); it++) {
            dfsCheckTree(*it, offset + 2);
        }
    }

    // dfs update node.nodeTot, total nodes of the subtree
    void dfsGetLevelNodeTot(Node *x) {
        x->level = 1;
        x->nodeTot = 0;
        for (auto it = (x->son).begin(); it != (x->son).end(); ++it) {
            dfsGetLevelNodeTot(*it);
            x->level = max(x->level, (*it)->level + 1);
            if ((*it)->level > delLowLevel) {
                x->nodeTot += (*it)->nodeTot;
            }
        }
        if (x->level > delLowLevel) x->nodeTot++;
    }

    //calculate hash of each node
    void getHash(Node *x) {
        for (auto it = (x->son).begin(); it != (x->son).end(); ++it) {
            getHash(*it);
        }

        for (int i = 0; i < HASH_TOT; ++i) {
            if (x->level <= delLowLevel) {
                x->hash[i] = 0;
                continue;
            } else {
                comObject.k = i;
                sort((x->son).begin(), (x->son).end(), comObject);
                x->hash[i] = x->label;
                for (auto it = (x->son).begin(); it != (x->son).end(); ++it) {
                    if ((*it)->level > delLowLevel) {
                        x->hash[i] = x->hash[i] * powBase[i][(*it)->nodeTot * 2] + (*it)->hash[i];
                    }
                }
                x->hash[i] = x->hash[i] * powBase[i][1] + x->label;
            }
        }
    }

    //dump ast from clang and change into link-list ast
    void buildFromFile(char* fileName) {
        string st;
        ++fileId;
        char la[100], tmpChar[100];
        sprintf(la, "out.txt");
        sprintf(tmpChar, "clang -Xclang -ast-dump -fsyntax-only %s 2>lala.txt 1>%s", fileName, la);
        system(tmpChar);
        vector < pair< Node*, int> > vec;
        vec.clear();
        ifstream fin(la);
        for (; getline(fin, st); ) {
            Node* x = new Node();
            string stNow = "";
            for (auto it = st.begin(); it != st.end(); it++) {
                if ((*it) == '[') {
                    while ((*it) != 'm') it++;
                } else {
                    //stNow += *(it);
                    if ((*it) == '0') break;
                    if (it == st.end() || (it != st.end() && *(it + 1) != '[')) stNow += *(it);
                }
            }
            
            x->originStr = stNow;
            int pos = stNow.find_first_of('-') + 1;
            int lastPos = stNow.length() - 1;
            //cout << pos << ' ' << lastPos << stNow << endl;
            if (stNow[lastPos] == ' ') lastPos--;
            //cout << stNow << endl;
            stNow = stNow.substr(pos, lastPos - pos + 1);
            if (vec.empty()) {
                root = x;
            } else {
                for (; vec.back().second >= pos; vec.pop_back());
                ((vec.back().first)->son).push_back(x);
            }
            //   printf("%d\n", this->root);
            vec.push_back({x, pos});
            
            
            //cout << mpLabel["CStyleCastExpr"] << endl;
            if (stNow == "CStyleCastExpr") {
                //cout << mpLabel[stNow] << endl;
                int x = x + 1;
                x++;
            }
            if (mpLabel.count(stNow) > 0) {
                x->label = mpLabel[stNow];
            } else {
                x->label = ++mpId;
                mpLabel[stNow] = mpId;
                //cout << mpId << ':' << stNow << endl;
#ifdef DEBUG
                mpBack[mpId] = stNow;
#endif
            }
            nodeList.push_back(x);
            //cout << stNow << endl;
        }

        dfsGetLevelNodeTot(root);
        getHash(root);
#ifdef DEBUG
        dfsCheckTree(root, 0);
#endif
    }

} *tree[MAXFILE];

//two subtrees are the same only if all the hashes equal
bool sameHash(Node *u, Node *v) {
    for (int i = 0; i < HASH_TOT; ++i) {
        if (u->hash[i] != v->hash[i]) return false;
    }
    return true;
}
//get similarity of node u and node v
//dp
//every <father, son> pair matches with each other, So O(n^2)
double getSimilarity(Node *u, Node *v) {
    auto itB = (v->son).begin();
    if (sameHash(u, v)) return 1;
    //return 0;
    if (u->level <= delLowLevel || v->level <= delLowLevel) return 0;
    if (similarity.count({u, v}) > 0) return similarity[{u, v}];
    vector <Node*> vecA;
    vector <Node*> vecB;
    comObject.k = 0;
    sort((u->son).begin(), (u->son).end(), comObject);
    sort((v->son).begin(), (v->son).end(), comObject);
    int sameNode = 0;
    for (auto itA = (u->son).begin(); itA != (u->son).end(); itA++){
        for (; (itB != (v->son).end()) && ((*itA)->hash[0] < (*itB)->hash[0]); itB++) {
            vecB.push_back(*itB);
        }
        if ((itB == (v->son).end()) || !sameHash((*itA), (*itB))) {
            vecA.push_back(*itA);
        } else {
            sameNode += (*itA)->nodeTot;
            itB++;
        }
    }
    
    double tmp = 1.0 * sameNode * 2 / (u->nodeTot + sameNode);
    for (auto itA = vecA.begin(); itA != vecA.end(); ++itA) {
        double maxSim = 0;
        int maxIt = -1;
        for (int i = 0; i < (int) vecB.size(); ++ i) {
            double ttt = getSimilarity(*itA, vecB[i]);
            if (ttt > maxSim) {
                maxSim = ttt;
                maxIt = i;
            }
        }
        if (maxIt >= 0) {
            for (int i = maxIt; i < (int) vecB.size() - 1; ++i) {
                vecB[i] = vecB[i + 1];
            }
            vecB.pop_back();
        }
        tmp += 1.0 * ((*itA)->nodeTot) * maxSim / (u->nodeTot + sameNode);
    }
    similarity[{u, v}] = tmp;
    return tmp;
}

double compare(const Tree *A, const Tree *B) {
    //similarity.clear();
    double tmp = getSimilarity(A->root, B->root);
    return tmp;
//=====following very bad, discard now.
    double ans = 0;
    double sum = 0;
    map < Node*, bool > mpVis;
    for (auto itA = A->nodeList.begin(); itA != A->nodeList.end(); itA++) {
        if ((*itA)->level > delLowLevel) {
            double maxSim = 0;

            Node *pos;
            for (auto itB = B->nodeList.begin(); itB != B->nodeList.end(); itB++) {
                if ((*itB)->level > delLowLevel && mpVis.count(*itB) == 0) {
                    double tmp = getSimilarity(*itA, *itB);
                    if (maxSim < tmp) {
                        maxSim = tmp;
                        pos = *itB;
                        //maxSim = max(maxSim, getSimilarity(*itA, *itB));
                    }
                }
                if (pos) mpVis[pos] = true;
            }
            double tmp = (*itA)->level * (*itA)->level;// * log((*itA)->level);
            sum += tmp;
            ans += tmp * maxSim;
        }
    }
    return ans / sum;
//return getSimilarity(A->root, B->root);
}

void init() {
    for (int i = 0; i < HASH_TOT; ++i) {
        powBase[i][0] = 1;
        for (int j = 1; j < MAX_TREE_SIZE; ++j) {
            powBase[i][j] = powBase[i][j - 1] * hashBase[i];
        }
    }
}

const int AST = 0;
const int MOSS = 1;
const int JPLAG = 2;
int ans[MAXFILE][MAXFILE][5];

vector <string> vecFiles;
int fileTot = 0;
map <string, int> mpFile;

int abstract(char *st) {
    int len = strlen(st);
    int tmp = 0;
    for (int i = 0; i < len; ++i) {
        if (st[i] >= '0' && st[i] <= '9') {
            tmp = tmp * 10 + st[i] - '0';
        }
    }
    return tmp;
}

void getMossMatrix(char *fileName) {
    freopen(fileName, "r", stdin);
    int line;
    char file1[20], file2[20], c1[20], c2[20];
    for (; scanf("%s%s%s%s%d", file1, c1, file2, c2, &line) != EOF; ) {
        ans[mpFile[string(file1)]][mpFile[string(file2)]][MOSS] = (abstract(c1) + abstract(c2)) / 2;
        ans[mpFile[string(file2)]][mpFile[string(file1)]][MOSS] = (abstract(c1) + abstract(c2)) / 2;
    }
    fclose(stdin);
}

void getJPlagMatrix(char *fileName) {
    freopen(fileName, "r", stdin);
    double w;
    char st[100];
    for (; scanf("%s%lf", st, &w) != EOF; ) {
        string tmp = string(st);
        int cutPos = tmp.find_first_of('-');
        string file1, file2;
        file1 = tmp.substr(0, cutPos);
        file2 = tmp.substr(cutPos + 1, tmp.length() - 2 - cutPos);
        ans[mpFile[file1]][mpFile[file2]][JPLAG] = round(w);
        ans[mpFile[file2]][mpFile[file1]][JPLAG] = round(w);
    }
}

void transferNoInclude(string fileName) {
    ofstream fout("now.cpp");
    ifstream fin(fileName.c_str());
    string st;
    while (getline(fin, st)) {
        if (st.find("include") >= st.length())
        fout << st << endl;
    }
}

void getAST(char *pathName) {
    string path = string(pathName);
    for (int i = 0; i < fileTot; ++i) {
        string fileName = path  + vecFiles[i];
        transferNoInclude(fileName);
        tree[i] = new Tree("now.cpp");
        }
    for (int i = 0; i < fileTot / 2; ++i) {
        for (int j = fileTot / 2; j < fileTot; ++j) {
            //if (i != 18 && i != 44) continue;
            ans[j][i][AST] = round(100 * compare(tree[i], tree[j]));
            ans[i][j][AST] = ans[j][i][AST];
        }
    }
    //printf("%")
}

void getCppFiles() {
    fileTot = 0;
    string base[2] = {"orig", "plag"};
    for (int k = 0; k < 2; ++k)
    for (int i = 1; i <= 30; ++i) {
        if (i >= 5 && i <= 6) continue;
        if (i >= 8 && i <= 9) continue;
        //if (i != 23) continue;
        char intTmp[10];
        sprintf(intTmp, "%d", i);
        vecFiles.push_back(base[k] +  string(intTmp) + ".cpp");
        //cout << vecFiles.back() << endl;
        mpFile[vecFiles.back()] = fileTot++;
    }
}

void printAns() {
    char fileName[15] = "result.txt";
    FILE *file = fopen(fileName, "w");
    fprintf(file, "AST/Moss/JPlag:\n");
    for (int i = fileTot/2; i < fileTot; ++i) {
        fprintf(file, "\t%s", vecFiles[i].c_str());
    }
    fprintf(file, "\n");
    for (int i = 0; i < fileTot / 2; ++i) {
        fprintf(file, "%s", vecFiles[i].c_str());
        for (int j = fileTot / 2; j < fileTot; ++j) {
            fprintf(file, "\t%d/%d/%d", ans[i][j][AST], ans[i][j][MOSS], ans[i][j][JPLAG]);
        }
        fprintf(file, "\n");
    }
}

void printBigDiff() {
    char fileName[20] = "bigDiff.txt";
    FILE *file = fopen(fileName, "w");
    fprintf(file, "AST/Moss/JPlag:\n");
    const int lim = 10, plagLim = 30;
    for (int i = 0; i < fileTot / 2; ++i) {
        for (int j = fileTot / 2; j < fileTot; ++j) {
            int flag = 0;
            for (int ti = 0; ti < 3; ++ti) {
                for (int tj = 0; tj < 3; ++tj) {
                    if (fabs(ans[i][j][ti] - ans[i][j][tj]) > lim) {
                        flag = 1;
                    }
                }
            }
            if (flag) {
                flag = 0;
                for (int ti = 0; ti < 3; ++ti) {
                    if (ans[i][j][ti] > plagLim) flag = 1;
                }
            }
            if (flag) {
                fprintf(file, "%s vs. %s : %d/%d/%d\n", vecFiles[i].c_str(), vecFiles[j].c_str(), ans[i][j][AST], ans[i][j][MOSS], ans[i][j][JPLAG]);
            }
        }
        //printf("\n");
    }
}

int main(int argc, char* argv[]) {
    //1. cpp path
    //2. jplag txt
    //3. moss txt
    init();
    mpLabel.clear();
   
//#ifdef COMPARE_MOSS_JPLAG
    if (string(argv[1]) == "com") {
        getCppFiles();
        getMossMatrix(argv[4]);
        getJPlagMatrix(argv[3]);
        getAST(argv[2]);
        
        //tree[18]->dfsCheckTree(tree[18]->root, 0);
        //tree[44]->dfsCheckTree(tree[44]->root, 0);
        printAns();
        printBigDiff();
        //cout << vecFiles[18] << vecFiles[44] << endl;
    } else {
        transferNoInclude(string(argv[2]));
        Tree *A = new Tree("now.cpp");
        transferNoInclude(string(argv[3]));
        Tree *B = new Tree("now.cpp");
        cout << compare(A, B) << endl;
        //A->dfsCheckTree(A->root, 0);
        //B->dfsCheckTree(B->root, 0);
//printf("%.5lf\n", compare(A, B));
    }
//#else

//#endif
    return 0;
}