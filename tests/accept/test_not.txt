# expected =10
Program
{

int print(int x, int type) extern;

int main(){
    int x = 4;
    bool n = false;
    print(x,0);
    if (!n) then{
       x = 10;
    }
    return x;
}


} 
