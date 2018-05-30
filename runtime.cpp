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
        if (a[k]<data[k][j]-data[k][i]){
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
  if (n[0]>0){
    ans.command += "buy(A," + toS(s[0],n[0]) + ");"+"sell(A," + toS(t[0],n[0]) + ");";
  }
  if (n[1]>0){
    ans.command += "buy(B," + toS(s[1],n[1]) + ");"+"sell(B," + toS(t[1],n[1]) + ");";
  }
  if (n[2]>0){
    ans.command += "buy(C," + toS(s[2],n[2]) + ");"+"sell(C," + toS(t[2],n[2]) + ");";
  }
  ans.value = best;
  return ans;
}


answer solve(int s,int t,int cp){
  answer ans;
  int a = (data[0][t]-data[0][s]);
  int b = (data[1][t]-data[1][s]);
  int c = (data[2][t]-data[2][s]);
  int sa=s,sb=s,sc=s;
  int ta=t,tb=t,tc=t;
  for (int i = s+1;i<t-9;i++){
    for (int j = i+10;j<=t;j++){
      if (a<data[0][j]-data[0][i]){
        a=data[0][j]-data[0][i];
        sa = i;
        ta=j;
      }
      if (b<data[1][j]-data[1][i]){
        b=data[1][j]-data[1][i];
        sb = i;
        tb=j;
      }
      if (c<=data[2][j]-data[2][i]){
        c=data[2][j]-data[2][i];
        sc = i;
        tc=j;
      }
    }
  }
  if (sa!=s&&sb!=s&&sc==s){
    ans.value = -1;
    ans.command = "";
    return ans;
  }
  if (ta!=t&&tb!=t&&tc==t){
    ans.value = -1;
    ans.command = "";
    return ans;
  }
  int na = 0,nb=0,nc=0;
  if(cp>=(a>0)*data[0][sa]*M+(b>0)*data[0][sb]*M+(c>0)*data[0][sc]*M){
    na = (a>0)*M;
    nb = (b>0)*M;
    nc = (c>0)*M;
    ans.command = "";
    if(na>0)ans.command+="buy(A," + toS(s,na) + ");"+"sell(A," + toS(t,na) + ");";
    if(nb>0)ans.command+="buy(B," + toS(s,nb) + ");"+"sell(B," + toS(t,nb) + ");";
    if(nc>0)ans.command+="buy(C," + toS(s,nc) + ");"+"sell(C," + toS(t,nc) + ");";
    ans.value = a*na+b*nb+c*nc+cp;
    return ans;
  }
  int best = 0;
  for(int i=0;i<=min(M,cp/data[0][sa]);i++){
    //二分探索
    for(int j=0;j<=min(M,(cp-i*data[0][sa])/data[1][sb]);j++){
      int k = min(M,(cp-i*data[0][sa]-j*data[1][sb])/data[2][sc]);
      int latest = i*a+j*b+k*c*(c>0);
      if(best<latest){
        best = latest;
        na=i;nb=j;nc=k*(c>0);
      }
      if(b<0)break;
    }
    if(a<0)break;
  }
  ans.command = "";
  if(na>0)ans.command+="buy(A," + toS(sa,na) + ");"+"sell(A," + toS(ta,na) + ");";
  if(nb>0)ans.command+="buy(B," + toS(sb,nb) + ");"+"sell(B," + toS(tb,nb) + ");";
  if(nc>0)ans.command+="buy(C," + toS(sc,nc) + ");"+"sell(C," + toS(tc,nc) + ");";
  ans.value = best+cp;
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
        answer ans_i_t = gready(i,t,ans[i].value);
        if (ans_i_t.value>ans[t].value){
          ans[t].value = ans_i_t.value;
          ans[t].command = ans[i].command + ans_i_t.command;
        }
      }
      //std::cout <<t << std::endl;
    }
  }
  std::cout << ans[319].command;  
}
