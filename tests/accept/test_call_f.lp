
# expected = 25
Program {

int sum(int a, int b){
    if(a<1) then {
        return 0;
    }
    return sum(a-1, b) + b;
}


int main(){

    bool x2 = true && true;
    int y = 5 - 1;
    int x = 1;
    int z = sum(5,5);
    return z;
}

}