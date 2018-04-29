OS - running in VirtualBox(Windows 10 and Linux Ubuntu 17.10.1)
Windows(Debug)

Time taken by function: 1768 microseconds (1,000 μs	0.001 s) -> 0.0017 секунды
T1+1@50 T7-1@50
T1+2@60 T4-2@60
T1+1@60 T7-1@60

T7-1@60 T2-10@70 T5-3@70 T6-20@80  T1+5@30 T3+1@40 T8+10@90

Input request data:
Windows(Release)
Time taken by function: 54 microseconds 
/fp:fast  /Og best result 40-41 microseconds

g++ -std=c++1z -pipe -Wall -I . main.cpp matchengine.hpp -m64 -Ofast -flto -march=native -funroll-loops -o matchengine
clang++-6.0 -std=c++1z -pipe -Wall -I . main.cpp -m64 -Ofast -flto -march=native -funroll-loops -o matchengine

Linux
./matchengine
Time taken by function: 21 - 22(g++ compiler) microseconds.
(clang++-5.0 - 24 microseconds)
(clang++-6.0 - 20 microseconds)

T1+1@50 T7-1@50
T1+2@60 T4-2@60
T1+1@60 T7-1@60

T7-1@60 T2-10@70 T5-3@70 T6-20@80  T1+5@30 T3+1@40 T8+10@90
Input request data:

54/22 = 2.454545 ~2.5 Desktop Linux faster than Desktop Windows everage ~ [2 - 2.5] times faster.
40/([20,21,22]) ~ 1.8 ~ 2

Linux faster than Windows at least 2 times

1,000 μs	0.001 s
2,500 μs	0.0025 s
5,000 μs	0.005 s
7,500 μs	0.0075 s
10,000 μs	0.01 s
25,000 μs	0.025 s
50,000 μs	0.05 s
75,000 μs	0.075 s
100,000 μs	0.1 s
250,000 μs	0.25 s
500,000 μs	0.5 s
750,000 μs	0.75 s
1,000,000 μs	1 s
2,500,000 μs	2.5 s
5,000,000 μs	5 s
7,500,000 μs	7.5 s
10,000,000 μs	10 s
25,000,000 μs	25 s
50,000,000 μs	50 s
75,000,000 μs	75 s
100,000,000 μs	100 s
250,000,000 μs	250 s
500,000,000 μs	500 s
750,000,000 μs	750 s
1,000,000,000 μs	1,000 s
2,500,000,000 μs	2,500 s
5,000,000,000 μs	5,000 s
10,000,000,000 μs	10,000 s
