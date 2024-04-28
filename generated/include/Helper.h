//#ifndef OOP_HELPER_H
//#define OOP_HELPER_H
//
//
//class Helper {
//public:
//    void help();
//};
//
//
//
//#endif //OOP_HELPER_H

#include <functional>

struct PairHash {
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U>& p) const {
        // Combine the hash values of the pair's elements
        return std::hash<T>()(p.first) ^ std::hash<U>()(p.second);
    }
};