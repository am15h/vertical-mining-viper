#include "vtv.h"
#include <bits/stdc++.h>

using namespace std;

vtv::vtv() {}

vtv::vtv(const vector<bool> &bits) : m_bits(bits) {}

void vtv::push_back(bool bit) { m_bits.push_back(bit); }

size_t vtv::size() const { return m_bits.size(); }

bool vtv::operator[](size_t index) const { return m_bits[index]; }

void vtv::set(size_t index, bool val) { 
    m_bits[index] = val; 
}

vtv vtv::dot(vtv v2) {
    vtv res;
    for(int i = 0; i < m_bits.size(); i++){
        res.push_back(m_bits[i] && v2[i]);
    }
    return res;
}

int vtv::support() {
    int tot = 0;
    for (int a : m_bits) {
        tot += a;
    }
    return tot;
}

vector<int> vtv::compress() {
    int n = m_bits.size();
    if(n==0){
        cout<<"empty vector"<<endl;
        return {};
    }
    
    // taking W0 as 4 and W1 as 1
    const int W0 = 4, W1 = 1;
    const int r0 = 2;
    const int r1 = 0;

    vector<int> cmp;
    vector<int> cnts;
    int cnt = 1;

    for (int i = 1; i <=n; i++) {
        if ((i == n) || (m_bits[i] != m_bits[i - 1])) {
            cnts.push_back(cnt);
            cnt = 0;
        }
        cnt++;
    }

    bool j = (m_bits[0]==1);
    for(int i = 0; i<(int)cnts.size();i++){
        int quotient,reminder;
        if(j){
            quotient = cnts[i]/W1;
            reminder = cnts[i]%W1;
        }else{
            quotient = cnts[i]/W0;
            reminder = cnts[i]%W0;
        }
        for(int k = 0;k<quotient;k++){
            cmp.push_back(1);
        }
        cmp.push_back(0);
        //push binary representation of reminder
        string rem = "";
		if(j  && r1){
			rem = bitset<r1>(reminder).to_string();
		}
		if(!j && r0){
			rem = bitset<r0>(reminder).to_string();
		}
        for(auto c : rem) cmp.push_back(c - '0');
        j = !j;
    }

    cout<<"actual vtv : size = "<<n<<" and vector = ";
    for(auto i : m_bits)cout<<i;
    cout<<endl;
    cout<<"compressed vtv(snake) : size = "<<(int)cmp.size()<<" and vector = ";
    for(auto i : cmp)cout<<i;
    cout<<endl;

    return cmp;
}