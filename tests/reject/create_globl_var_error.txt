# expected =Globl Error Decl in : global variable declared as x can only be initialized with a constant value at line 5
Program
{
int y = 5;    
int x = 10 + y;

int main()
{
    return x;
}

}