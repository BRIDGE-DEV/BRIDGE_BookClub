// rule of zero.
// custom destructor, custom copy/move constrctor, custom copy/move assignment operator. 이 다섯개가 다 필요없으면, 그냥 하지 하나라도 만들지 마라. 심플 이즈 더 베스트.
// std::string, std::vector 두 친구와 함께라면 왠만하면 rule of zero 달성이 가능하다.

#include <iostream>

class ruleofzero {
public:
    std::string s;
};

int main() {
    ruleofzero roz{ "Hello World!" }; // implicit constructor

    ruleofzero roz2(roz); // implicit copy constructor

    ruleofzero roz3{ "foo" };
    roz3 = roz; // implicit copy assignment operator

    std::cout << "before: " << roz.s << std::endl;
    ruleofzero roz4 { std::move(roz) }; // implicit move assignment operator
    std::cout << "after: " << roz.s << std::endl;
}

