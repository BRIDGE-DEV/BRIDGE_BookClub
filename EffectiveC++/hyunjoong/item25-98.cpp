// clang++ -std=c++98 item25-98.cpp && ./a.out

#include <iostream>

void *operator new(std::size_t count) throw(std::bad_alloc) {
    std::cout << "call new " << count << std::endl;
    return std::malloc(count);
}

class foo {
public:
    foo() {
        std::cout << "foo ctor" << std::endl;
    }
    std::vector<int> vec;
};

class baz {
public:
    baz()
    : buf(new char[0x10]) {
        std::cout << "baz ctor" << std::endl;
    }

    baz(const baz &other) 
    : buf(new char[0x10]) {
        std::cout << "baz cpy ctor" << std::endl;
        std::memcpy(buf, other.buf, 0x10);
    }

    baz &operator=(const baz &other)  {
        std::cout << "baz cpy op" << std::endl;
        baz tmp = other;
        std::swap(buf, tmp.buf);
        return *this;
    }

    ~baz()  {
        delete[] buf;
    }

    char *buf;
};

// 책에서 제시한 방법대로 한 버젼.
class baz2 {
public:
    baz2()
    : buf(new char[0x10]) {
        std::cout << "baz2 ctor" << std::endl;
    }

    baz2(const baz2 &other) 
    : buf(new char[0x10]) {
        std::cout << "baz2 cpy ctor" << std::endl;
        std::memcpy(buf, other.buf, 0x10);
    }

    baz2 &operator=(const baz2 &other)  {
        std::cout << "baz2 cpy op" << std::endl;
        baz2 tmp = other;
        std::swap(buf, tmp.buf);
        return *this;
    }

    ~baz2()  {
        delete[] buf;
    }

    void swap(baz2 &other) {
        using std::swap;
        swap(buf, other.buf);
    }
private:
    char *buf;
};

namespace std {
    template<>
    void swap<baz2>(baz2 &a, baz2 &b)  {
        a.swap(b);
    }
}

// 책에서 제시한 template 버젼대로 한 버젼.
template<typename T>
class baz2_t {
public:
    baz2_t()
    : buf(new T[0x10]) {
        std::cout << "baz2_t ctor" << std::endl;
    }

    baz2_t(const baz2_t &other) 
    : buf(new T[0x10]) {
        std::cout << "baz2_t cpy ctor" << std::endl;
        std::memcpy(buf, other.buf, 0x10);
    }

    baz2_t &operator=(const baz2_t &other)  {
        std::cout << "baz2_t cpy op" << std::endl;
        baz2_t tmp = other;
        std::swap(buf, tmp.buf);
        return *this;
    }

    ~baz2_t()  {
        delete[] buf;
    }

    void swap(baz2_t &other) {
        using std::swap;
        swap(buf, other.buf);
    }
private:
    T *buf;
};


template<typename T>
void swap(baz2_t<T> &a, baz2_t<T> &b) {
    a.swap(b);
}

template<typename T>
void dosth(T& obj1, T& obj2) {
    using std::swap;
    swap(obj1, obj2);
}

int main() {
    std::cout << "\t:: foo :: " << std::endl;
    foo f0;
    f0.vec.push_back(0);
    foo f1;
    f1.vec.push_back(1);

    std::cout << ":: foo swap" << std::endl;

    std::swap(f0, f1);
    // 이전 버젼과 다르게, std::move가 없으므로 std::vector의 swap이 operator new를 호출한다.

    std::cout << std::endl;



    std::cout << "\t:: baz :: " << std::endl;

    baz bz0;
    baz bz1;

    std::cout << ":: baz swap" << std::endl;

    std::swap(bz0, bz1); // 이 한 줄이 폭탄이 됨.
    // call new 16
    // baz cpy ctor
    // baz cpy op
    // call new 16
    // baz cpy ctor
    // baz cpy op
    // call new 16
    // baz cpy ctor
    // 복사 생성자 1번, 복사 대입 연산자 2번. 총 heap alloc 3번.
    //   _Tp __t(std::move(__x));
    // __x = std::move(__y);
    // __y = std::move(__t);

    std::cout << std::endl;



    std::cout << "\t:: baz2 :: " << std::endl;

    baz2 bz2_0;
    baz2 bz2_1;

    std::cout << ":: baz2 swap" << std::endl;

    std::swap(bz2_0, bz2_1);

    std::cout << std::endl;



    std::cout << "\t:: baz2_t :: " << std::endl;

    baz2_t<int> bz2t_0;
    baz2_t<int> bz2t_1;

    std::cout << ":: baz2_t swap" << std::endl;

    using std::swap;
    swap(bz2t_0, bz2t_1);

    std::cout << std::endl;


    std::cout << "\t:: dosth ::" << std::endl;
    dosth(bz2t_0, bz2t_1);
}

