#include <iostream>

class foo {
public:
    foo(int i)
        : test {i} { }
    int test;
};

std::ostream &operator<<(std::ostream &os, const foo &obj) {
    os << obj.test;
    return os;
}

std::istream &operator>>(std::istream &is, foo &obj) {
    is >> obj.test;
    // if (/* obj.test 생성에 실패할 일이 없으므로 그냥 넘어가기*/)
    // is.setstate(std::ios::failbit);
    return is;
}


class bar {
public:
    bar(int i)
        : test {i} { }
    friend std::ostream &operator<<(std::ostream &os, const bar &obj);
    friend std::istream &operator>>(std::istream &is, bar &obj);
private:
    int test;
};

std::ostream &operator<<(std::ostream &os, const bar &obj) {
    os << obj.test;
    return os;
}

std::istream &operator>>(std::istream &is, bar &obj) {
    is >> obj.test;
    // if (/* obj.test 생성에 실패할 일이 없으므로 그냥 넘어가기*/)
    // is.setstate(std::ios::failbit);
    return is;
}



int main() {
    foo f {1};
    std::cin >> f;
    std::cout << f << std::endl;

    bar b {2};
    std::cin >> b;
    std::cout << b << std::endl;
}

