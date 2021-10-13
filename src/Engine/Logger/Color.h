//
// Created by KRATSTOM on 28.03.2021.
//

#pragma once

#include <iostream>

class Color {

public:
    enum Code {
        RED = 31,
        BLUE = 34,
        YELLOW = 93,
        DEFAULT = 00
    };

    explicit Color(Code pCode) : code(pCode) {}

    friend std::ostream &operator<<(std::ostream &out, const Color &col) {
        return out << "\033[" << col.code << "m";
    }

private:
    Code code;
};
