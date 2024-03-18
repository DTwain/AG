#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

typedef std::map<int, std::vector<int>> dict;
std::ifstream fin("graf.txt");
void Moore_alg(dict *lista_de_adiacenta, int *nod_start, int *n){
    std::queue<int> q;
    int *l = new int[*n + 1];
    int *p = new int[*n + 1];
    for(int i = 0 ; i <= *n; ++i)
        l[i] = 0x3f3f3f3f;
    for(int i = 0 ; i <= *n; ++i)
        p[i] = -1;
    q.push(*nod_start);
    l[*nod_start] = 0;
    while(!q.empty()){
        int nod_curent = q.front();
        for(unsigned int i = 0; i < (*lista_de_adiacenta)[nod_curent].size(); ++i)
            if(l[(*lista_de_adiacenta)[nod_curent][i]] == 0x3f3f3f3f){
                p[(*lista_de_adiacenta)[nod_curent][i]] = nod_curent;
                l[(*lista_de_adiacenta)[nod_curent][i]] = l[nod_curent] + 1;
                q.push((*lista_de_adiacenta)[nod_curent][i]);
            }
        q.pop();
    }
    for(int i = 1; i <= *n; ++i)
        std::cout<<l[i]<<" ";
    std::cout<<"\n";
    for(int i = 1; i <= *n; ++i)
        std::cout<<p[i]<<" ";
}

int main(){
    int *n = new int{0};
    dict *lista_de_adiacenta = new dict;
    fin >> *n;
    int *a, *b;
    a = new int{ 0 };
    b = new int{ 0 };
    
    while(fin >> *a >> *b)
        (*lista_de_adiacenta)[*a].push_back(*b);
    
    delete a;
    delete b;
    a = b = nullptr;
    int cnt =  0;
    dict::iterator it = lista_de_adiacenta -> begin();
    while( it != lista_de_adiacenta -> end()){
        std::cout<< it -> first << ": ";
        for(unsigned int i = 0; i < it -> second.size(); ++i)
            std::cout<< it -> second[i]<<" ";
        ++it;
        std::cout << "\n";
    }

    int *nod_de_start = new int{ 0 };
    std::cout << "Alg_MOORE: nod de start: ";
    std::cin >> *nod_de_start;
    Moore_alg(lista_de_adiacenta, nod_de_start, n);


    lista_de_adiacenta -> clear();
    delete lista_de_adiacenta;
    lista_de_adiacenta = nullptr;
    delete n;
    n = nullptr;
    return 0;
}