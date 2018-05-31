#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define min(a,b) ((a<b)?a:b)

//コードの短縮のため、マクロを使わせていただきます。
#define toS(x,y) std::to_string(x)+","+std::to_string(y)

extern int data[3][320];

#define  M  10000
struct answer{
  int value;
  std::string command;
};//解とそれを実現する命令

std::string itocom (int st,int n,int buy,int sell){
  std::string stock = "";
  if (n==0)return stock;
  if (st==0) stock = "A,";
  if (st==1) stock = "B,";
  if (st==2) stock = "C,";
  std::string ans = "buy("+stock+toS(buy,n)+");sell("+stock+toS(sell,n)+");";
  return ans;
}


answer gready(int S,int T,int cp){
  //制約付きナップザザック
  answer ans;
  std::vector<int> a(3);
  std::vector<int> n(3);
  for (int i=0;i<3;i++){
    a[i] = (data[i][T]-data[i][S]);
    n[i] = 0;
  }
  std::vector<int>s(3);
  std::vector<int>t(3);
  for(int i=0;i<3;i++){
    s[i]=S;t[i]=T;
  }
  for (int i = S+1;i<T-9;i++){
    for (int j = i+10;j<=T;j++){
      for (int k=0;k<3;k++){
        if ((double)a[k]/(double)data[k][s[k]]<(double)(data[k][j]-data[k][i])/(double)data[k][i]){
          a[k] =data[k][j]-data[k][i];
          s[k] =i;
          t[k] =j;
        }
      }
    }
  }
  int best = 0;
  std::vector<int> v(3);for(int i=0;i<3;i++)v[i]=i;
  do{
    int score = 0;
    int lest_cp=cp;
    for (int i=0;i<3;i++){
      if (a[v[i]]>0)
      score += a[v[i]]*min(M,lest_cp/data[v[i]][s[v[i]]]);
      lest_cp -= min(M,lest_cp/data[v[i]][s[v[i]]])*data[v[i]][s[v[i]]];
    }
    if (best<score){
      lest_cp=cp;
      for(int i=0;i<3;i++){
        n[v[i]] =(a[v[i]]>0)*min(M,lest_cp/data[v[i]][s[v[i]]]);
        lest_cp -=n[v[i]]*data[v[i]][s[v[i]]];
      }
      best = score;
    }
  }while(next_permutation(v.begin(),v.end()));
  best += cp;
  ans.command = "";
  for (int k=0;k<3;k++){
    ans.command += itocom(k,n[k],s[k],t[k]);
  }
  ans.value = best;
  return ans;
}
answer separate_gready(int S,int T,int st){
  //制約付きナップザザック
  answer ans;
  int a = (data[st][T]-data[st][S]);
  int n;
  int s=S;
  int t=T;
  for (int i = S+1;i<T-9;i++){
    for (int j = i+10;j<=T;j++){
      if (a<data[st][j]-data[st][i]){
        a =data[st][j]-data[st][i];
        s =i;
        t =j;
      }
    }
  }
  ans.value = M*a;
  ans.command = itocom(st,M,s,t);
  return ans;
}




int main(){
  answer ans[320];
  ans[0].value=10000;
  for (int t = 0;t<320;t++){
    if (t<10){
      ans[t].value = 10000;
    }else{
      ans[t] = ans[t-1];
      for (int i = 0;i<t-9;i++){
        if (ans[i].value<M*data[0][i]+M*data[1][i]+M*data[2][i]){
          answer ans_i_t = gready(i,t,ans[i].value);
          if (ans_i_t.value>ans[t].value){
            ans[t].value = ans_i_t.value;
            ans[t].command = ans[i].command + ans_i_t.command;
          }
        }
        else{
          
        }
      }
      //std::cout <<t << std::endl;
    }
  }
  std::cout << ans[319].command;
}















