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
    vtv(const size_t size, bool init);
    vtv(const vector<bool> &bits);
    void push_back(bool bit);
    size_t size() const;
    bool operator[](size_t index) const;
    void set(size_t index, bool val);
    int support();
    vtv dot(vtv v2);
    vector<int> compress();
};