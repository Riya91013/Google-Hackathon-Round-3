#include<iostream>
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
#define ll long long int
#define f(i,a,b) for(ll i = a; i<b ; ++i)
#define fr(i,a,b) for(ll i = a; i>=b ; --i)
#define vl vector<ll>
#define all(x) x.begin(),x.end()
vector<int> test_vectors(16);
vector<string> test_vec(16);
map<char,int> value;
vector<vector<char>> layer_2;
vector<vector<char>> layer_1;
vector<vector<char>> layer_3;

// Function to convert number from decimal to Binary
string decToBinary(int n)
{
    string st = "";
    for (int i = 3; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
        st += '1';
        else
        st += '0';
    }
    return st;
}

/* function generating vector of all the possible test vectors for 4 inputs, i.e. all 16 possibilities, 
and their binary values. Binary values can be used to assign value to input nodes A,B,C,D easily.
*/
void test_vec_gen(){
    for(int i = 0; i<16; ++i){
        test_vectors[i] = i+1;
    }
    for(int i = 0; i<16; ++i){
        test_vec[i] = decToBinary(test_vectors[i]);
    }
}

/*fucntion used to return the value of after the operation is performed on two nodes,
nodes are passed as char, and the value in map with name of value[] stores the value at the particular node.
The operation perfornmed could be "&, |, ~, ^" any of these.
*/
int value_assign(char a, char b, char op){
    int ans;
    int p1 = value[a];
    int p2;
    p2 = value[b];
    if(op == '&'){
        ans = p1 & p2;
    }else 
    if(op == '|'){
        ans = p1 | p2;
    }else
    if(op == '~'){
        if(p1 == 0) ans = 1;
        else ans = 0;
    }else
    if(op == '^'){
        ans = p1^p2;
    }
    return ans;
}

/*Function to check whether the vector we are using is enough to test the particular fault mentioned.
Eg: If I have test vector <0,0,0,1> then the function will return true if the value with fault nd without fault
are different, so that we can test through the vector, or will return false if both of them will return same value.
*/
bool test_vector(char fault_at, int fault_type, int z_in){
    bool ans;
    bool ok = false;
    int replc ;
    if(fault_type == 0) replc = 0;
    else replc = 1;
    // all the values are updated acc to previous ones, except for the node with fault
    // ok = true condition used to update the value differently
    for(int i = 0; i<layer_1.size(); ++i){
        char op = layer_1[i][1];
        if(layer_1[i][0] == fault_at){
            ok = true;
        }
        if(ok == true){
            value[layer_1[i][0]] = replc;
            ok = false;
        }else{
            if(layer_1[i].size() == 4){
                value[layer_1[i][0]] = value_assign(layer_1[i][2], layer_1[i][3],layer_1[i][1]);
            }else
            if(layer_1[i].size() == 3){
                value[layer_1[i][0]] = value_assign(layer_1[i][2], ' ',layer_1[i][1]);
            }
        }
        // cout<<layer_1[i][0]<<" "<<value[layer_1[i][0]]<<endl;
    }
    for(int i = 0; i<layer_2.size(); ++i){
        char op = layer_2[i][1];
        if(layer_2[i][0] == fault_at){
            ok = true;
        }
        if(ok == true){
            value[layer_2[i][0]] = replc;
            ok = false;
        }else{
            if(layer_2[i].size() == 4){
                value[layer_2[i][0]] = value_assign(layer_2[i][2], layer_2[i][3],layer_2[i][1]);
            }else
            if(layer_2[i].size() == 3){
                value[layer_2[i][0]] = value_assign(layer_2[i][2], ' ',layer_2[i][1]);
            }
        }
        // cout<<layer_2[i][0]<<" "<<value[layer_2[i][0]]<<endl;
    }
    for(int i = 0; i<layer_3.size(); ++i){
        char op = layer_3[i][1];
        if(layer_3[i][0] == fault_at){
            ok = true;
        }
        if(ok == true){
            value[layer_3[i][0]] = replc;
            ok = false;
        }else{
            if(layer_3[i].size() == 4){
                value[layer_3[i][0]] = value_assign(layer_3[i][2], layer_3[i][3],layer_3[i][1]);
            }else
            if(layer_3[i].size() == 3){
                value[layer_3[i][0]] = value_assign(layer_3[i][2], ' ',layer_3[i][1]);
            }
        }
        // cout<<layer_3[i][0]<<" "<<value[layer_3[i][0]]<<endl;
    }
    // To print the Z(output) with fault, remove the comment from the below line
    // cout<<"Z(with fault): "<<value['Z']<<endl;

    if(z_in == value['Z']){
        ans = false;
    }else{
        ans = true;
    }
    return ans;
}

/* Function for updating all the values of nodes via map, intially all the values of 
nodes are set to -1, then three layers are formed for circuit, layer_1 contains the nodes directly 
connected to input nodes that are A,B,C,D, layer_2 contains all the nodes connected directly to 
layer_1 nodes, and then the final layer_3 contains our output node Z
Fr eg:  (Input)
4
net_e = A&B
net_f = C|D
net_g = ~net_f
Z = net_g^net_e
FAULT_AT = net_f
FAULT_TYPE = SA0

Here :
layer_1 : e,f
layer_2 : g
layer_3 : Z
*/
void solve(char fault_at, int fault_type, vector<vector<char>> circuit,int n)
{
    for(int i = 0; i<n ; ++i){
        if(circuit[i].size() == 4){
            value[circuit[i][0]] = -1;
            value[circuit[i][2]] = -1;
            value[circuit[i][3]] = -1;
        }else
        if(circuit[i].size() == 3){
            value[circuit[i][0]] = -1;
            value[circuit[i][2]] = -1;
        }
    }
    
    for(int i = 0; i<n ; ++i){
        if(circuit[i][0] != 'Z'){
            if(circuit[i][2] == 'A' || circuit[i][2] == 'B' || circuit[i][2] == 'C' || circuit[i][2] == 'D'){
                // vector<char>temp;
                layer_1.push_back(circuit[i]);
            }else{
                layer_2.push_back(circuit[i]);
            }
        }else{
            layer_3.push_back(circuit[i]);
        }
    }

    // loop running 16 times for checking all the possible test cases for four inputs
    // in the loop first all the values of all nodes are updated
    // then test_vector function is called to check whether the vector we are having is 
    // sufficient to check for that fault, if it is then true is returned and printed out, else False is returned 
    // and False is printed out
    for(int i = 0; i<16; ++i){
        string st = test_vec[i];
        // st is the string having each characted has the value A,B,C,D
        // will take respectively
        // to print the string used remove the comment from the below line
        // cout<<"string: "<<st<<endl;
        value['A'] = int(st[0]) - 48;
        value['B'] = int(st[1]) - 48;
        value['C'] = int(st[2]) - 48;
        value['D'] = int(st[3]) - 48;
        
        // all the layers values are updated for each test vector
        for(int i = 0; i<layer_1.size(); ++i){
            char op = layer_1[i][1];
            // here the size 4 and 3 differentiate the node having &, |, ^ with the node having just ~
            if(layer_1[i].size() == 4){
                value[layer_1[i][0]] = value_assign(layer_1[i][2], layer_1[i][3],layer_1[i][1]);
            }else
            if(layer_1[i].size() == 3){
                value[layer_1[i][0]] = value_assign(layer_1[i][2], ' ',layer_1[i][1]);
            }
        }
        for(int i = 0; i<layer_2.size(); ++i){
            char op = layer_2[i][1];
            if(layer_2[i].size() == 4){
                value[layer_2[i][0]] = value_assign(layer_2[i][2], layer_2[i][3],layer_2[i][1]);
            }else
            if(layer_2[i].size() == 3){
                value[layer_2[i][0]] = value_assign(layer_2[i][2], ' ',layer_2[i][1]);
            }
        }
        for(int i = 0; i<layer_3.size(); ++i){
            char op = layer_3[i][1];
            if(layer_3[i].size() == 4){
                value[layer_3[i][0]] = value_assign(layer_3[i][2], layer_3[i][3],layer_3[i][1]);
            }else
            if(layer_3[i].size() == 3){
                value[layer_3[i][0]] = value_assign(layer_3[i][2], ' ',layer_3[i][1]);
            }
        }
        // To print the Z(ouput) without any fault remove comment from the below line
        // cout<<"Z(without fault): "<<value['Z']<<endl;

        // ans store whether the test vector from the 16 vectors is enough to check the fault mentioned.
        bool ans = test_vector(fault_at,fault_type,value['Z']);
        if(ans == true){
            cout<<"[A,B,C,D] = [";
            for(int i = 0; i<st.length(); ++i){
                cout<<st[i];
                if(i != st.length()- 1){
                    cout<<" ";
                }
            }
            cout<<"],Z = ";
            cout<<value['Z']<<endl;
            // cout<<endl;
            break;
        }

        // To print the ans remove the comments on below code
        // if(ans == true){
        //     cout<<"True"<<endl;
        // }else{
        //     cout<<"False"<<endl;
        // }
    }

} 

/* Main function from where the code start
*/
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; // the number of lines in input
    cout<<"Input the number of lines for input file: "<<endl;
    cin>>n;
    
    // vector to store all the string seprerated with space in the input of circuit
    // string splitting used
    vector<vector<string>> input(n);
    for(int i = 0; i<n ; ++i){
        string S, T;
  
        getline(cin, S);

        while (S.length() == 0)
            getline(cin, S);
    
        stringstream X(S);
    
        while (getline(X, T, ' ')) {
            input[i].push_back(T);
        }
    }

    int n2 = 2;
    // vector to store all the string seprerated with space in the input of faults
    vector<vector<string>> faults(n2);
    for(ll i = 0; i<n2 ; ++i){
        string S, T;
        getline(cin, S);
        while (S.length() == 0)
            getline(cin, S);
    
        stringstream X(S);
        while (getline(X, T, ' ')) {
            faults[i].push_back(T);
        }
    }
    char fault_at;
    int fault_type;
    for(int i = 0; i<n2; ++i){
        string st = faults[i][2];
        if(st.length() == 1){
            fault_at = st[0];
        }else
        if(st.length() == 5){
            fault_at = st[st.length()-1];
        }else
        if(st.length() == 3){
            fault_type = int(st[st.length()-1]) - 48;
        }
    }
    // to print the node where faults is and the fault type remove the comment from below code
    // cout<<"FAULT AT: "<<fault_at<<endl;
    // cout<<"FAULT TYPE: "<<fault_type<<endl;
    
    /*Final vectors to store all the characters in the input, i.e.
    nodes and the operations to be performed
    */
    vector<vector<char>> circuit(n);
    for(int i = 0; i<n ; ++i){
        for(int j = 0; j< input[i].size(); ++j){
            if(j == 0){
                if(input[i][j].length() == 5){
                    string st = input[i][j];
                    circuit[i].push_back(st[st.length()-1]);
                }else
                {
                    circuit[i].push_back(input[i][j][0]);
                }
            }else
            if(j == 1){
                continue;
            }else{
                if(input[i][j].length() == 3){
                    string st = input[i][j];
                    circuit[i].push_back(st[1]);
                    circuit[i].push_back(st[0]);
                    circuit[i].push_back(st[2]);
                }else
                if(input[i][j].length() == 6)
                {
                    string st = input[i][j];
                    circuit[i].push_back(st[0]);
                    circuit[i].push_back(st[st.length()-1]);
                }else{
                    string st = input[i][j];
                    circuit[i].push_back(st[5]);
                    circuit[i].push_back(st[4]);                                     
                    circuit[i].push_back(st[st.length()-1]);
                }
            }
        }
    }
    // for(auto it: circuit){
    //     for(auto ir: it){
    //         cout<<ir<<" ";
    //     }
    //     cout<<endl;
    // }
    test_vec_gen();
    solve(fault_at,fault_type,circuit,n);
    
    return 0;
}