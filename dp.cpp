#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#define min(a,b) ((a<b)?a:b)

//コードの短縮のため、マクロを使わせていただきます。
#define toS(x,y) std::to_string(x)+","+std::to_string(y)

extern int data[3][320];

#define  M  10000


std::string itocom (int st,int n,int buy,int sell){
  std::string stock = "";
  if (n==0)return stock;
  if (st==0) stock = "A,";
  if (st==1) stock = "B,";
  if (st==2) stock = "C,";
  std::string ans = "buy("+stock+toS(buy,n)+");sell("+stock+toS(sell,n)+");";
  return ans;
}

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
}

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
  for(int i=0;i<3;i++){
    dif[i] = data[T][i]-data[t][i];
    dif[i] /= data[t][i];//効率
  }
  //全キープを初期値
  //int best_total = stock_value(anst.stock,T);
  int argmax = std::distance(dif.begin(), std::max_element(dif.begin(), dif.end()));
  int argmin = std::distance(dif.begin(), std::min_element(dif.begin(), dif.end()));
  int mean = 0*(0!=argmax&&0!=argmin) + 2*(2!=argmax&&2!=argmin) + 2*(2!=argmax&&2!=argmin);

  if (




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
  for (int T=1;T<320;T++){
    ans[T].total=0;
    for (int t=0;t<T;t++){
      answer temp = gready(ans[t],t,T);
      if (temp.total>ans[T].total){
        ans[T] = temp;
      }
    }
  }
  std::cout << ans[319].command << std::endl;
}


