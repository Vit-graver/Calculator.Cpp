#include "calculator.h"
#include <cmath>
#include <sstream> 

Number memory = 0.0;
bool memorySet = false;

bool ReadNumber(Number& result) {
    if (!(std::cin >> result)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    return true;
}

bool RunCalculatorCycle() {
    Number current = 0.0;
    std::string command;

    while (std::cin >> command) {
        if (command == "q") {
            return true;
        } else if (command == "c") {
            current = 0.0;
        } else if (command == "=") {
            std::cout << current << std::endl;
        } else if (command == "s") {
            memory = current;
            memorySet = true;
        } else if (command == "l") {
            if (!memorySet) {
                std::cerr << "Error: Memory is empty" << std::endl;
                return false;
            }
            current = memory;
        } else if (command == "+") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            current += operand;
        } else if (command == "-") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            current -= operand;
        } else if (command == "*") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            current *= operand;
        } else if (command == "/") {
             Number operand;
              if (!ReadNumber(operand)) {
               return false;
                   }
                    if (operand == 0.0) {
                    current = std::numeric_limits<Number>::infinity();
                    } else {
                      current /= operand;
                    }
        } else if (command == "**") {
            Number exponent;
            if (!ReadNumber(exponent)) {
                return false;
            }
            // Проверка на 0 в отрицательной степени
            if (exponent < 0 && current == 0.0) {
                std::cerr << "Error: Cannot raise zero to a negative power" << std::endl;
                return false;
            }
            // Проверка на отрицательное основание в дробной степени
            if (current < 0 && std::fmod(exponent, 1.0) != 0.0) {
                std::cerr << "Error: Negative base with fractional exponent" << std::endl;
                return false;
            }
            current = std::pow(current, exponent);
        } else if (command == ":") {
            Number operand;
            if (!ReadNumber(operand)) {
                return false;
            }
            current = operand;
        } else {
            // Это нужно для случаев, когда число идёт первым в строке
            Number num;
            std::istringstream iss(command);
            if (iss >> num) {
                current = num;
            } else {
                if (current == 0.0){
                std::cerr << "Error: Numeric operand expected" << std::endl;
                return false;
                } else {
                std::cerr << "Error: Unknown token " << command << std::endl;
                return false;
                }
            }
        }
    }
    return true;
}