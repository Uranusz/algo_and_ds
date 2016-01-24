// =====================================================================================
//
//       Filename:  priority_queue.cc
//
//    Description:
//
//        Version:  1.0
//        Created:  01/24/2016 07:02:45 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Jiahao Zhu (JZ), uranus.superz@outlook.com
//   Organization:
//
// =====================================================================================

#include <iostream>
#include <vector>
#include <limits>
#include <assert.h>

using namespace std;


// =====================================================================================
//        Class:  PriorityQueue
//  Description:  implement using max-heap
// =====================================================================================
template < typename T >
class PriorityQueue {
    public:
        typedef unsigned int uint;

        // ====================  LIFECYCLE     =======================================
        PriorityQueue() : heap_size_(0) {}                            // constructor

        uint size() {
            return heap_size_;
        }

        T& operator[](int i) {
            return container_[i];
        }

        T const& operator[](int i) const {
            return container_[i];
        }

        void increase_key(int i, T const& key) {
            assert(key > container_[i]);
            container_[i] = key;

            while (i > 0 && container_[parent(i)] < container_[i]) {
                swap(container_[parent(i)], container_[i]);
                i = parent(i);
            }
        }

        void insert(T const& key) {
            container_.push_back(NegInfinity);
            heap_size_ ++;
            increase_key(heap_size_ - 1, key);
        }

        bool max(T& max) {
            if (size() <= 0)
                return false;

            max = container_[0];
            return true;
        }

        bool extract_max(T& max) {
            if (size() <= 0)
                return false;

            max = container_[0];
            heap_size_--;
            container_.erase(container_.begin());
            heapify(0);
            return true;
        }

        void heapify(int i) {
            int l = left(i);
            int r = right(i);
            int largest = -1;

            if (l < static_cast<int>(size()) && container_[i] < container_[l])
                largest = l;
            else
                largest = i;

            if (r < static_cast<int>(size()) && container_[r] > container_[largest])
                largest = r;

            if (largest != i) {
                swap(container_[i], container_[largest]);
                heapify(largest);
            }
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

        void print() {
            for (auto i : container_)
                cout << i << " ";

            cout << endl;
        }
    private:
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

    public:
        static const T NegInfinity;

    private:
        vector<T> container_;  // the container
        uint heap_size_;

}; // ----------  end of template class PriorityQueue  ----------

template<typename T> const T PriorityQueue<T>::NegInfinity =
    numeric_limits<T>::min();

#include	<stdlib.h>

// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:
// =====================================================================================
int
main(int argc, char* argv[]) {
    PriorityQueue<int> pq;
    cout << pq.size() << endl;

    for (int i = 0; i < 10; ++i)
        pq.insert(i);

    pq.print();

    // extract elements
    while (pq.size()) {
        int a = 0;
        pq.extract_max(a);
        cout << a << " ";
    }

    cout << endl;
    return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
