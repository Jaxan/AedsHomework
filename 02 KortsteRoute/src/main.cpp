#include <iostream>
#include "../include/NetwerkMatrix.h"

int main() {

    try {

        NetwerkMatrix test("sporen.txt");

        std::cout << "Mijn station heeft de grootte: " << test.grootte() << std::endl;

    } catch (std::exception const& e) {

        std::cout << e.what() <<std::endl;

    }

    return 0;

}
