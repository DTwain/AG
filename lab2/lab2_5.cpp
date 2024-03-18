#include <iostream>
#include <queue>
#include <map>
#include <fstream>

std::ifstream fin("graf.txt");
typedef std::map<int, std::vector<int>> dict;

void dfs(dict *lista_de_adiacenta, bool *visited, int nod){
     visited[nod] = true;
     std::cout<< nod << " ";
     for(int i = 0; i < (*lista_de_adiacenta)[nod].size(); ++i)
          if(visited[(*lista_de_adiacenta)[nod][i]] == false)
               dfs(lista_de_adiacenta, visited, (*lista_de_adiacenta)[nod][i]);
}

int main(){
     dict *lista_de_adiacenta = new dict;
     int n;
     fin >> n;
     bool *visited = new bool[n + 1]{ false };
     int a = 0,
          b = 0;
     while(!fin.eof()){
          fin >> a >> b;
          (*lista_de_adiacenta)[a].push_back(b);
     }
     dfs(lista_de_adiacenta, visited, 1);

     delete[] visited;
     delete lista_de_adiacenta;
     return 0;
}
