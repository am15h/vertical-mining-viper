#pragma once

#include <bits/stdc++.h>
#include "item_set.h"
#include "vtv.h"

using namespace std;

class Viper {
   private:
    vector<item_set> individual_snakes;

    /// total_items: max integer in the HIL database
    vector<item_set> create_single_snakes(vector<vector<int>> database,
                                          int total_items, double min_support) {
        int no_of_rows = database.size();
        cout << "Creating single snakes..." << endl;

        vector<vector<bool>> matrix(no_of_rows);

        for (int i = 0; i < no_of_rows; i++) {
            /// Set all to zeros
            vector<bool> tmp(total_items, 0);
            matrix[i] = tmp;

            /// Set list indexes to true
            vector<int> h_list = database[i];
            for (int idx : h_list) {
                matrix[i][idx - 1] = 1;
            }
        }

        vector<item_set> f1;

        for (int col = 0; col < total_items; col++) {
            vtv item;
            for (int row = 0; row < no_of_rows; row++) {
                item.push_back(matrix[row][col]);
            }
            item_set is = item_set({(unsigned int)(col + 1)}, item);
            individual_snakes.push_back(is);
            if (item.support() >= min_support) {
                f1.push_back(is);
            }
        }

        return f1;
    };

   public:
    /// Input HIL database and minSupport
    void apply(vector<vector<int>> database, int total_items,
               double min_support);

    string itemize(long long num){
        // [1, 2, 3]
        string str = to_string(num);
        string fin = "{";
        for(int i = 0; i < str.size(); i++){
            fin.push_back(str[i]);
            fin+=", ";
        }
        fin.pop_back();
        fin.pop_back();
        fin.push_back('}');

        int max_size = 25;
        if(fin.size() < 25){
            int diff = max_size - fin.size();
            string s(diff, ' ');
            fin += s;
        }    
        return fin;
    }           
};