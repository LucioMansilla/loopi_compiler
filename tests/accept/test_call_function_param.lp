# expected = 6
Program
{

int f(int x,int y){
    int res = 10;
    return res;

}

int main(){
    int i = 1;
    int res = 1;
    int n = 4;
    while (i < n){
       res = res * i;
       i = i + 1;
    }

    return res;
}

} 
