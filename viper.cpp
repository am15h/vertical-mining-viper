#include "viper.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<pair<ll, pair<ll, ll>>> set_of_itemsets(vector<ll> s_k);

void Viper::apply(vector<vector<int>> database, int total_items,
                  double min_support) {
    int no_of_rows = database.size();
    
    cout << "Applying VIPER procedure..." << endl;

    /// Pass 1

    /// Create snakes for individual items
    vector<item_set> F1 =
        create_single_snakes(database, total_items, min_support);

    cout << "F1 item_set created, size: " << F1.size() << endl;

    /// Pass 2
    int f1_size = F1.size();

    /// counter 2-D array:
    /// counter[i][j] stores
    /// num of occurances of item "i" with item "j"
    int** counter = new int*[f1_size];
    for (int i = 0; i < f1_size; i++) {
        counter[i] = new int[f1_size]{0};
    }

    for (int r = 0; r < no_of_rows; r++) {
        for (int i = 0; i < f1_size; i++) {
            for (int j = i + 1; j < f1_size; j++) {
                if (F1[i][r] == 1 && F1[j][r] == 1) {
                    counter[i][j]++;
                }
            }
        }
    }

    map<ll, item_set> F2;
    map<ll, item_set> C2;
    vector<ll> prev_candidates;
    for (int i = 0; i < f1_size; i++) {
        for (int j = i + 1; j < f1_size; j++) {
            if (counter[i][j] >= min_support) {
                item_set is = F1[i].dot(F1[j]);
                F2[i * 10 + j] = is;
                prev_candidates.push_back(i * 10 + j);
            }
            C2[i * 10 + j] = F1[i].dot(F1[j]);
        }
    }

    cout << "F2 item_set created, size: " << F2.size() << endl;

    // delete counter array
    for (int i = 0; i < f1_size; i++) {
        delete[] counter[i];
    }
    delete[] counter;

    /// Subsequent Passes
    vector<map<ll, item_set>> FK(1000);
    vector<map<ll, item_set>> CK(1000);
    CK[0] = C2;
    FK[0] = F2;
    // Start running FANGS algorithm
    for (int i = 3; i < 10; i++) {
        // get candidates at level i from FORC algorithm
        vector<pair<ll, pair<ll, ll>>> candidates = set_of_itemsets(prev_candidates);
        
        vector<ll> temp;
        // generate support for all chosen candidates
        for (int idx = 0; idx < candidates.size(); ++idx) {
    
            int remlist_K = candidates[idx].second.second;
            int new_p = candidates[idx].second.first;
            int new_candidate = candidates[idx].first;
            
            item_set is = CK[i-3][new_p].dot(F1[remlist_K]);
            
            CK[i-2][new_candidate] = is;
            // If support is more than minimum support, insert into frequent candidates
            if (is.support() >= min_support) {
                FK[i-2][new_candidate] = is;
                temp.push_back(new_candidate);
            }
        }
        printf("F%d item_set created, size: %d\n", i, FK[i-2].size());
        // If no new frequent candidates found, exit generation
        if (temp.size() == 0) {
            break;
        }
        prev_candidates = temp;
    }

    printf("\n Printing Frequent-K item-sets\n");

    // Print out the frequent itemsets as result
    for(int idx = 0; idx < 10; ++idx) {
        
        for(auto j = FK[idx].begin() ; j != FK[idx].end() ; j++) {
            std::cout << "Itemset: " << itemize(j -> first) << "    Support: " << (j -> second).support() << std::endl;
        }
    }
}


