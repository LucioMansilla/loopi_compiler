# expected =Type Error in operation * : left-hand side has type int but right-hand side has type bool at line 8
# expected =Type Error in : variable declared as bool but initialized with a value of type int at line 9
Program
{

int main()
{
    int x = 1 * false;
    bool z = x;

    return x;
}

}