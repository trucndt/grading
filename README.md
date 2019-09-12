# GRADING FOR PROJECT 1

This repo provides an automated grading program for Project 1 with 6 test cases

# Compilation
Require CMake >= 10.0

From the root folder:
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Execution
Syntax: from the root folder
```bash
$ ./build/grading <path/to/mix/root> [OPTIONS]
```
- `path/to/mix/root` is the relative or absolute path to the root folder of the Mix project
- `OPTIONS`: this field is optional, you can add the `--no-halt` to check the results when the parent dies before the children.

Example:
```bash
$ ./build/grading /home/user/Proj1/fletcher/proj1/
```

# Result
6 test cases will be run, the grading program will indicate the result (`PASSED`/`FAILED`) of each test. In specific, it will check the correctness of the student program's output. 

If the result is FAILED, it will output the errors which include:
1. Incorrect or missing vampire numbers.
2. The reported numbers have incorrect or missing fangs.
3. Not printing all fangs on a single line.

In addition, test 6 will show the running time together with the cpu utilization (`cpu time/real time * 100`). Below are some sample outputs:

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

Running TEST 6 with time: 1000 - 1000000
821.94user 1.65system 1:58.78elapsed 693%CPU (0avgtext+0avgdata 50368maxresident)k
0inputs+0outputs (0major+24777minor)pagefaults 0swaps
PASSED

PASSED 6/6 tests

```


```
===== Grading program for Project 1 ===== 

Compiling ...


Running TEST 1: 100 - 90000
FAILED
- Incorrect or missing vampire numbers.

Running TEST 2: 100000 - 200000
PASSED

Running TEST 3: 500000 - 1000000
FAILED
- Incorrect or missing vampire numbers.
- The reported numbers have incorrect or missing fangs.

Running TEST 4: 100000 - 105000
PASSED

Running TEST 5: 200000 - 205000
PASSED

Running TEST 6 with time: 1000 - 1000000
22.94user 0.09system 0:04.32elapsed 532%CPU (0avgtext+0avgdata 83744maxresident)k
0inputs+0outputs (0major+26634minor)pagefaults 0swaps
FAILED
- Incorrect or missing vampire numbers.

PASSED 3/6 tests
```

# Test cases
We test 6 ranges of number:
1. 100 - 90,000
2. 100,000 - 200,000
3. 500,000 - 1,000,000
4. 100,000 - 105,000
5. 200,000 - 205,000
6. 1,000 - 1,000,000

Test 4 and 5 are a bit tricky as they only have one or two vampire numbers.

# Notes
1. If a student fails all 6 tests, we should re-check their program manually, could be that the parent dies before children or incorrect output format. 
2. If it is the case that the parent dies before children, you can re-run the grading program with the option `--no-halt` to test the correctness of the result. For example:
```bash
$ ./build/grading /home/user/Proj1/fletcher/proj1/ --no-halt
```
3. If a student fails all tests except for test 4 and 5, it's very likely that the parent dies before children.
4. Some students implement an efficient algorithm which you may not find a good cpu utilization in test 6. You would want to read their report beforehand, if they claim a better ratio, you may try to re-run their program manually with a larger range of numbers.
5. An error of *"Incorrect or missing vampire numbers"* will lose all the points for items 6,7,8 in the grading criteria.