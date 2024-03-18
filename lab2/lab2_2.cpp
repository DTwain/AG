#include <iostream>
#include <fstream>

std::ifstream fin("graf.txt");

void inchiderea_tranzitiva(bool **mat_de_adicenta, int n){
     bool **mat_drumurilor = new bool*[n];
     for(int i = 0; i < n; ++i)
          mat_drumurilor[i] = new bool[n];

     for(int i = 0; i < n; ++i)
          for(int j = 0; j < n; ++j)
               mat_drumurilor[i][j] = mat_de_adicenta[i][j];
     
     for(int k = 0; k < n; ++k)
          for(int i = 0; i < n; ++i)
               for(int j = 0; j < n; ++j)
                    if(mat_drumurilor[i][j] == 0)
                         mat_drumurilor[i][j] = mat_drumurilor[i][k] * mat_drumurilor[k][j];
     
     for(int i = 0; i < n; ++i, std::cout<<"\n")
          for(int j = 0; j < n; ++j)
               std::cout<< mat_drumurilor[i][j] << " ";
     
     // dealocam mat_drumurilor
     for(int i = 0; i < n; ++i)
          delete[] mat_drumurilor[i];
     delete[] mat_drumurilor;


}

int main(){
     int n; 
     fin >> n;

     bool **mat_adiacenta = new bool*[n];
     for(int i = 0; i < n; ++i){
          mat_adiacenta[i] = new bool[n]{ 0 };
          mat_adiacenta[i][i] = 1;
     }

     int u = 0, v = 0;
     while(!fin.eof()){
          fin >> u >> v;
          mat_adiacenta[u][v] = 1;          
     }
     
     inchiderea_tranzitiva(mat_adiacenta, n);

     for(int i = 0; i < n; ++i)
          delete[] mat_adiacenta[i];
     delete[] mat_adiacenta;

     fin.close();
     return 0;
}