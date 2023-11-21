# expected = 144
Program {

    bool compare_fib_result(int num, int result) extern;
    void print_int(int x) extern;
    
    int fib(int n) {
        if (n == 0) then {
            return 0;
        }
        
        if (n == 1) then {
            return 1;
        }
        return fib(n - 1) + fib(n - 2);
    }

      void main() {
        int i = 0;
        bool is_fib = true;
        
        while(i < 13 && is_fib) {
            
            int fib_i = fib(i);

            if (compare_fib_result(i,fib_i)) then {
                print_int(fib_i);
            } else {
                is_fib = false;
            }
            i = i + 1;
        }  
        return;
    }
}
