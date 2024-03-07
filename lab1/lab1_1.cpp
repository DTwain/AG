#include <iostream>
#include <vector>
#include <fstream>
std::ifstream fin("fisier.txt");

int **matricea_de_adiacenta(int *n, std::vector<std::pair<int,int>> *vec){
    int **mat = new int*[*n];
    for (int i = 0; i < *n; ++i)
        mat[i] = new int[*n]{ 0 };

    for (int i = 0; i < (int)vec -> size(); ++i){
        std::pair<int, int> *local_pair = new std::pair<int, int>;
        *local_pair = (*vec)[i];
        mat[local_pair -> first - 1][local_pair -> second - 1] = 1;
        mat[local_pair -> second - 1][local_pair -> first - 1] = 1;
        delete local_pair;   
    }
    return mat;
}
std::vector<std::vector<int>> *mat_de_adicenta__to__lista_de_adicenta(int *n, int **mat){
    std::vector<std::vector<int>> *lista_de_adiacenta = new std::vector<std::vector<int>>;
    
    for (int i = 0; i < *n; ++i){
        std::vector<int> *puncte_incidente_cu_i = new std::vector<int>;
        for (int j = 0; j < *n; ++j)
            if (mat[i][j] == 1)
                puncte_incidente_cu_i -> push_back(j + 1);
        lista_de_adiacenta -> push_back(*puncte_incidente_cu_i);
        delete puncte_incidente_cu_i;
    }
    return lista_de_adiacenta;
}

typedef struct{
    int **mat_de_incidenta;
    std::vector<std::pair<int,int>> *muchie_corespunzatoare_coloanei;
    int *nr_muchi_distincte;
}structure;  

structure *lista_de_adiacenta__to__matricea_de_incidenta(int *n, std::vector<std::vector<int>> *lista_de_adicenta){
    /*
    Numarul de coloane il vom determina prin numararea a cate numere sunt mai mari decat fiecare nod de la 1 la n, inclusiv
    1: 2, 
    2: 1, 3, 4, 
    3: 2, 4, 
    4: 2, 3, 
    Pentru nodul 1 -> il avem doar pe 2 mai mare decat 1
    Pentru nodul 2 -> ii avem pe 3 si 4 mai mari decat 2
    Pentru nodul 3 -> il avem doar de 4 mai mare decat 3
    Pentru nodul 4 -> nu avem niciun nod mai mare decat el, incident cu acesta
    -> 1 + 2 + 1 = 4 coloane
    Realizam aceasta operatie pentru a evita cazul cand muchile se repeta in fisierul de intrare.
    Daca am avea certitudinea ca muchile din fisier sunt distincte, le - am numara si acela ar fi numarul de coloane. 
    */
    structure *mat_de_incidenta_lista_de_muchi = new structure;
    mat_de_incidenta_lista_de_muchi -> nr_muchi_distincte = new int{ 0 };
    mat_de_incidenta_lista_de_muchi -> muchie_corespunzatoare_coloanei = new std::vector<std::pair<int,int>>;

    for(unsigned int i = 0; i < lista_de_adicenta->size(); ++i)
        for(unsigned int j = 0; j < (*lista_de_adicenta)[i].size(); ++j)
            if (i + 1 < (*lista_de_adicenta)[i][j]){
                *mat_de_incidenta_lista_de_muchi -> nr_muchi_distincte += 1;
                mat_de_incidenta_lista_de_muchi -> muchie_corespunzatoare_coloanei -> push_back(std::pair<int,int>(i + 1, (*lista_de_adicenta)[i][j]));
            }
    // alocam dinamic matricea de incidenta
    mat_de_incidenta_lista_de_muchi -> mat_de_incidenta = new int*[*n];
    for(int i = 0; i < *n; ++i)
        mat_de_incidenta_lista_de_muchi -> mat_de_incidenta[i] = new int[(int)*mat_de_incidenta_lista_de_muchi -> nr_muchi_distincte]{ 0 };
    
    int *cnt_muchi_adaugate = new int{ 0 };
    for(unsigned int i = 0; i < lista_de_adicenta -> size(); ++i)
        for(unsigned int j = 0; j < (*lista_de_adicenta)[i].size(); ++j)
            if (i + 1 < (*lista_de_adicenta)[i][j]){
                mat_de_incidenta_lista_de_muchi -> mat_de_incidenta[(*lista_de_adicenta)[i][j] - 1][*cnt_muchi_adaugate] = 1;
                mat_de_incidenta_lista_de_muchi -> mat_de_incidenta[i][*cnt_muchi_adaugate] = 1;
                ++(*cnt_muchi_adaugate);
            }
    delete cnt_muchi_adaugate;

    return mat_de_incidenta_lista_de_muchi;
}

std::vector<std::vector<int>> *matricea_de_incidenta__to__lista_de_adicenta(int *nr_noduri, int *nr_muchi_distincte, int **mat_de_incidenta){
    std::vector<std::vector<int>> *lista_de_adicenta = new std::vector<std::vector<int>>;
    for(unsigned int i = 0; i < *nr_noduri; ++i){
        std::vector<int> *vec = new std::vector<int>;
        for(unsigned int j = 0; j < *nr_muchi_distincte; ++j)
            if(mat_de_incidenta[i][j] == 1)
                for(unsigned int k = 0; k < *nr_noduri; ++k)
                    if( k != i && mat_de_incidenta[k][j] == 1){ 
                        vec -> push_back(k + 1);
                        break;
                    }
        lista_de_adicenta -> push_back(*vec);
    }
    return lista_de_adicenta;
}

int **lista_de_adiacenta__to__matricea_de_adicenta(std::vector<std::vector<int>> *lista_de_adicenta){
    int **mat_de_adiacenta = new int*[(int)lista_de_adicenta -> size()];
    for(int i = 0; i < (int)(lista_de_adicenta -> size()); ++i)
        mat_de_adiacenta[i] = new int[(int)lista_de_adicenta -> size()]{ 0 };
    
    for(unsigned int i = 0; i < (int)(lista_de_adicenta -> size()); ++i)
        for(unsigned int j = 0; j < (int)((*lista_de_adicenta)[i].size()); ++j){
            mat_de_adiacenta[i][(*lista_de_adicenta)[i][j] - 1] = 1;
            mat_de_adiacenta[(*lista_de_adicenta)[i][j] - 1][i] = 1;
        }
    return mat_de_adiacenta;
}
int main() {
    int *n = new int{ 0 };
    std::vector<std::pair<int,int>> *vec = new std::vector<std::pair<int,int>>;
    fin >> *n;
    int *a = new int{ 0 };
    int *b = new int{ 0 };
    while(fin >> *a >> *b)
        vec -> push_back(std::make_pair(*a, *b));
    
    delete a, b;
    a, b = NULL, NULL;

    // Fisier -> matrice de adiacenta
    int **mat_adiacenta = matricea_de_adiacenta(n, vec);
    for(int i = 0; i < *n; ++i, std::cout<<'\n')
        for(int j = 0; j < *n; ++j)
            std::cout<< mat_adiacenta[i][j] <<" ";
    std::cout<<'\n';

    delete vec; // dealocam vectorul in care am stocat perechile din fisier
    vec = NULL;

    // matrice de adiacenta -> lista adiacenta
    std::vector<std::vector<int>> *lista_de_adiacenta = mat_de_adicenta__to__lista_de_adicenta(n, mat_adiacenta);
    for(int i = 0; i < *n; ++i, std::cout<<'\n'){
        std::cout<< i + 1 <<": ";
        for(unsigned int j = 0; j < (*lista_de_adiacenta)[i].size(); ++j)
            std::cout<< (*lista_de_adiacenta)[i][j] <<", ";
    }   
    for(int i = 0; i < *n; ++i)
        delete mat_adiacenta[i];
    delete mat_adiacenta;
    mat_adiacenta = NULL;

    // lista adiacenta -> matrice de incidenta
    structure *rezultat = lista_de_adiacenta__to__matricea_de_incidenta(n, lista_de_adiacenta);
    std::cout<<"\nU = { ";
    for(unsigned int i = 0; i < (int)(rezultat -> muchie_corespunzatoare_coloanei -> size()); ++i)
        std::cout<<"("<<(*rezultat -> muchie_corespunzatoare_coloanei)[i].first<<", "<<(*rezultat -> muchie_corespunzatoare_coloanei)[i].second<<"), ";
    std::cout<<"} \n";

    for(int i = 0; i < *n; ++i, std::cout<<'\n')
        for(unsigned int j = 0; j < *rezultat -> nr_muchi_distincte; ++j)
            std::cout<< rezultat -> mat_de_incidenta[i][j] << " "; 
    delete lista_de_adiacenta;
       

    // matrice de incidenta -> lista adiacenta
    std::cout<< '\n';
    std::vector<std::vector<int>> *lista_de_adiacenta_2 = matricea_de_incidenta__to__lista_de_adicenta(n, rezultat -> nr_muchi_distincte, rezultat -> mat_de_incidenta);
    for (unsigned int i = 0; i < int(lista_de_adiacenta_2 -> size()); ++i, std::cout<<'\n'){
        std::cout<< i + 1 << ": ";
        for(unsigned int j = 0; j < int((*lista_de_adiacenta_2)[i].size()); ++j)
            std::cout<< (*lista_de_adiacenta_2)[i][j] << " ";
    }
    delete rezultat;

    // lista adiacenta -> matrice de adiacenta
    std::cout<<'\n';
    int **mat_de_adiacenta = lista_de_adiacenta__to__matricea_de_adicenta(lista_de_adiacenta_2);
    for(int i = 0; i < *n; ++i, std::cout<<'\n')
        for(int j = 0; j < *n; ++j)
            std::cout<< mat_de_adiacenta[i][j] <<" ";

    for(int i = 0; i < *n; ++i)
        delete mat_de_adiacenta[i];
    delete mat_de_adiacenta;
    mat_de_adiacenta = NULL;

    delete n;
    n = NULL;

	fin.close();
	return 0;
}