#include "item_set.h"

item_set::item_set() {}

item_set::item_set(vector<uint32_t> name, vtv bits)
    : m_name(name), m_bits(bits) {}

bool item_set::operator[](size_t index) const { return m_bits[index]; }

item_set item_set::dot(item_set set2) {
    vector<uint32_t> res_name = {m_name[0], set2.getName()[0]};
    vtv res_vtv = m_bits.dot(set2.getBits());

    return item_set(res_name, res_vtv);
}

double item_set::support() {
    return m_bits.support();
}