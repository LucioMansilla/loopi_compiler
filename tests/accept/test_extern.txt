# expected = 6
Program{

    void print_int(int x) extern;

    int mul(int a, int b){
        return a * b;
    }
    
    int main(){
        int x = mul(2, 3);
        print_int(x);
        return x;
    }
}