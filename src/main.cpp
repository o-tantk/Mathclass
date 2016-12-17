#include "tfm.h"
#include <iostream>

int main(int argc, char **argv){
    // Common functions
    std::cout << "pi : " << tfm::pi<float>() << std::endl;
    std::cout << "clamp(-0.5, 0.0, 1.0) : " << tfm::clamp(-0.5f, 0.0f, 1.0f) << std::endl;
    std::cout << "clamp(1.5, 0.0, 1.0) : " << tfm::clamp(1.5f, 0.0f, 1.0f) << std::endl;
    std::cout << "degrees(pi) : " << tfm::degrees(tfm::pi<float>()) << std::endl;
    std::cout << "radians(180) : " << tfm::radians(180.0f) << std::endl;

    std::cout << std::endl;
    // Vector

    tfm::vec3 v(0.0f, 1.0f, 0.0f);
    std::cout << v << std::endl;
    std::cout << "v(1, 1, 1) = " << tfm::vec3(1, 1, 1) << std::endl;
    std::cout << "Length of v(1, 1, 1) = " << tfm::length(tfm::vec3(1, 1, 1)) << std::endl;
    std::cout << "normalize(v(1, 1, 1) = " << tfm::normalize(tfm::vec3(1, 1, 1)) << std::endl;
    std::cout << "cross(v(1, 0), v(0, 1)) = " << tfm::cross(tfm::vec3(1, 0, 0), tfm::vec3(0, 1, 0)) << std::endl;

    std::cout << std::endl;
    // Matrix

    tfm::mat3 m( tfm::vec3(1.0f, 0.0f, 0.0f),
                tfm::vec3(0.0f, 1.0f, 0.0f),
                tfm::vec3(0.0f, 0.0f, 1.0f) );
    std::cout << m + tfm::mat3() << std::endl;
    std::cout << "10.0f * m = " << 10.0f * m << std::endl;
    std::cout << "m * 1.5f = " << m * 1.5f << std::endl;

    tfm::mat3 A = tfm::rotate(tfm::pi<float>(), tfm::pi<float>() * 0.5f, tfm::pi<float>() * 0.25f).m;
    std::cout << "A = " << A << std::endl;
    std::cout << "det(A) = " << tfm::determinant(A) << std::endl;
    std::cout << "trs(A) = " << tfm::transpose(A) << std::endl;
    std::cout << "inv(A) = " << tfm::inverse(A) << std::endl;
    std::cout << "inv(A) * A = " << tfm::inverse(A) * A << std::endl;

    tfm::mat3 B = tfm::scale(tfm::pi<float>(), -tfm::pi<float>() * 0.5f, tfm::pi<float>() * 0.25f).m;
    std::cout << "B = " << B << std::endl;
    std::cout << "det(B) = " << tfm::determinant(B) << std::endl;
    std::cout << "trs(B) = " << tfm::transpose(B) << std::endl;
    std::cout << "inv(B) = " << tfm::inverse(B) << std::endl;
    std::cout << "inv(B) * B = " << tfm::inverse(B) * B << std::endl;


    std::cout << std::endl;
    // Quaternion

    tfm::quat q;
    std::cout << q << std::endl;
    tfm::quat rot = tfm::exp( tfm::radians(90.0f) * 0.5f * tfm::vec3(0.0f, 0.0f, 1.0f) );
    std::cout << "exp(45` * v(0, 0, 1)) : " << rot << std::endl;
    std::cout << "log( ^ ) : " << tfm::log(rot) << std::endl;
    std::cout << "degrees(log( ^ ).z) : " << tfm::degrees(tfm::log(rot).z) << std::endl;
    std::cout << "mat3_cast( ^ ) : " << tfm::mat3_cast(rot) << std::endl;
    std::cout << "quat_cast( I ) : " << tfm::quat_cast(tfm::mat3()) << std::endl;

    std::cout << std::endl;
    // Transformations

    tfm::mat3 translation( tfm::vec3(1.0f, 0.0f, 0.0f),
                            tfm::vec3(0.0f, 1.0f, 0.0f),
                            tfm::vec3(10.0f, 10.0f, 1.0f) );
    std::cout << "mat3 T(10, 10) * v(0, 0) = " << translation * tfm::vec3(0.0f, 0.0f, 1.0f) << std::endl;
    std::cout << "transf T(10, 10, 0) * v(0, 0, 1) = " << tfm::translate(10.0f, 10.0f, 0.0f) * tfm::vec3(0.0f, 0.0f, 1.0f) << std::endl;
    std::cout << "transq T(10, 10, 0) * v(0, 0, 1) = " << tfm::q_translate(10.0f, 10.0f, 0.0f) * tfm::vec3(0.0f, 0.0f, 1.0f) << std::endl;
    std::cout << "transf R(0, 0, 90`) * v(1, 0, 0) = " << tfm::rotate(tfm::radians(90.0f), tfm::vec3(0, 0, 1)) * tfm::vec3(1.0f, 0.0f, 0.0f) << std::endl;
    std::cout << "transq R(0, 0, 90`) * v(1, 0, 0) = " << tfm::q_rotate(tfm::radians(90.0f), tfm::vec3(0, 0, 1)) * tfm::vec3(1.0f, 0.0f, 0.0f) << std::endl;
    std::cout << "transf R(0, 90`, 0) * v(1, 0, 0) = " << tfm::rotate(tfm::radians(90.0f), tfm::vec3(0, 1, 0)) * tfm::vec3(1.0f, 0.0f, 0.0f) << std::endl;
    std::cout << "transq R(0, 90`, 0) * v(1, 0, 0) = " << tfm::q_rotate(tfm::radians(90.0f), tfm::vec3(0, 1, 0)) * tfm::vec3(1.0f, 0.0f, 0.0f) << std::endl;
    std::cout << "transf R(90`, 0, 0) * v(1, 0, 0) = " << tfm::rotate(tfm::radians(90.0f), tfm::vec3(1, 0, 0)) * tfm::vec3(1.0f, 0.0f, 0.0f) << std::endl;
    std::cout << "transq R(90`, 0, 0) * v(1, 0, 0) = " << tfm::q_rotate(tfm::radians(90.0f), tfm::vec3(1, 0, 0)) * tfm::vec3(1.0f, 0.0f, 0.0f) << std::endl;

    std::cout << std::endl;

    std::cout << "Test ends." << std::endl;
    return 0;
}
