HW Programming Assignment 1 - Matrix Multiplication
CS18BTECH11042
Note: Please refer to the program comments for details and check build #22 on jenkins.

List of files submitted:
* matmul.c
* Report.pdf
* README.txt


Compilation:
Please compile the file matmul.c using flags pthread and lm as follows:
gcc matmul.c -pthread -lm


Running:
Run the ./a.out (or the executable file produced) providing the required arguments:
* ar (No. of rows in matrix A)
* ac (No. of columns in matrix A)
* br (No. of rows in matrix B)
* bc (No. of columns in matrix B)
and the optional argument interactive if you want to provide the matrices A and B.


Non-Interactive:
./a.out --ar 100 --ac 1001 --br 1001 --bc 1000
Interactive:
./a.out --ar 3 --ac 3 --br 3 --bc 3 --interactive


Sample Output:
Non-Interactive:
For /a.out --ar 100 --ac 100 --br 100 --bc 100
Time taken for single threaded: 16622 us
Time taken for multi process: 4588 us
Time taken for multi threaded: 4126 us
Speedup for multi process : 3.62 x
Speedup for multi threaded : 4.03 x


For ./a.out --ar 100 --ac 1001 --br 1001 --bc 1000
Time taken for single threaded: 649486 us
Time taken for multi process: 148810 us
Time taken for multi threaded: 138682 us
Speedup for multi process : 4.36 x
Speedup for multi threaded : 4.68 x


 For ./a.out --ar 777 --ac 777 --br 777 --bc 777
Time taken for single threaded: 2113488 us
Time taken for multi process: 618365 us
Time taken for multi threaded: 606346 us
Speedup for multi process : 3.42 x
Speedup for multi threaded : 3.49 x


For ./a.out --ar 100 --ac 1001 --br 1001 --bc 1
Time taken for single threaded: 2232 us
Time taken for multi process: 962 us
Time taken for multi threaded: 1175 us
Speedup for multi process : 2.32 x
Speedup for multi threaded : 1.90 x


For ./a.out --ar 3 --ac 4 --br 4 --bc 5
Time taken for single threaded: 2 us
Time taken for multi process: 1465 us
Time taken for multi threaded: 143 us
Speedup for multi process : 0.00 x
Speedup for multi threaded : 0.01 x


For ./a.out --ar 1 --ac 1001 --br 1001 --bc 1
Time taken for single threaded: 18 us
Time taken for multi process: 913 us
Time taken for multi threaded: 135 us
Speedup for multi process : 0.02 x
Speedup for multi threaded : 0.13 x


For ./a.out --ar 3 --ac 4 --br 5 --bc 5
Matrix multiplication not possible 
Interactive:


For ./a.out --ar 2 --ac 1 --br 1 --bc 3 --interactive
Enter A:
1
1
Enter B:
1 1 1
Result:
1 1 1
1 1 1
Enter A:
1
1  
Enter B:
1 1 1
Result:
1 1 1
1 1 1
Enter A:
1
1
Enter B:
1 1 1
Result:
1 1 1
1 1 1
Time taken for single threaded: 1 us
Time taken for multi process: 2092 us
Time taken for multi threaded: 316 us
Speedup for multi process : 0.00 x
Speedup for multi threaded : 0.00 x


For ./a.out --ar 3 --ac 3 --br 3 --bc 3 --interactive
Enter A:
2 3 4
4 3 4
5 3 7
Enter B:
1 0 0
0 1 0
0 0 1
Result:
2 3 4
4 3 4
5 3 7
Enter A:
1 0 0
0 1 0
0 0 1
Enter B:
2 3 4
4 3 4
5 3 7
Result:
2 3 4
4 3 4
5 3 7
Enter A:
1 0 0
0 1 0
0 0 1
Enter B:
1 0 0
0 1 0
0 0 1
Result:
1 0 0
0 1 0
0 0 1
Time taken for single threaded: 2 us
Time taken for multi process: 1826 us
Time taken for multi threaded: 255 us
Speedup for multi process : 0.00 x
Speedup for multi threaded : 0.01 x


 For ./a.out --ar 8 --ac 1 --br 1 --bc 1 --interactive
Enter A:
1
1
1
1
1
1
1
1
Enter B:
1
Result:
1
1
1
1
1
1
1
1
Enter A:
1
1
1
1
1
1
1
1
Enter B:
1
Result:
1
1
1
1
1
1
1
1
Enter A:
1
1
1
1
1
1
1
1
Enter B:
1
Result:
1
1
1
1
1
1
1
1
Time taken for single threaded: 1 us
Time taken for multi process: 1153 us
Time taken for multi threaded: 188 us
Speedup for multi process : 0.00 x
Speedup for multi threaded : 0.01 x
