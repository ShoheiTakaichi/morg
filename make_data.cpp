#include <iostream>
#include <vector>
#include <string>
#define min(a,b) ((a<b)?a:b)


//std::string toS(int x) {return std::to_string(x);}
#define toS(x,y) std::to_string(x)+","+std::to_string(y)


const int M = 10000;
extern int data[3][320];


struct gre{
  int value;
  std::string command;
};



gre gready(int s,int t,int cp){
  //制約付きナップザザック
  gre ans;
  int org_cp = cp;
  int a = (data[0][t]-data[0][s]);
  int b = (data[1][t]-data[1][s]);
  int c = (data[2][t]-data[2][s]);
  int na = 0,nb=0,nc=0;
  int best = 0;
  //緩和解周辺の探索
  if (a>b&&a>c){
    na = min(M,cp/data[0][s]);
    cp -= na*data[0][s];
    if (b>c&&b>0){
      nb = min(M,cp/data[1][s]);
      cp -= nb*data[1][s];
      if (c>0){
        nc = min(M,cp/data[2][s]);
        cp -= nc*data[2][s];
      }
    }
    if (c>b&&c>0){
      nc = min(M,cp/data[2][s]);
      cp -= nc*data[2][s];
      if (b>0){
        nb = min(M,cp/data[1][s]);
        cp -= nb*data[1][s];
      }
    }
  }
  if (b>a&&b>c){
    nb = min(M,cp/data[1][s]);
    cp -= nb*data[1][s];
    if (a>c&&a>0){
      na = min(M,cp/data[0][s]);
      cp -= na*data[0][s];
      if (c>0){
        nc = min(M,cp/data[2][s]);
        cp -= nc*data[2][s];
      }
    }
    if (c>a&&c>0){
      nc = min(M,cp/data[2][s]);
      cp -= nc*data[2][s];
      if (a>0){
        na = min(M,cp/data[0][s]);
        cp -= nb*data[0][s];
      }
    }
  }
  if (c>a&&c>b){
    nc = min(M,cp/data[2][s]);
    cp -= nc*data[2][s];
    if (a>b&&a>0){
      nb = min(M,cp/data[1][s]);
      cp -= nb*data[1][s];
      if (a>0){
        na = min(M,cp/data[0][s]);
        cp -= na*data[0][s];
      }
    }
    if (a>b&&a>0){
      na = min(M,cp/data[0][s]);
      cp -= na*data[0][s];
      if (b>0){
        nb = min(M,cp/data[1][s]);
        cp -= nb*data[1][s];
      }
    }
  }
  best = na*a+nb*b+nc*c + org_cp;

  ans.command = "buy(A," + toS(s,na) + ");"+"buy(B," + toS(s,nb) + ");"+"buy(C," + toS(s,nc) + ");"+"sell(A," + toS(t,na) + ");"+"sell(B," + toS(t,nb) + ");"+"sell(C," + toS(t,nc) + ");";
  ans.value = best;
  return ans;
}





int main(){
  std::string a[320];
  std::string temp_str;
  int stock[320][3];
  int capital[320];capital[0]=10000;
  for (int t = 0;t<320;t++){
    if (t<10){
      capital[t] = 10000;
    }else{
      capital[t] = capital[t-1];
      a[t] = a[t-1];
      for (int i = 0;i<t-9;i++){
        gre tempG = gready(i,t,capital[i]);
        if (tempG.value>capital[t]){
          capital[t] = tempG.value;
          a[t] = a[i] + tempG.command;
        }
      }
      //std::cout <<t << std::endl;
    }
  }
  std::cout << a[319];  
}

