#include <iostream>
#include <fstream>
#include <vector>
std::ifstream fin("fisier.txt");

bool **citire_mat_de_adiacenta(bool **mat_de_adiacenta, int *nr_noduri){
     for(unsigned int i = 0; i < *nr_noduri; ++i)
          for(unsigned int j = 0; j < *nr_noduri; ++j)
               fin >> mat_de_adiacenta[i][j];

     return mat_de_adiacenta;
}
std::vector<int> *det_noduri_izolate(std::vector<int> *noduri_izolate, int *n, bool **mat_de_adiacenta){
     for(unsigned int i = 0; i < *n; ++i){
          bool nod_adiacent_cu_i_gasit = false;
          for(unsigned int j = 0; j < *n; ++j)
               if(mat_de_adiacenta[i][j]){
                    nod_adiacent_cu_i_gasit = true;
                    break;
               }
          if(!nod_adiacent_cu_i_gasit) 
               noduri_izolate -> push_back(i);
     }
     return noduri_izolate;

}
bool det_daca_graful_este_regular(int *n, bool **mat_de_adiacenta){
     int *grad_nod_1 = new int{ 0 };
     for(unsigned int i = 0; i < *n; ++i)
          (*grad_nod_1) += (int)mat_de_adiacenta[0][i];
     bool este_regular = true;
     for(unsigned int i = 1; i < *n; ++i){
          unsigned int grad_nod_curent = 0; 
          for(unsigned int j = 0; j < *n; ++j)
               grad_nod_curent += (int)mat_de_adiacenta[i][j];
          if(*grad_nod_1 != grad_nod_curent){
               este_regular = false;
               break;
          }
     }
     delete grad_nod_1;
     grad_nod_1 = nullptr;
     
     return este_regular;
}
int **det_mat_distantelor(int **mat_distantelor, int *n, bool **mat_de_adicenta){
     for(unsigned int i = 0; i < *n; ++i)
          for(unsigned int j = 0; j < *n; ++j)
               mat_distantelor[i][j] = mat_de_adicenta[i][j];
     
     for(unsigned int i = 0; i < *n; ++i)
               for(unsigned int j = 0; j < *n; ++j)
                    if(i != j && mat_distantelor[i][j] == 0)
                         mat_distantelor[i][j] = 0x3f3f3f3f;

     for(unsigned int k = 0; k < *n; ++k)
          for(unsigned int i = 0; i < *n; ++i)
               for(unsigned int j = 0; j < *n; ++j){
                    if(i != j && mat_distantelor[i][j] > mat_distantelor[i][k] + mat_distantelor[k][j])
                         mat_distantelor[i][j] = mat_distantelor[i][k] + mat_distantelor[k][j];
               }
     
     return mat_distantelor;
}
void DFS(int *nr_noduri, bool *vizitat, bool **mat_de_adicenta, unsigned int nod){
     unsigned int i = 0;
     vizitat[nod] = 1;
     for(i = 0; i < *nr_noduri; ++i)
          if(mat_de_adicenta[nod][i] == 1 && vizitat[i] == 0)
               DFS(nr_noduri, vizitat, mat_de_adicenta, i);
}
bool det_conexitate(int *nr_noduri, bool **mat_de_adicenta){
     bool *vizitat = new bool[*nr_noduri];
     DFS(nr_noduri, vizitat, mat_de_adicenta, 0);
     for(unsigned int i = 0; i < *nr_noduri; ++i)
          if(vizitat[i] == 0){
               delete []vizitat;
               vizitat = nullptr;
               return false;
          }
     delete []vizitat;
     vizitat = nullptr;          
     return true;
}
int main(){
     int *n = new int{ 0 };
     fin >> *n;
     bool **mat_de_adiacenta = new bool*[*n];
     for(unsigned int i = 0; i < *n; ++i)
          mat_de_adiacenta[i] = new bool[*n]{ false };

     mat_de_adiacenta = citire_mat_de_adiacenta(mat_de_adiacenta, n);

     std::vector<int> *noduri_izolate = new std::vector<int>;
     noduri_izolate = det_noduri_izolate(noduri_izolate, n, mat_de_adiacenta);
     if((int)noduri_izolate -> size() > 0){
          std::cout<<"noduri izolate (care sunt, NU cate sunt) : ";
          for(unsigned int i = 0; i < (int)noduri_izolate -> size(); ++i)
               std::cout<< (*noduri_izolate)[i] + 1 <<" ";
          std::cout<<'\n';
     }
     else
          std::cout<< "NU exista noduri izolate!\n";

     // dealocam vectorul pentru nodurile izolate
     delete noduri_izolate;
     noduri_izolate = nullptr;


     if(det_daca_graful_este_regular(n, mat_de_adiacenta))
          std::cout<< "Graful este regular\n";
     else
          std::cout<< "Graful nu este regular\n";

     std::cout<< "Matricea distantelor:\n";
     int **mat_distantelor = new int*[*n];
     for(unsigned int i = 0; i < *n; ++i)
          mat_distantelor[i] = new int[*n]{ 0 };

     mat_distantelor = det_mat_distantelor(mat_distantelor, n, mat_de_adiacenta);
     for(unsigned int i = 0; i < *n; ++i, std::cout<<'\n')
          for(unsigned int j = 0; j < *n; ++j)
               if(i == j || mat_distantelor[i][j] != 0x3f3f3f3f)
                    printf("%5d", mat_distantelor[i][j]);
               else
                    printf("%5s", "inf");
     // dealocam matricea distantelor
     for(unsigned int i = 0; i < *n; ++i){
          delete []mat_distantelor[i];
          mat_distantelor[i] = nullptr;
     }
     delete []mat_distantelor;
     mat_distantelor = nullptr;

     bool este_conex = det_conexitate(n, mat_de_adiacenta);
     if(este_conex)
          std::cout<<"\nEste conex";
     else
          std::cout<<"\nNU este conex!";
     
     for(unsigned int i = 0; i < *n; ++i){
          delete []mat_de_adiacenta[i];
          mat_de_adiacenta[i] = nullptr;
     }
     delete []mat_de_adiacenta;
     mat_de_adiacenta = nullptr;

     delete n;
     n = nullptr;

     fin.close();
     return 0;
}
/*
8 Homicidalmaniac22021973
0 1 0 0 0 0 0 0 
1 0 1 0 0 0 0 0
0 1 0 1 1 0 0 0
0 0 1 0 1 0 0 0
0 0 1 1 0 0 0 0
0 0 0 0 0 0 1 0
0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0
*/