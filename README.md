# GRADING FOR PROJECT 1

This repo provides an automated grading program for Project 1 with 6 test cases

# Compilation
Require CMake >= 10.0
```bash
$ mkdir build
$ cd build
$ cmake ..
```

# Execution
Syntax:
```bash
$ ./build/grading <path/to/mix/root>
```
- `path/to/mix/root` is the relative or absolute path to the root folder of the Mix project

Example:
```bash
$ ./build/grading ../../Proj1/fletcher/proj1/
```

# Result
6 test cases will be run, the grading program will indicate the result (PASSED/FAILED) of each test. In specific, it will check the correctness of the student program's output. 

In addition, test 6 will show the running time so that we can compute the cpu usage. Below is a sample output

```
===== Grading program for Project 1 ===== 

Compiling ...
Generated proj1 app


Running TEST 1: 100 - 90000
PASSED

Running TEST 2: 100000 - 200000
PASSED

Running TEST 3: 500000 - 1000000
PASSED

Running TEST 4: 100000 - 105000
PASSED

Running TEST 5: 200000 - 205000
PASSED

Running TEST 6 with time: 1000 - 10000000
344.25user 0.58system 5:38.48elapsed 101%CPU (0avgtext+0avgdata 50640maxresident)k
0inputs+0outputs (0major+13642minor)pagefaults 0swaps
PASSED

PASSED 6/6 tests
```

# Test cases
We test 6 ranges of number:
1. 100 - 90,000
2. 100,000 - 200,000
3. 500,000 - 1,000,000
4. 100,000 - 105,000
5. 200,000 - 205,000
6. 1,000 - 1,000,000


# Grading policy
