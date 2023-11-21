# expected = 9
Program
{
int x = 5;

int increment(int a){
    return a+1;
}     

int multiply(int a, int b){
    a = increment(a);
    return a * b;
}

int main(){
    int y = 3;
    x = multiply(2, y);
    return x;
}

} 