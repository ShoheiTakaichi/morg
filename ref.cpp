#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)

//コードの短縮のため、マクロを使わせていただきます。
#define toS(x,y) std::to_string(x)+","+std::to_string(y)

extern int data[3][320];

#define  M  10000
struct answer{
  int value;
  std::string command;
};//解とそれを実現する命令

answer gready(int S,int T,int cp,bool w){
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
        //if (a[k]/data[k][s[k]]<(data[k][j]-data[k][i])/data[k][i]){
        if (a[k]<data[k][j]-data[k][i]){
          a[k] =data[k][j]-data[k][i];
          s[k] =i;
          t[k] =j;
        }
      }
    }
  }
  int best = 0;
  
  if (!w){
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
  }
  
  if(w){
  for (int i=0;i<=(a[0]>0)*min(M,cp/data[0][s[0]]);i++){
    int cp2 = cp - i*data[0][s[0]];
    for (int j=0;j<=(a[1]>0)*min(M,cp2/data[1][s[1]]);j++){
      int cp3 = cp2 -j*data[1][s[1]];
      int k = (a[2]>0)*min(M,cp3/data[2][s[2]]);
      int score = a[0]*i + a[1]*j + a[2]*k;
      if (score>best){
        n[0]=i;n[1]=j;n[2]=k;
        best = score;
      }
    }
  }
  }

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
std::string iTostock(int i){
  if (i==0)return "A";
  if (i==1)return "B";
  return "C";
}

answer isorate_gready(int S,int T,int cp){
  answer ans;
  std::vector<std::vector<answer>>dp(3,std::vector<answer>(T-S+1));
  dp[0][0].value = cp;
  dp[1][0].value = cp;
  dp[2][0].value = cp;
  std::string temp;
  for(int i = 0;i<3;i++){
    for(int s = 1;s+S<=T;s++){
       dp[i][s]=dp[i][s-1];
       if(s>9){
         for(int ss=0;ss<s-9;ss++){
           if(dp[i][ss].value+(data[i][s+S]-data[i][ss+S])*M > dp[i][s].value){
             dp[i][s].value = dp[i][ss].value + (data[i][s+S]-data[i][ss+S])*M; 
             dp[i][s].command = dp[i][ss].command + "buy("+iTostock(i)+","+std::to_string(S+ss)+");"+ "sell("+iTostock(i)+","+std::to_string(S+s)+");";
           }
         }
       }
    }
  }
  ans.value = dp[0][T-S].value+ dp[1][T-S].value+ dp[2][T-S].value -cp-cp;
  ans.command = dp[0][T-S].command+ dp[1][T-S].command+ dp[2][T-S].command;
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
        answer ans_i_t;
        if(ans[i].value>M*(data[0][i]+data[1][i]+data[2][i])){
           ans_i_t = isorate_gready(i,t,ans[i].value);
        }else{
          ans_i_t = gready(i,t,ans[i].value,(i<0));
        }
        if (ans_i_t.value>ans[t].value){
          ans[t].value = ans_i_t.value;
          ans[t].command = ans[i].command + ans_i_t.command;
        }
      }
      //std::cout <<t << std::endl;
    }
  }
  std::cout << ans[319].command << std::endl;;  
  std::cout << ans[319].value << std::endl;
}
