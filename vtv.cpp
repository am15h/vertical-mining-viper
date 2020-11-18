#include "vtv.h"

using namespace std;

vtv::vtv() {}

vtv::vtv(const vector<bool> &bits) : m_bits(bits) {}

void vtv::push_back(bool bit) { 
    m_bits.push_back(bit); 
}

size_t vtv::size() const {
    return m_bits.size();
}

bool vtv::operator[]( size_t index ) const {
	return m_bits[index];
}