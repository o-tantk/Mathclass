#include "tfm.h"
#include <iostream>

int main(int argc, char **argv){
    std::cout << "pi : " << tfm::pi<float>() << std::endl;
    std::cout << "clamp(1.5, 0.0, 1.0) : " << tfm::clamp(1.5f, 0.0f, 1.0f) << std::endl;
    std::cout << "degrees(pi) : " << tfm::degrees(tfm::pi<float>()) << std::endl;

    tfm::vec3 v(0.0f, 1.0f, 0.0f);
    std::cout << v << std::endl;

    tfm::mat3 m( tfm::vec3(1.0f, 0.0f, 0.0f),
                tfm::vec3(0.0f, 1.0f, 0.0f),
                tfm::vec3(0.0f, 0.0f, 1.0f) );
    std::cout << m + tfm::mat3() << std::endl;

    std::cout << "Test ends." << std::endl;
    return 0;
}
