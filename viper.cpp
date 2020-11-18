#include "viper.h"

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

    vector<item_set> F2;

    for(int i = 0; i < f1_size; i++){
        for(int j = i+1; j < f1_size; j++){
            if(counter[i][j] >= min_support){
                item_set is = F1[i].dot(F1[j]);
                F2.push_back(is);
            }
        }
    }

    /// Subsequent Passes

}