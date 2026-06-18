#include <iostream>

enum class Priority
{
    EASY,
    MEDIUM, 
    HARD,
    CRITICAL
};
template <typename T>
struct priority_queue
{
    T* arr = nullptr;
    size_t capacity = 0;
    size_t size = 0;
    float grow = 2.0;
};


namespace sort{
    template <typename T>
    bool comp(const T& a, const T& b)
{
    return (a > b) ? true : false; 
}

    //построение дерево
    template <typename T>
    void heapify(T* arr, size_t size, size_t idx, 
    bool (*comp)(const T& a, const T& b))
{
    size_t left = idx * 2 + 1;
    size_t right = idx * 2 + 2;
    size_t largest = idx;

    if(left < size && comp(arr[left], arr[largest])) largest = left;
    if(right < size && comp(arr[right], arr[largest])) largest = right;

    if(idx != largest)
    {
        std::swap(arr[idx], arr[largest]);
        heapify(arr, size, largest, comp);
    }
}
    template <typename T>
    void build_heap(T* arr, size_t size,
    bool (*comp)(const T& a, const T& b))
{
    for(int i = (size / 2 - 1); i >= 0; --i)
    {
        heapify(arr, size, i, comp);
    }
}

    template <typename T>
    void print(const T* arr, size_t size, char ch = ' ')
{
    for(int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << ch;
    }
    std::cout << '\n';
}

    template <typename T>
    void heap_sort(T* arr, size_t size, 
        bool (*comp)(const T& a, const T& b)
    )
    {
        for(int i = 0; i < size; ++i)
        {
            build_heap(arr, size - i, comp);
            std::swap(arr[size- 1 - i], arr[0]);
        }   
    }
}
template <typename T>
void resize(T*& arr, size_t& size, 
    const size_t newSize)
{
    if(size == newSize) return;
    T* buf = new T[newSize];
    for(int i = 0; i < std::min(newSize, size); ++i)
    {
        buf[i] = arr[i];
    }
    size = newSize;
    delete[] arr;
    arr = buf;
    buf = nullptr;
}
template <typename T>
void push(priority_queue<T>& pr, const T& elem,
    bool (*comp)(const T& a, const T& b)
)
{
    if(pr.capacity == pr.size) resize(pr.arr, pr.capacity,
        static_cast<size_t>(pr.capacity * 2 + 1));
    pr.arr[pr.size] = elem;
    size_t pos = pr.size;
    ++pr.size;
    while(pos > 0)
    {
        size_t parent = (pos - 1) / 2;
        if(!comp(pr.arr[pos],pr.arr[parent])) break;

        std::swap(pr.arr[pos], pr.arr[parent]);
        pos = parent;
        
    }
}
template <typename T>
T pop(priority_queue<T>& pr, 
    bool (*comp)(const T& a, const T& b))
{
    if(pr.size == 0) throw std::runtime_error("out");
    T res = *pr.arr;
    *pr.arr = pr.arr[pr.size-1];
    --pr.size;
    sort::heapify(pr.arr, pr.size, 0, comp);
    return res;
}


size_t deep_three(
    size_t size
)
{
    size_t res = 0;
    while(size > 0)
    {
        size >>= 1;
        ++res;
    }
    return res;
}
template <typename T>
void print_three(
    T* arr, size_t size
)
{
    size_t height = deep_three(size);
    if(height == 0) return;
    size_t width = (1 << height) - 1;

    size_t current = 0;
    for(int i = 1; i <= height; ++i)
    {
        size_t cur_wd = (1 << i) - 1;
        size_t num_delim = (width - cur_wd) / 2;
        size_t num = (1 << (i - 1));
        for(int j = 0; j < num_delim; ++j)
        {
            std::cout << ' ';
        }
        for(int j = 0; j < num; ++j)
        {
            if(current >= size) break;
            std::cout << arr[current++] << ' ';
            
        }
        std::cout << std::endl << std::endl;
    }
}
int main()
{
    //test
    /*
    priority_queue<int> a;
    for(int i = 0; i < 20; ++i)
    {
        push(a, rand() % 9, sort::comp);
       // sort::print(a.arr, a.size);
    }

    sort::print<int>(a.arr, a.size);
    
    for(int i = 0; i < 19; ++i)
    {
    std::cout << pop(a, sort::comp) << std::endl;
    sort::print<int>(a.arr, a.size);
    }
    }*/
    size_t size = 15;
    int* arr = new int[size];
    for(int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 10;
    }
    //sort::print(arr, size);
    print_three(arr, size);
    sort::build_heap(arr, size, sort::comp);
    print_three(arr, size);
    sort::heap_sort(arr, size,sort::comp);
    print_three(arr, size);
    return 0;
}