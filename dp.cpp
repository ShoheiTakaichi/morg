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

struct answer{
  int value;
  int stock [3];
  int buyT [3];
  std::string command;
};//解とそれを実現する命令

void copy_answer(answer* a,answer* b){
  (*b).value = (*a).value;
  (*b).command = (*a).command;
  for (int i=0;i<3;i++){
    (*b).stock[i]=(*a).stock[i];
    (*b).buyT[i]=(*a).buyT[i];
  }
}



int total_value(answer a,int t){
  int ans = a.value;
  for(int i=0;i<3;i++){
    ans += a.stock[i] * data[i][t];
  }
  return ans;
}



int main(){
  answer ans[320];
  ans[0].value=10000;
  std::fill(ans[0].stock,ans[0].stock+3,0);
  std::fill(ans[0].buyT,ans[0].buyT+3,0);
  for (int T = 0;T<320;T++){
    if (T<10){
      ans[T].value=10000;
      std::fill(ans[T].stock,ans[T].stock+3,0);
      std::fill(ans[T].buyT,ans[T].buyT+3,0);
    }else{
      copy_answer(&ans[T-1],&ans[T]);
      for (int t=0;t<T;t++){
        std::vector<int> dif(3);
        for(int i=0;i<3;i++){
          dif[i] = data[i][T]-data[i][t];
        }
        int temp_total = total_value(ans[t],T);
        int temp_value = ans[t].value;
        for(int i=0;i<3;i++){
          if(dif[i]<0&&ans[t].buyT[i]<t-9){
            temp_value += (ans[t]).stock[i]*data[i][t];
            temp_total += (ans[t]).stock[i]*dif[i];
          }
        }
        if(total_value(ans[T],T)< )




      }

    }
  }
  std::cout << ans[319].command;
}



















