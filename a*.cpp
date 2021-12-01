#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#define MAX 10000
#define se second
#define f first
#define mp make_pair
using namespace std;
typedef pair<int, int> p;
int n, m;
char graphic[MAX][MAX];
int dist[MAX][MAX];
int visited[MAX][MAX];
p father[MAX][MAX];
pair<int , int> s, e;
vector<p> path;
priority_queue<pair<int, p >, vector<pair<int, p> >, greater< pair<int, p> > > fila;
int movesX[5] = {1, 0, -1, 0};
int movesY[5] = {0, 1, 0, -1};
int distances(int i, int j){
      int x_cost_end = abs(i - e.f);
      int x_cost_start = abs(i - s.f);
      int y_cost_end = abs(j - e.se);
      int y_cost_start = abs(j - s.se);
      int total_cost = x_cost_end + x_cost_start + y_cost_end + y_cost_start;
      return total_cost;

}
void find_Path(int x2, int y2){
  path.push_back(mp(x2, y2));
  if(x2 == (int)s.f && y2 == (int)s.se){
    return;
  }
  p fth = father[x2][y2];
  find_Path(fth.f, fth.se);
}
void search(int x ,int y){
    fila.push(mp(distances(x, y), mp(x, y)));
    visited[x][y] = 1;
    father[x][y] = mp(x, y);
    while(!fila.empty()){
        pair<int, p> v = fila.top();
        fila.pop();
        if((int)v.se.f == (int)e.f && (int)v.se.se == (int)e.se){
          find_Path(v.se.f, v.se.se);
          return;
        }
        for(int i = 0; i < 4; i++){
            int x1 = v.se.f + movesX[i];
            int y1 = v.se.se + movesY[i];
            if(x1 <= 0 || x1 > n || y1 <= 0 || y1 > m) continue;
            if(visited[x1][y1] == 0 && graphic[x1][y1] != '#'){
                visited[x1][y1] = 1;
                father[x1][y1] = mp(v.se.f, v.se.se);
                fila.push(mp(distances(x1, y1), mp(x1, y1)));
            }
        }
    }

}
int main(){
    char in;
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> in;
            if(in == 's'){
                s = mp(i, j);
            } else if(in == 'e'){
                e = mp(i, j);
            }
            graphic[i][j] = in;
        }
    }
    search(s.f, s.se);
    cout << path.size() << '\n';
}
