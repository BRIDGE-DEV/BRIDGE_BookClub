#include <iostream>
// custom destructor, custom copy constrctor, custom copy assignment operator. 셋 중 하나라도 있으면, 셋 전체가 필요할 확률이 매우 높다(걍 셋 다 써라). 셋 중 하나라도 = delete됐으면 셋 전체 다 = delete이어야 할 확률이 매우 높다.

class ruleofthree {
public:
    ruleofthree() :
    p(new char[SIZE]) { // 1. owning ptr이 있다고 해 봅시다.
        std::cout << "ctor ";
        std::printf("%p\n", p);
    }

    ~ruleofthree() noexcept { // noexcept안해줘도 왠만하면 암시적 noexcept라고 하는데.. 왠만하면이라는 말이 참 걸리니까 써 줍니다.
        std::cout << "dtor ";
        std::printf("%p\n", p);
        delete[] p; // 2. 그러면 객체가 죽을 때 free해줘야겠죠? 자 custom destructor를 만들었으니 rule of three!
    }

    // 3. copy constructor를 해 봅시다!
    //  a. const reference로 파라미터를 받을 것.
    //  b. deep-copy를 수행할 것.
    //  이걸 안만들면 어떻게 될까? 자동으로 만들어진 copy assignment operator은멤버인 p를 그냥 복사하고 끝난다. 그러면 어떻게 된다? 같은 메모리 주소를 둘이서 포인팅 하게 되고 double free가 일어나고 어플리케이션이 터진다! 이 코드를 커멘트 아웃하고 실행시켜보면 바로 터진다. destructor에 메모리 주소도 나오게 해 뒀으니 확인해보기 바란다.
    ruleofthree(const ruleofthree &other) noexcept
    : p(new char[SIZE]) {
        std::cout << "cctor ";
        std::printf("%p\n", p);
        std::memcpy(p, other.p, SIZE);
    }


    // 4. copy assignment operator를 해 봅시다!
    //  a. non-const reference를 반환할 것
    //  b. const reference로 파라미터를 받을 것
    //  c. virtual이 아닐 것
    //  d. copy-and-swap idiom을 사용하자
    //  e. 만약 새로운 멤버가 추가되면.. 여기도 꼭 넣어야한다!!
    //  휴.. 기억할 것도 많다..
    // 만약 이게 없다면... 위에서 설명한 거랑 같은 일이 일어나겠죠?
    ruleofthree &operator=(const ruleofthree &other) noexcept {
        std::cout << "cao" << std::endl;
        auto tmp = other; // copy constructor
        std::swap(p, tmp.p); // 나는 복사 생성된 p의 값을 가지고, 이 임시 객체는 스코프 나갈 때 소멸.
        return *this;
    }

    // 여기에서 책에서 나온 대로 pass-by-value로 파라미터를 넘길 수도 있지만.. 너무 머리 쓴 코드가 아닐까? 실제로 -O2 플래그로 컴파일 했을 때 차이가 있긴 한데.. 솔직히 어셈블리가 너무 복잡해서 못읽겠다.. cpp core guidelines에서는 위에 형식을 추천하니깐..
    // ruleofthree &operator=(ruleofthree other) noexcept {
    //     std::cout << "cao" << std::endl;
    //     std::swap(p, other.p);
    //     return *this;
    // }

private:
    static constexpr size_t SIZE = 10;
    char *p;
};

int main() {
    ruleofthree rot; // constructor
    ruleofthree rot2 = rot; // copy constructor

    ruleofthree rot3;
    rot3 = rot; // copy assignment operator

    // ruleofthree rot_cpy_2 { rot }; 이 형태가 가장 좋은 copy constructor 호출이 아닐까?
    // ruleofthree rot_cpy(rot); 사실 이게 원래 의도가 아닐까?
}
