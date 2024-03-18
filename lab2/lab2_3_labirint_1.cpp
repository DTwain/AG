#include <iostream>
#include <fstream>
#include <string>
#include <queue>
std::ifstream fin("labirint_1.txt");

const int dir_X[] = {0, -1, 0, 1},
          dir_Y[] = {-1, 0, 1, 0};

void Lee(int **labirint_int){
     std::queue<std::pair<int, int>> q;
     int poz_start_x = 0, 
          poz_start_y = 0,
          poz_final_x = 20,
          poz_final_y = 0;
     for(int i = 0; i < 41; ++i){
          if(labirint_int[0][i] == -1)
               poz_start_y = i;
          if(labirint_int[20][i] == -1)
               poz_final_y = i;
     }

     q.push(std::make_pair(poz_start_x, poz_start_y));
     labirint_int[poz_start_x][poz_start_y] = 1;
     labirint_int[poz_final_x][poz_final_y] = 0;
     while(!q.empty()){
          int x_local = q.front().first,
               y_local = q.front().second;
          for(int i = 0; i <= 3; ++i){
               int x_nou = x_local + dir_X[i],
                    y_nou = y_local + dir_Y[i]; 
               if(x_nou >= 0 && x_nou <= 20 && y_nou >= 0 && y_nou <= 40 && labirint_int[x_nou][y_nou] == 0){
                    labirint_int[x_nou][y_nou] = labirint_int[x_local][y_local] + 1;
                    q.push(std::make_pair(x_nou, y_nou));
               }
          }
          q.pop();
     }
}
std::pair<int,int> cautare_poz_final(int **labirint_int){
     int poz_final_x = 20,
          poz_final_y = 0;
     for(int i = 0; i < 41; ++i){
          if(labirint_int[20][i] == -1)
               poz_final_y = i;
     }
     return std::make_pair(poz_final_x, poz_final_y);
}

void reconstruire(int **labirint_int, char **labirint_final, int poz_final_x, int poz_final_y){
     int poz_x = poz_final_x,
          poz_y = poz_final_y;
     labirint_final[poz_x][poz_y] = '@';
     do{
          int poz_vec_dir = -1;
          for(int i = 0; i <= 3 && poz_vec_dir == -1; ++i)
               if(labirint_int[poz_x + dir_X[i]][poz_y + dir_Y[i]] + 1 == labirint_int[poz_x][poz_y]){
                    poz_x += dir_X[i];
                    poz_y += dir_Y[i];
                    poz_vec_dir = i;
               }
          labirint_final[poz_x][poz_y] = '@';
          
     }while(labirint_int[poz_x][poz_y] != 1);
}
int main(){
     char **labirint = new char*[21];
     for(int i = 0; i < 21; ++i)
          labirint[i] = new char[42];

     // convertim fiecare linie citita intr-o matrice ce stocheaza int - uri
     int **labirint_int = new int*[41];
     for(int i = 0; i < 41; ++i)
          labirint_int[i] = new int[41]{ 0 };

     for(int i = 0; i < 21; ++i){
          fin.getline(labirint[i], 42);
          for(int j = 0; j < 41; ++j)
               if(labirint[i][j] == '1')
                    labirint_int[i][j] = -2; // blocat
               else if(labirint[i][j] == '0')
                    labirint_int[i][j] = 0; // liber
               else if(labirint[i][j] == 'S' || labirint[i][j] == 'F')
                    labirint_int[i][j] = -1; // inceput / final
     }

     std::pair<int,int> poz_final = cautare_poz_final(labirint_int);
     Lee(labirint_int);
     reconstruire(labirint_int, labirint, poz_final.first, poz_final.second);

     for(int i = 0; i < 21; ++i, std::cout<< "\n")
          for(int j = 0; j < 41; ++j)
               printf("%2c", labirint[i][j]);

     for(int i = 0; i < 21; ++i)
          delete[] labirint[i];
     delete[] labirint;

     for(int i = 0; i < 21; ++i)
          delete[] labirint_int[i];
     delete[] labirint_int;

     return 0;
}