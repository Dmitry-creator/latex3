#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
const int N=200001;
map<pair<int,int>,int> mp;
int n,m;
bool used[N];
vector<int> vec[N];
vector<int> f_in;
int t_in[N],f_up[N],timer;
int root;
/*!
        \brief кол-во вершин и кол-во ребер
*/
inline void dfs(int p, int pred){
    int count=0;
    used[p] = true;
    t_in[p]=timer++;
    f_up[p]=t_in[p];
    for (int i=0; i<vec[p].size(); i++){ // перебираем все ребра которые идет из вершины
	int e=vec[p][i];
	if (e==pred){ 
	    continue;
	}
	
	if (e != pred && used[e]){ // если мы были уже в этой вершине 
	    f_up[p]= min(t_in[e], f_up[p]);// так как это обратное ребро то вершина уже посчитана
	}else{
	    if (p == root){ 
		count++;   
	    }
	    dfs(e,p);
	    f_up[p]=min(f_up[e], f_up[p]);// присваиваем посчитанную вершину  вызываем dfs и считаем следующую
	    if (p  != root && t_in[p] <= f_up[e]){
		f_in.push_back(p);
	    }
	}
    }
    if (p == root && count > 1){
	f_in.push_back(p);
    }
}
   
int main(){

    ifstream in("input.txt");
    /*!
        \brief кол-во вершин и кол-во ребер
    */
    in >> n >> m;// кол-во вершин и кол-во ребер
    
    for (int i=0; i<m; i++){
    int p,e;
    
    in >> p;
    in >> e; // считываем вершины
    p--; 
    e--;
    vec[p].push_back(e);// записывыем соединение вершин в двумерный массив
    vec[e].push_back(p);// записываем соединение вершин в обратном порядке
    mp[make_pair(p,e)] =i;// записываем номера пар
    mp[make_pair(e,p)] =i;// записываем номера пар в обрятном порядке
    } 
    in.close();
    ofstream out("output.txt");
    for (int i=0; i<n; i++){
	if (!used[i]){
	    root=i;//запоминаем номер вершины
	    dfs(i, -1);//
	}
    }

    int size=f_in.size();
    sort(f_in.begin(), f_in.end());
        for (int i=0; i<f_in.size(); i++){
	    if (f_in[i]== f_in[i+1]){
		size--;
		f_in[i]=-1;
	    }
		}
    out << size << endl;

    for (int i=0; i<f_in.size(); i++){
	if (f_in[i]!=-1)
	out << f_in[i]+1 << endl;
    }
    out.close();
    return 0;
}
