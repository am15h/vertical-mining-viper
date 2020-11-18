#pragma once

#include <stdint.h>

#include <string>
#include <vector>

#include "vtv.h"

using namespace std;

class item_set {
   private:
    vector<uint32_t> m_name;
    vtv m_bits;

   public:
    item_set();
    item_set(vector<uint32_t> name, vtv bits);
    double support();
    item_set dot(item_set set2);
    vector<uint32_t> getName();
    vtv getBits();
    bool operator[](size_t index) const;
    bool operator<(const item_set &rhs) const;
};