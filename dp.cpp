#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#define min(a,b) ((a<b)?a:b)

//コードの短縮のため、マクロを使わせていただきます。
#define toS(x,y) std::to_string(x)+","+std::to_string(y)

extern int data[3][320];

#define  M  10000


std::string iTostock(int i){
  std::string stock = "";;
  if (i==0) stock = "A,";
  if (i==1) stock = "B,";
  if (i==2) stock = "C,";
  return stock;
}

struct answer{
  int value;
  int total;
  std::vector<int> stock;
  std::vector<int> buyT;
  std::string command;
};

int stock_value(std::vector<int>stock,int T){
  int ans=0;
  ans += stock[0]*data[0][T];
  ans += stock[1]*data[1][T];
  ans += stock[2]*data[2][T];
  return ans;
}



//Tをみこしたt~Tでの選択(各銘柄最大一回）
//buy keep sell のどれかを行う。各銘柄
answer gready(answer anst,int t,int T){
  answer ans;
  ans.stock = std::vector<int>(3);
  ans.buyT = std::vector<int>(3);
  std::vector <double> dif (3);
  ans.value = anst.value;
  ans.buyT = anst.buyT;
  ans.stock = anst.stock;
  for(int i=0;i<3;i++){
    dif[i] = data[i][T]-data[i][t];
    dif[i] /= data[i][t];//効率
  }
  //全キープを初期値
  //int best_total = stock_value(anst.stock,T);
  int argmax = std::distance(dif.begin(), std::max_element(dif.begin(), dif.end()));
  int argmin = std::distance(dif.begin(), std::min_element(dif.begin(), dif.end()));
  int argmean = 0*(0!=argmax&&0!=argmin) + 1*(1!=argmax&&1!=argmin) + 2*(2!=argmax&&2!=argmin);
  std::string com = "";
  std::vector<int>deel (3);
  std::fill(deel.begin(),deel.end(),0);
  if (anst.stock[argmin]>0&&anst.buyT[argmin]<t-9){
    deel[argmin] -= anst.stock[argmin];
    ans.value += anst.stock[argmin]*data[argmin][t];
    ans.stock[argmin] = 0;
  }
  if (anst.stock[argmean]>0&&anst.buyT[argmean]<t-9){
    deel[argmean] -= anst.stock[argmean];
    ans.value += anst.stock[argmean]*data[argmean][t];
    ans.stock[argmean] = 0;
  }
  deel[argmax] = min(M-ans.stock[argmax],ans.value/data[argmax][t]);
  if (deel[argmax]>0){
    ans.stock[argmax] += deel[argmax];
  }
  ans.value -= deel[argmax]*data[argmax][t];

  if (ans.value>data[argmean][t]&&dif[argmean]>0){
    deel[argmean] += min(M,ans.value/data[argmean][t]);
    ans.stock[argmean] += min(M,ans.value/data[argmean][t]);
    ans.value -= ans.stock[argmean]*data[argmean][t];
  }
  if (ans.value>data[argmin][t]&&dif[argmin]>0){
    deel[argmin] += min(M,ans.value/data[argmin][t]);
    ans.stock[argmin] += min(M,ans.value/data[argmin][t]);
    ans.value -= ans.stock[argmin]*data[argmin][t];
  }
  for(int i = 0;i<3;i++){
    if(deel[i]<0){
      com += "sell("+iTostock(i)+std::to_string(t)+","+std::to_string(-deel[i])+");";
    }
  }
  for(int i = 0;i<3;i++){
    if(deel[i]>0){
      com += "buy("+iTostock(i)+std::to_string(t)+","+std::to_string(deel[i])+");";
      ans.buyT[i] = t;
    }
  }
  ans.command = anst.command + com;
  ans.total = ans.value + stock_value(ans.stock,T);
  return ans;
}






int main(){
  answer ans[320];
  ans[0].value=10000;
  ans[0].total=10000;
  for (int i = 0;i<320;i++){
    ans[i].stock = std::vector<int>(3);
    ans[i].buyT = std::vector<int>(3);
    std::fill(ans[i].stock.begin(),ans[i].stock.end(),0);
    std::fill(ans[i].buyT.begin(),ans[i].buyT.end(),0);
  }
  answer temp;
  for (int T=1;T<320;T++){
    ans[T].total=0;
    for (int t=0;t<T;t++){
      temp = gready(ans[t],t,T);
      if (temp.total>ans[T].total){
        ans[T] = temp;
      }
    }
  }
  std::cout << ans[319].command << std::endl;
  std::cout << ans[319].total << std::endl;
}


