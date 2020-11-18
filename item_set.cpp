#include "item_set.h"
#include <bits/stdc++.h>
using namespace std;

item_set::item_set() {}

item_set::item_set(vector<uint32_t> name, vtv bits)
    : m_name(name), m_bits(bits) {}

bool item_set::operator[](size_t index) const { return m_bits[index]; }

item_set item_set::dot(item_set set2) {
    vector<uint32_t> res_name;
    res_name = m_name;
    cout << "A\n";
    res_name.push_back(set2.getName()[0]);
    cout << "B\n";
    vtv res_vtv = m_bits.dot(set2.getBits());
    cout << "C\n";
    return item_set(res_name, res_vtv);
}

double item_set::support() {
    return m_bits.support();
}

vector<uint32_t> item_set::getName(){
    return m_name;
}

vtv item_set::getBits(){
    return m_bits;
}