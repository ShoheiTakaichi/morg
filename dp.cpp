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

std::iTostock(int i){
  std::string stock = "";;
  if (st==0) stock = "A,";
  if (st==1) stock = "B,";
  if (st==2) stock = "C,";
  return stock;
}



struct answer{
  int value;
  int stock [3];
  int buyT [3];
  std::string command;
};//解とそれを実現する命令



int main(){
  answer ans[320];
  ans[0].value=10000;
  std::fill(ans[0].stock,ans[0].stock+3,0);
  std::fill(ans[0].buyT,ans[0].buyT+3,0);
  for (int T = 0;T<320;T++){
  }
  std::cout << ans[319].command << std::endl;
}


