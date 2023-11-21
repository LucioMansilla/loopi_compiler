# expected =Identifier suma not declared; 
# expected =Did you mean: sum? at line 11
Program{
   int gauss_sum(int n){
       int sum = n*(n+1)/2;
       return sum;
   }
   int main(){
       int n = 100;
       int sum = gauss_sum(n);
       return suma;
   }
}
