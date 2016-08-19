#include "tfm.h"
#include <iostream>

int main(int argc, char **argv){
    std::cout << "pi : " << tfm::pi<float>() << std::endl;
    std::cout << "clamp(1.5, 0.0, 1.0) : " << tfm::clamp(1.5f, 0.0f, 1.0f) << std::endl;
    std::cout << "degrees(pi) : " << tfm::degrees(tfm::pi<float>()) << std::endl;

    std::cout << std::endl;

    tfm::vec3 v(0.0f, 1.0f, 0.0f);
    std::cout << v << std::endl;
    std::cout << "v(1, 1, 1) = " << tfm::vec3(1, 1, 1) << std::endl;
    std::cout << "Length of v(1, 1, 1) = " << tfm::length(tfm::vec3(1, 1, 1)) << std::endl;
    std::cout << "normalize(v(1, 1, 1) = " << tfm::normalize(tfm::vec3(1, 1, 1)) << std::endl;
    std::cout << "cross(v(1, 0), v(0, 1)) = " << tfm::cross(tfm::vec3(1, 0, 0), tfm::vec3(0, 1, 0)) << std::endl;

    std::cout << std::endl;

    tfm::mat3 m( tfm::vec3(1.0f, 0.0f, 0.0f),
                tfm::vec3(0.0f, 1.0f, 0.0f),
                tfm::vec3(0.0f, 0.0f, 1.0f) );
    std::cout << m + tfm::mat3() << std::endl;
    std::cout << "10.0f * m = " << 10.0f * m << std::endl;
    std::cout << "m * 1.5f = " << m * 1.5f << std::endl;

    std::cout << std::endl;

    tfm::mat3 translation( tfm::vec3(1.0f, 0.0f, 0.0f),
                            tfm::vec3(0.0f, 1.0f, 0.0f),
                            tfm::vec3(10.0f, 10.0f, 1.0f) );
    std::cout << "T(10, 10) * v(0, 0) = " << translation * tfm::vec3(0.0f, 0.0f, 1.0f) << std::endl;

    std::cout << std::endl;

    std::cout << "Test ends." << std::endl;
    return 0;
}
