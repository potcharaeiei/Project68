1. fitness.c  gcc fitness.c -o fitness 
              .\fitness
2. test_fitness.c  gcc fitness.c test_e2e.c -o test_e2e
                   ./test_e2e
3. test_e2e.c  gcc -std=c11 -Wall -Wextra test_e2e.c -o test_e2e
              .\test_e2e
