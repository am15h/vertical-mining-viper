#include "viper.h"

#include <unordered_map>

typedef long long ll;

vector<pair<ll, pair<ll, ll>>> set_of_itemsets(vector<ll> s_k);

void Viper::apply(vector<vector<int>> database, int total_items,
                  double min_support) {
    int no_of_rows = database.size();

    /// Pass 1

    /// Create snakes for individual items
    vector<item_set> F1 =
        create_single_snakes(database, total_items, min_support);

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

    unordered_map<ll, item_set> F2;

    for (int i = 0; i < f1_size; i++) {
        for (int j = i + 1; j < f1_size; j++) {
            if (counter[i][j] >= min_support) {
                item_set is = F1[i].dot(F1[j]);
                F2[i * 10 + j] = is;
            }
        }
    }

    // delete counter array
    for (int i = 0; i < f1_size; i++) {
        delete[] counter[i];
    }
    delete[] counter;

    /// Subsequent Passes
    vector<unordered_map<ll, item_set>> FK;
    FK.push_back(F1);
    FK.push_back(F2);
    for (int i = 3; i < 10; i++) {
        vector<pair<ll, <pair<ll, ll>>>> candidates = set_of_itemsets();
        for (int idx = 0; idx < candidates.size(); ++i) {
            int remlist_K = candidates[idx].first;
            int new_p = candidates[idx].second.first;
            int new_candidate = candidates[idx].second.second;
            item_set is = FK[i-1][new_p].dot(F1[0])
            if (is.support() > min_support) {
                FK[i].push_back({new_candidate, is})
            }
        }
    }
}