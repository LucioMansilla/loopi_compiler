# expected =Type Error in operation + : left-hand side has type int but right-hand side has type bool at line 7
Program
{

int main()
{
    int x = 10 + false;
    return x;
}

}