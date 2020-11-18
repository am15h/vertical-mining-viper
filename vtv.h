#include <vector>

using namespace std;

/**
 * Snake
 *
 * vtv: Vertical Tid Vector
 *
 */

class vtv {
   private:
    vector<bool> m_bits;

   public:
    vtv();
    vtv(const vector<bool> &bits);
    void push_back(bool bit);
    size_t size() const;
    bool operator[](size_t index) const;
};