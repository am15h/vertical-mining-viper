#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<pair<ll, pair<ll, ll>>> set_of_itemsets(vector<ll> s_k) {


    
    // HashTable stores prefixes and their corresponding extList

    map<ll, vector<ll>> hash_table;

    // Create HashTable

    for (ll i = 0; i < s_k.size(); i++) {
        hash_table[s_k[i] / 10].push_back(s_k[i]%10);
    }

    vector<ll> rem;
    vector<ll> pnew;
    vector<ll> c_next;

    vector<pair<ll, pair<ll, ll>>> ret;

    // Here we generate new items for Ck+1 at each step

    for (auto i = hash_table.begin(); i != hash_table.end(); i++) {
        vector<ll> ext_list = i->second;
        ll p = i->first;

        for (ll j = 0; j < ext_list.size(); j++) {
            ll new_p = p * 10 + ext_list[j];
            pnew.push_back(new_p);

            // rem_list stores the last character all possible candidate itemsets

            vector<ll> rem_list;

            for (ll k = j + 1; k < ext_list.size(); k++)
                rem_list.push_back(ext_list[k]);

            // Generate all k-subsets of new_p

            vector<ll> all_subsets;
            ll size = log10(new_p);
            for (ll ind = 0; ind <= size; ind++) {
                ll adder = pow(10, ind);
                ll divider = adder * 10;

                all_subsets.push_back((new_p / divider) * adder +
                                      (new_p % adder));
            }

            for (ll k = 0; k < all_subsets.size(); k++) {
                vector<ll> current_ext_list = hash_table[all_subsets[k]];

                vector<ll> common(10000);
                vector<ll>::iterator it, st;

                sort(rem_list.begin(), rem_list.end());
                sort(current_ext_list.begin(), current_ext_list.end());

                it = set_intersection(rem_list.begin(), rem_list.end(),
                                      current_ext_list.begin(),
                                      current_ext_list.end(), common.begin());

                vector<ll> intersection;

                for (st = common.begin(); st != it; st++)
                    intersection.push_back(*st);

                rem_list = intersection;
            }

            rem = rem_list;

            // Generate new items for Ck+1

            for (ll k = 0; k < rem_list.size(); k++) {
                ll new_candidate = new_p * 10 + rem_list[k];
                c_next.push_back(new_candidate);
                ret.push_back({new_candidate, {new_p, rem_list[k]}});
            }
        }
    }

    return ret;
}