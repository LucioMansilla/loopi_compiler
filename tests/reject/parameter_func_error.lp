# expected =The type of the parameters do not match the formal in the function gauss_sum at line 11
Program{

    int gauss_sum(int n){
        int sum = n*(n+1)/2;
        return sum;
    }

    int main(){
        bool n = true;
        int sum = gauss_sum(n);
        return sum;
    }

}