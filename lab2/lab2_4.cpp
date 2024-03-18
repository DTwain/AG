#include <iostream>
#include <queue>
#include <map>
#include <fstream>

std::ifstream fin("graf.txt");
typedef std::map<int, std::vector<int>> dict;

/*
vizitat - array pentru a vedea prin ce noduri am trecut
vec_distantelor - va stoca distanta pana la nodul x de la nodul sursa
vec_parcurgere_bfs - va stoca nodurile in ordinea descoperirii BFS
q.front() - nodul curent din coada
q.second() - distanta pana la nodul curent
*/
void bfs(dict *lista_de_adiacenta, bool *vizitat, std::vector<int> *vec_distantelor , std::vector<int> *vec_parcurgere_bfs, int nod){
     std::queue<std::pair<int, int>>q;
     q.push(std::make_pair(nod, 1));

     vec_distantelor -> push_back(0);
     vec_parcurgere_bfs -> push_back(nod);
     vizitat[nod] = true;

     while(!q.empty()){
          int nod_curent = q.front().first;
          int distanta_curenta = q.front().second;
          for(int i = 0; i < (*lista_de_adiacenta)[nod_curent].size(); ++i){
               if(vizitat[(*lista_de_adiacenta)[nod_curent][i]] == 0){

                    vec_distantelor -> push_back(distanta_curenta);
                    vec_parcurgere_bfs -> push_back((*lista_de_adiacenta)[nod_curent][i]);
                    vizitat[(*lista_de_adiacenta)[nod_curent][i]] = true;

                    q.push(std::make_pair((*lista_de_adiacenta)[nod_curent][i], distanta_curenta + 1));
               }
          }
          q.pop();

     }
}

int main(){
     dict *lista_de_adiacenta = new dict;
     int n;
     fin >> n;
     bool *visited = new bool[n + 1]{ false };
     std::vector<int> *vec_parcurgere_bfs = new std::vector<int>;
     std::vector<int> *vec_distantelor = new std::vector<int>;
     int a = 0,
          b = 0;
     while(!fin.eof()){
          fin >> a >> b;
          (*lista_de_adiacenta)[a].push_back(b);
     }
     bfs(lista_de_adiacenta, visited, vec_distantelor, vec_parcurgere_bfs, 1);

     for(int i = 0; i < vec_parcurgere_bfs -> size(); ++i)
          std::cout << (*vec_parcurgere_bfs)[i] << " ";
     std::cout<<'\n';
     for(int i = 0; i < vec_distantelor -> size(); ++i)
          std::cout << (*vec_distantelor)[i] << " ";

     delete[] visited;
     delete vec_parcurgere_bfs;
     delete vec_distantelor;
     delete lista_de_adiacenta;
     return 0;
}
