#include <bits/stdc++.h>
#include "viper.h"
using namespace std;
#define dbg(x) cout<<'>'<< #x <<':'<< x <<endl;


int main(int argc, char const *argv[]) {

    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    if (argc < 2) {
        cerr << "Usage : " << argv[0] << " " << "<input-file>" << endl;
        exit(1);
    }
    ifstream myfile (argv[1]);
    if (!myfile.is_open()) {
        cerr << "Unable to open file : " << argv[1];
        exit(1);
    }
    
    int rows, cols;
    double min_support;
    myfile >> rows >> cols >> min_support;
    vector<vector<int>> database(rows);
    Viper viper;
    for(int i = 0; i < rows; ++i) {
        int tid, num_vals, val;
        myfile >> tid >> num_vals;
        
        for(int j = 0; j < num_vals; ++j) {
            myfile >> val;
        
            database[i].push_back(val);
            
        }

        
    }

    // cout << "Database size: " << database.size() << endl;
    // dbg(database.size())

    viper.apply(database, cols, min_support);
    
    return 0;
}

