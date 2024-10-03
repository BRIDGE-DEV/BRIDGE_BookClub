// move semantic이 필요하다고요? 하...

#include <iostream>

class ruleoffive {
public:
    char *p;
    static constexpr int SIZE = 10;

    ruleoffive() noexcept
    : p {new char[SIZE]}
    {
        std::cout << "ctor" << std::endl;
    }

    ~ruleoffive() noexcept {
        std::cout << "dtor" << std::endl;
        delete[] p;
    }

    ruleoffive(const ruleoffive &other) noexcept
    : p {new char[SIZE]}
    {
        std::cout << "cctor" << std::endl;
        std::memcpy(p, other.p, SIZE);
    }

    ruleoffive &operator=(const ruleoffive &other) noexcept {
        std::cout << "operator=" << std::endl;
        auto tmp {other};
        std::swap(p, tmp.p);
        return *this;
    }

    // 여기까진 rule of three와 동일합니다. 하지만 문제는 move assignment/constructor가 암시적으로 생성되지 않는다는거죠. 이걸 만들지 않으면 복사 생성자만 호출되고 제대로 move semantic이 일어나지 않음을 확인할 수 있습니다.

    ruleoffive(ruleoffive &&other) noexcept
    : p {std::exchange(other.p, nullptr)}
    {
        std::cout << "mctor" << std::endl;
    }

    ruleoffive &operator=(ruleoffive &&other) noexcept {
        auto tmp { std::move(other) };
        std::swap(p, tmp.p);
        return *this;
    }
};

// 이렇게 간단한 클래스인데도 이정도의 boilerplate가 필요하다는 얘깁니다. 그니깐 rule of zero를 애용합시다. (가능하다면요!)

int main() {
    ruleoffive rof;

    std::printf("before: %p\n", rof.p);
    ruleoffive rof2 = std::move(rof);
    std::printf("after: %p\n", rof.p);

    ruleoffive rof3;
    std::printf("before: %p\n", rof2.p);
    rof3 = std::move(rof2);
    std::printf("after: %p\n", rof2.p);
}

