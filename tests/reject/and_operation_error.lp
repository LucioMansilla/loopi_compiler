# expected =Type Error in operation && : left-hand side has type int but right-hand side has type bool at line 8
# expected =Type Error in : variable declared as int but initialized with a value of type bool at line 8
Program
{

int main()
{
    int x = 1 && false;
    return x;
}

}