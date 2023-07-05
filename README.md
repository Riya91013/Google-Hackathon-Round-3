# Google-Hackathon-Round-3
Programming language used: C++

How to run: Compile hackathon.cpp

Sample input:

4
net_e = A&B
net_f = C|D
net_g = ~net_f
Z = net_g^net_e
FAULT_AT = net_f
FAULT_TYPE = SA0

Input will also ask for the number of lines in circuit input only
as it is eual to 4 in the above example...

Solution to Round-3 task:

The Approach i am using here is checking all the possible test vectors. Here we have four inputs so it is feasible to check all 16 possibilities to find out what are the test vectors I can use to detect the mentioned fault in the input file. Here I have used C++ language. First I am analyzing the input , taking values from it that are in use later and storing them in the circuit vector. Then creating all the 16 vectors, and passing each vector through the test whether they are enough to identify the fault. That is do they give different values with and without fault, then only the test vector is enough to point out the stuck at fault. For checking I am comparing the output of two circuits, the one without any fault and one with fault.
