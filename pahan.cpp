#include <iostream>
#include "random"
#include<vector>
#include<cmath>
#include<chrono>
#include "limits.h"
using namespace std;

class merge_sort{
public:
    void executer(vector<int>& a){
        a = split(a, 0, a.size()-1);
    }
private:
    vector<int> split(vector<int>& a, int l, int r){
        if(r - l < 1){
            return  {a[l]};
        }
        auto l_task = split(a, l, (l + r)/2);
        auto r_task = split(a, (l + r)/2+1, r);
        return merge(l_task, r_task);
    }
    vector<int> merge(vector<int>& b, vector<int>& c){
        vector<int> ans(b.size() + c.size(), 0);
        int i1 = 0, i2 = 0, i3 = 0;
        while(i1 < b.size() && i2 < c.size()){
            if(b[i1] < c[i2]){
                ans[i3++] = b[i1++];
            }
            else{
                ans[i3++] = c[i2++];
            }
        }
        while(i1 < b.size()){
            ans[i3++] = b[i1++];
        }

        while(i2 < c.size()){
            ans[i3++] = c[i2++];
        }
        return ans;
    }
};
template <class T>
class injection_sort{
public:
    void injection( vector<T>& a) {
        for (int i = 0; i < a.size(); i++) {
            for (int j = i; a[j] < a[j - 1] && j > 0; j--) {
                swap(a[j], a[j - 1]);
            }
        }
    }
};
template <class T>
class bin_injection_sort{
public:
    void bin_injection(vector<T>& a){
        int i; int  j;
        T selected;
        int loc;
        for (i = 1; i < a.size(); ++i)
        {
            j = i - 1;
            selected = a[i];
            loc = binarySearch(a, selected, 0, j);
            while (j >= loc)
            {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = selected;
        }
    }
private:
    int binarySearch(vector<T> &a, T item,
                    int low, int high)
    {
        if (high <= low)
            return (item > a[low]) ?
                   (low + 1) : low;

        int mid = (low + high) / 2;

        if (item == a[mid])
            return mid + 1;

        if (item > a[mid])
            return binarySearch(a, item,
                                mid + 1, high);
        return binarySearch(a, item, low,
                            mid - 1);
    }
};
class q_sort{
private:
     random_device rd;
     mt19937 gen;
public:
    q_sort(): gen(rd()){}
    void q(vector<int>& a, int l, int r){
        if(l >= r){
            return;
        }
         uniform_int_distribution<int> distrib(l, r);
        int op = distrib(gen);
        int i = l;
        int j = r;
        int op_1 = a[op];
        while(i <= j){
            while(a[i] < op_1){
                i++;
            }
            while(a[j] > op_1){
                j--;
            }
            if(i >= j) break;
            swap(a[i++], a[j--]);
        }
        q(a, l, j);
        q(a, j + 1, r);
    }
};
class guar_q_sort{
private:
    int select(vector<int>& a, int l, int r){
        if(r - l < 5){
            for (int i = l + 1; i < r; ++i) {
                int tmp = a[i];
                int j;
                for (j = i - 1; j >= l && a[j] > tmp; --j)
                    a[j + 1] = a[j];
                a[j + 1] = tmp;
            }
            return a[(l+r)/2];
        }
        for(int i = l; i  + 4 < r; i+=5){
            if (a[i + 4] < a[i])
                 swap(a[i + 4], a[i]);
            if (a[i + 3] < a[i + 1])
                 swap(a[i + 3], a[i + 1]);
            if (a[i + 1   ] < a[i]) {
                 swap(a[i + 1], a[i]);
                 swap(a[i + 4], a[i + 3]);
            }
            if (a[i + 2] < a[i + 1]) {
                int temp = a[i + 2];
                a[i + 2] = a[i + 1];
                if (temp < a[i])
                     swap(temp, a[i]);
                a[i + 1] = temp;
            } else if (a[i + 3] < a[i + 2])
                 swap(a[i + 3], a[i + 2]);
            if (a[i + 4] < a[i + 2]) {
                int x = a[i + 4];
                a[i + 4] = a[i + 3];
                a[i + 3] = a[i + 2];
                if (x < a[i + 1]) {
                    a[i + 2] = a[i + 1];
                    a[i + 1] = x;
                }
                else
                    a[i + 2] = x;
            }
            else if (a[i + 4] < a[i + 3])
                 swap(a[i + 4], a[i + 3]);
        }
        return a[l + 2 + 5 * (((r - l) / 5) / 2)];
    }
public:
    void q_sorter(vector<int>& a, int l, int r){
        if(l >= r){
            return;
        }
        int i = l;
        int j = r;
        int op_1 = select(a, l, r);
        while(i <= j){
            while(a[i] < op_1){
                i++;
            }
            while(a[j] > op_1){
                j--;
            }
            if(i >= j) break;
            swap(a[i++], a[j--]);
        }
        q_sorter(a, l, j);
        q_sorter(a, j + 1, r);
    }
};
class Heap{
private:
    void heapify(vector<int>& a, int size, int current) {
        int root = current;

        int left = 2 * current;
        int right = 2 * current + 1;

        if (left < size && a[left] > a[root]) {
            root = left;
        }

        if (right < size && a[right] > a[root])
            root = right;

        if (root != current) {
           swap(a[current], a[root]);
            heapify(a, size, root);
        }
    }
public:
    void heap_sort(vector<int>& a) {
        a.push_back(a[0]);
        for (int i = a.size() / 2; i > 0 ; --i)
            heapify(a, a.size(), i);

        for (int i = a.size() - 1; i > 1; --i)
        {
            swap(a[1], a[i]);
            heapify(a, i, 1);
        }
        a.erase(a.begin());
    }
};
void insert_timer(){
     random_device read;
     mt19937 generator(read());
     uniform_int_distribution<int> distrib1(INT_MIN, INT_MAX);
    cout << "Insertion_sort" << '\n';
    vector<int> a(20, 0);
    cout << a.size() << ' ';
    injection_sort<int> b;
    long long cnt = 0;
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.injection(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(50);
    cout << a.size() << ' ';
    cnt = 0;
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.injection(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(100);
    cout << a.size() << ' ';
    cnt = 0;
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.injection(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(150);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.injection(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(200);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.injection(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(300);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.injection(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(500);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.injection(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(1000);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.injection(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

}
void merge_timer_for_inj_comp(){
     random_device read;
     mt19937 generator(read());
     uniform_int_distribution<int> distrib1(INT_MIN, INT_MAX);
    cout<< '\n' << "Merge_sort" << '\n';
    vector<int> a(20, 0);
    cout << a.size() << ' ';
    merge_sort b;
    long long cnt = 0;
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.executer(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(50);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.executer(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(100);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.executer(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(150);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.executer(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(200);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.executer(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(300);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.executer(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(500);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.executer(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(1000);
    cnt = 0;
    cout << a.size() << ' ';
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < a.size() - 1; j++) a[j] = distrib1(generator);
        auto c_start =  chrono::high_resolution_clock::now();
        b.executer(a);
        auto c_end =  chrono::high_resolution_clock::now();
        cnt +=  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    }
    cout << (double)cnt/double(200) << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

}
void merge_timer(){
     random_device read;
     mt19937 generator(read());
     uniform_int_distribution<int> distrib1(INT_MIN, INT_MAX);
    cout << '\n' << "Merge_sort" << '\n';
    vector<int> a(1000, 0);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    merge_sort b;
    auto c_start =  chrono::high_resolution_clock::now();
    b.executer(a);
    auto c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(3000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.executer(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << ' '<< "unsorted" << endl;

    a.resize(10000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.executer(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(30000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.executer(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(50000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.executer(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(100000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.executer(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(300000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.executer(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(500000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.executer(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(1000000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.executer(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;
}
void qsort_timer(){
     random_device read;
     mt19937 generator(read());
     uniform_int_distribution<int> distrib1(INT_MIN, INT_MAX);
    cout << '\n' << "Q_sort" << '\n';
    vector<int> a(1000, 0);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    q_sort b;
    auto c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0, a.size() - 1);
    auto c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(3000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(10000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(30000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(50000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(100000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(300000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(500000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(1000000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;
}
void guar_q_sort_timer(){
     random_device read;
     mt19937 generator(read());
     uniform_int_distribution<int> distrib1(INT_MIN, INT_MAX);
    cout << '\n' << "Guaranteed Qsort" << '\n';
    vector<int> a(1000, 0);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    guar_q_sort b;
    auto c_start =  chrono::high_resolution_clock::now();
    b.q_sorter(a, 0, a.size() - 1);
    auto c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(3000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q_sorter(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(10000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q_sorter(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(30000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q_sorter(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(50000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q_sorter(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(100000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q_sorter(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(300000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q_sorter(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(500000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q_sorter(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(1000000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.q_sorter(a, 0, a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;
}
void heap_timer(){

     random_device read;
     mt19937 generator(read());
     uniform_int_distribution<int> distrib1(INT_MIN, INT_MAX);
    cout << '\n' << "Heap_sort" << '\n';
    vector<int> a(1000, 0);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    Heap b;
    auto c_start =  chrono::high_resolution_clock::now();
    b.heap_sort(a);
    auto c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(3000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.heap_sort(a);;
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(10000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.heap_sort(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(30000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.heap_sort(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(50000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.heap_sort(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(100000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.heap_sort(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(300000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.heap_sort(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(500000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.heap_sort(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;

    a.resize(1000000);
    cout << a.size() << ' ';
    for(int i = 0; i < a.size() - 1; i++) a[i] = distrib1(generator);
    c_start =  chrono::high_resolution_clock::now();
    b.heap_sort(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ' ;
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl ;
    else cout << ' '<< "unsorted" << endl;
}
void string_timer_20(){
    random_device read;
    mt19937 generator(read());
    uniform_int_distribution<int> distrib1(0, 25);
    vector<string> a(20);
    vector<string> a_1(20);
    injection_sort<string> b;
    bin_injection_sort<string> c;
    cout << "n = " << 20 << endl;
    cout << "m = " << 1 << " t1 = ";
    for(int i = 0; i < 20; i++){
        a[i] = 'a' + distrib1(generator);
        a_1[i] = a[i];
    }

    auto c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    auto c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;
    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a_1.begin(), a_1.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;


    cout << "m = " << 10 << " t1 = ";
    for(int i = 0; i < 20; i++){
        string s;
        for(int j = 0; j < 10; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;

    cout << "m = " << 100 << " t1 = ";
    for(int i = 0; i < 20; i++){
        string s;
        for(int j = 0; j < 100; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;
}
void string_timer(){
    random_device read;
    mt19937 generator(read());
    uniform_int_distribution<int> distrib1(0, 25);
    vector<string> a(20);
    vector<string> a_1(20);
    injection_sort<string> b;
    bin_injection_sort<string> c;
    cout << "n = " << 20 << endl;
    cout << "m = " << 1 << " t1 = ";
    for(int i = 0; i < 20; i++){
        a[i] = 'a' + distrib1(generator);
        a_1[i] = a[i];
    }

    auto c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    auto c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;
    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a_1.begin(), a_1.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;


    cout << "m = " << 10 << " t1 = ";
    for(int i = 0; i < 20; i++){
        string s;
        for(int j = 0; j < 10; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;

    cout << "m = " << 100 << " t1 = ";
    for(int i = 0; i < 20; i++){
        string s;
        for(int j = 0; j < 100; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;
}
void string_timer_200(){
    random_device read;
    mt19937 generator(read());
    uniform_int_distribution<int> distrib1(0, 25);
    vector<string> a(200);
    vector<string> a_1(200);
    injection_sort<string> b;
    bin_injection_sort<string> c;
    cout << "n = " << 200 << endl;
    cout << "m = " << 1 << " t1 = ";
    for(int i = 0; i < 200; i++){
        a[i] = 'a' + distrib1(generator);
        a_1[i] = a[i];
    }

    auto c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    auto c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;
    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a_1.begin(), a_1.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;


    cout << "m = " << 10 << " t1 = ";
    for(int i = 0; i < 200; i++){
        string s;
        for(int j = 0; j < 10; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;

    cout << "m = " << 100 << " t1 = ";
    for(int i = 0; i < 200; i++){
        string s;
        for(int j = 0; j < 100; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;
}
void string_timer_1200(){
    random_device read;
    mt19937 generator(read());
    uniform_int_distribution<int> distrib1(0, 25);
    vector<string> a(1200);
    vector<string> a_1(1200);
    injection_sort<string> b;
    bin_injection_sort<string> c;
    cout << "n = " << 1200 << endl;
    cout << "m = " << 1 << " t1 = ";
    for(int i = 0; i < 1200; i++){
        a[i] = 'a' + distrib1(generator);
        a_1[i] = a[i];
    }

    auto c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    auto c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;
    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a_1.begin(), a_1.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;


    cout << "m = " << 10 << " t1 = ";
    for(int i = 0; i < 1200; i++){
        string s;
        for(int j = 0; j < 10; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;

    cout << "m = " << 100 << " t1 = ";
    for(int i = 0; i < 1200; i++){
        string s;
        for(int j = 0; j < 100; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;
}
void string_timer_3000(){
    random_device read;
    mt19937 generator(read());
    uniform_int_distribution<int> distrib1(0, 25);
    vector<string> a(3000);
    vector<string> a_1(3000);
    injection_sort<string> b;
    bin_injection_sort<string> c;
    cout << "n = " << 3000 << endl;
    cout << "m = " << 1 << " t1 = ";
    for(int i = 0; i < 3000; i++){
        a[i] = 'a' + distrib1(generator);
        a_1[i] = a[i];
    }

    auto c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    auto c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;
    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a_1.begin(), a_1.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;


    cout << "m = " << 10 << " t1 = ";
    for(int i = 0; i < 3000; i++){
        string s;
        for(int j = 0; j < 10; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;

    cout << "m = " << 100 << " t1 = ";
    for(int i = 0; i < 3000; i++){
        string s;
        for(int j = 0; j < 100; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;
}
void string_timer_10000(){
    random_device read;
    mt19937 generator(read());
    uniform_int_distribution<int> distrib1(0, 25);
    vector<string> a(10000);
    vector<string> a_1(10000);
    injection_sort<string> b;
    bin_injection_sort<string> c;
    cout << "n = " << 10000 << endl;
    cout << "m = " << 1 << " t1 = ";
    for(int i = 0; i < 10000; i++){
        a[i] = 'a' + distrib1(generator);
        a_1[i] = a[i];
    }

    auto c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    auto c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;
    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    long long t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a_1.begin(), a_1.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;


    cout << "m = " << 10 << " t1 = ";
    for(int i = 0; i < 10000; i++){
        string s;
        for(int j = 0; j < 10; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;

    cout << "m = " << 100 << " t1 = ";
    for(int i = 0; i < 10000; i++){
        string s;
        for(int j = 0; j < 100; j++) {
            s.push_back(char('a' + distrib1(generator)));
        }
        a[i] = (s);
        a_1[i] = a[i];
    }

    c_start =  chrono::high_resolution_clock::now();
    b.injection(a);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t1 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << " t2 = ";
    else cout << ' '<< "unsorted" << endl;

    c_start =  chrono::high_resolution_clock::now();
    c.bin_injection(a_1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    t2 = chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count();
    if(is_sorted(a.begin(), a.end())) cout<< ' ' << "sorted" << endl;
    else cout << "unsorted" << endl;
    cout << double(t2)/double(t1) << endl;
}
void reversed_list_timer(){
    cout << "n = " << 1000 << endl;
    vector<int> a(1000, 0);
    vector<int> a_1(1000, 0);
    for(int i = 0; i < a.size(); i++){
        a[i] = a.size() - i;
        a_1[i] = a[i];
    }
    q_sort b;
    guar_q_sort c;
    auto c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0 , a.size() - 1);
    auto c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    c_start =  chrono::high_resolution_clock::now();
    c.q_sorter(a_1, 0 , a_1.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << endl;

    cout << "n = " << 10000 << endl;
    a.resize(10000);
    a_1.resize(10000);
    for(int i = 0; i < a.size(); i++){
        a[i] = a.size() - i;
        a_1[i] = a[i];
    }
    c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0 , a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    c_start =  chrono::high_resolution_clock::now();
    c.q_sorter(a_1, 0 , a_1.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << endl;

    cout << "n = " << 100000 << endl;
    a.resize(100000);
    a_1.resize(100000);
    for(int i = 0; i < a.size(); i++){
        a[i] = a.size() - i;
        a_1[i] = a[i];
    }
    c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0 , a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    c_start =  chrono::high_resolution_clock::now();
    c.q_sorter(a_1, 0 , a_1.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << endl;

    cout << "n = " << 1000000 << endl;
    a.resize(1000000);
    a_1.resize(1000000);
    for(int i = 0; i < a.size(); i++){
        a[i] = a.size() - i;
        a_1[i] = a[i];
    }
    c_start =  chrono::high_resolution_clock::now();
    b.q(a, 0 , a.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << ' ';
    c_start =  chrono::high_resolution_clock::now();
    c.q_sorter(a_1, 0 , a_1.size() - 1);
    c_end =  chrono::high_resolution_clock::now();
    cout <<  chrono::duration_cast< chrono::nanoseconds>(c_end - c_start).count() << endl;
}

int main(){
    insert_timer();
    //merge_timer_for_inj_comp();
    //qsort_timer();
    //merge_timer();
    //guar_q_sort_timer();
    //heap_timer();
    //string_timer_20();
    //string_timer_200();
    //string_timer_1200();
    //string_timer_3000();
    //string_timer_10000();
    //skip_timer
    //reversed_list_timer();
}
