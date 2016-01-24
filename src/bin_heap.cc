// =====================================================================================
//
//       Filename:  min_bin_heap.cc
//
//    Description:  min-heap
//
//        Version:  1.0
//        Created:  01/24/2016 01:13:26 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Jiahao Zhu (JZ), uranus.superz@outlook.com
//   Organization:
//
// =====================================================================================

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

enum { NIL = -1 };

//-----------------------------------------------------------------------------
//  below functions work for indexes start from 1, not 0
//-----------------------------------------------------------------------------
inline int parent_(int i) {
    assert(i > 0);
    return i / 2;
}

inline int left_(int i) {
    assert(i > 0);
    return 2 * i;
}

inline int right_(int i) {
    assert(i > 0);
    return 2 * i + 1;
}

//-----------------------------------------------------------------------------
//  below functions are wrappers working for indexes start from 0
//-----------------------------------------------------------------------------
inline int parent(int i) {
    return parent_(i + 1) - 1;
}

inline int left(int i) {
    return left_(i + 1) - 1;
}

inline int right(int i) {
    return right_(i + 1) - 1;
}

//-----------------------------------------------------------------------------
//  Functors as policy class
//-----------------------------------------------------------------------------
template <typename T>
struct LessThan {
    bool operator()(T const& a, T const& b) {
        return a < b;
    }
};

template <typename T>
struct GreateThan {
    bool operator()(T const& a, T const& b) {
        return a > b;
    }
};

// min-heap or max-heap
enum {MIN_HEAP, MAX_HEAP};

//-----------------------------------------------------------------------------
//  Heap Type traits
//-----------------------------------------------------------------------------
template <typename T, int HEAP_TYPE = MIN_HEAP>
struct HTraits {
    typedef LessThan<T> Comparator;
};

// partial specialization
template <typename T>
struct HTraits<T, MAX_HEAP> {
    typedef GreateThan<T> Comparator;
};

template <typename T, int HEAP_TYPE = MIN_HEAP, typename Traits = HTraits<T, HEAP_TYPE>>
void heapify(vector<T>& h, int i) {
    typedef typename Traits::Comparator Comparator;
    int l = left(i);
    int r = right(i);
    int float_down_candidate = NIL;
    Comparator comparator;

    if (l < static_cast<int>(h.size()) && comparator(h[l], h[i]))
        float_down_candidate = l;
    else
        float_down_candidate = i;

    if (r < static_cast<int>(h.size()) && comparator(h[r], h[float_down_candidate]))
        float_down_candidate = r;

    if (float_down_candidate != i) {
        swap(h[i], h[float_down_candidate]);
        heapify(h, float_down_candidate);
    }
}

template <typename T, int HEAP_TYPE = MIN_HEAP, typename Traits = HTraits<T, HEAP_TYPE>>
void build_heap(vector<T>& h) {
    for (int i = static_cast<int>(h.size()) / 2; i >= 0; --i)
        heapify<T, HEAP_TYPE, Traits>(h, i);
}

//-----------------------------------------------------------------------------
//  use a min-heap to sort given array
//-----------------------------------------------------------------------------
template <typename T>
void heap_sort(vector<T>& in, vector<T>& out) {
    out.clear();
    build_heap<T, MIN_HEAP>(in);

    while (in.size() > 0) {
        swap(in.front(), in.back());
        out.push_back(in.back());
        in.pop_back();
        heapify<T, MIN_HEAP>(in, 0);
    }
}

//-----------------------------------------------------------------------------
//  find k big elements
//-----------------------------------------------------------------------------
template <typename T>
vector<T> findK(vector<T>& in, int k) {
    vector<int> out(in.begin(), in.begin() + k);
    build_heap<T, MIN_HEAP>(out);

    for (auto it = in.begin() + k + 1; it != in.end(); ++it) {
        if (*it > out[0]) {
            out[0] = *it;
            heapify<T, MIN_HEAP>(out, 0);
        }
    }

    return out;
}

#include	<stdlib.h>

// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:
// =====================================================================================
int
main(int argc, char* argv[]) {
    vector<int> heap({5, 4, 3, 2, 1, 110, 12, 15, 10, 200});
    vector<int> out;
    heap_sort(heap, out);

    for (auto i : out)
        cout << i << " ";

    cout << endl;
    vector<int> out1 = findK(out, 3);

    for (auto i : out1)
        cout << i << " ";

    cout << endl;
    return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
