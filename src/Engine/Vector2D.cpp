//
// Created by KRATSTOM on 12.04.21.
//

#include "Vector2D.h"
#include <stdexcept>


Vector2D::Vector2D(const float &x, const float &y) :
        x(x), y(y) {}

/**
 * @param other the second vector
 * @return a sum of two Vectors
 */
Vector2D Vector2D::operator+(const Vector2D &other) const {
    Vector2D newVector(x + other.x, y + other.y);
    return newVector;
}

/**
 * @param other the second vector
 * @return difference of two vectors
 */
Vector2D Vector2D::operator-(const Vector2D &other) const {
    Vector2D newVector(x - other.x, y - other.y);
    return newVector;
}

/**
 * @param other the second vector
 * @return a product of two vectors
 */
Vector2D Vector2D::operator*(const Vector2D &other) const {
    Vector2D newVector;
    newVector.x = x * other.x + y * other.x;
    newVector.y = x * other.y + y * other.y;
    return newVector;
}

/**
 * @param value the multiplier
 * @return a scalar product of the vector and float number
 */
Vector2D Vector2D::operator * (const float &value) const {
    return {x * value, y * value};
}

/**
 * @param value divisor
 * @return a scalar division of the vector and float number
 */
Vector2D Vector2D::operator / (const float &value) const {
    if(value == 0)
        throw std::invalid_argument("Vector2D::operator /: 0 value division!");
    return {x / value, y / value};
}

/**
 * Add a vector to this.
 * @param other other vector
 * @return this
 */
Vector2D &Vector2D::operator += (const Vector2D &other) {
    x += other.x;
    y += other.y;
    return *this;
}

/**
 * Remove a vector from this
 * @param other the other vector
 * @return this
 */
Vector2D &Vector2D::operator -= (const Vector2D &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

/**
 * Multiply this by float number.
 * @param val multiplier
 * @return this
 */
Vector2D &Vector2D::operator *= (const float &val) {
    x *= val;
    y *= val;
    return *this;
}

/**
 * Divide this by float number
 * @param val non-zero divisor
 * @return this
 */
Vector2D &Vector2D::operator/=(const float &val) {
    if(val == 0)
        throw std::invalid_argument("Vector2D::operator /=: division by 0!");
    x /= val;
    y /= val;
    return *this;
}

/**
 * @param other the other vector to compare
 * @return true if values of two vectors are equal.
 */
bool Vector2D::operator==(const Vector2D &other) const {
    return std::abs(x - other.x) < 0.000001 && std::abs(y - other.y) < 0.000001;
}



/**
 * Normalize this vector
 */
void Vector2D::normalize() {
    if(x == 0 && y == 0)
        return;
    *this /= getMagnitude();
}

/**
 * @return normalized copy of this vector
 */
Vector2D Vector2D::normalized() const {
    Vector2D norm(x,y);
    norm.normalize();
    return norm;
}

/**
 * @return magnitude of this vector
 */
float Vector2D::getMagnitude() const {
    return sqrtf(x * x + y * y);
}

/**
 * Converts this vector to string <br>
 * @return "{ x=val, y=val }"
 */
std::string Vector2D::toString() const {
    return "{ x=" + std::to_string(x) + ", y=" + std::to_string(y) + " }";
}


/**
 * Calculates the distance between two vectors.
 * @param a vector a
 * @param b vector b
 * @return the distance between a and b
 */
float Vector2D::distance(const Vector2D &a, const Vector2D &b) {
    float c = fabsf(a.x - b.x);
    float d = fabsf(a.y - b.y);
    return sqrtf(c * c + d * d);
}

/**
 * @return Vector2(0, 1).
 */
Vector2D Vector2D::up() {
    return Vector2D(0,1);
}

/**
 * @return Vector2(0, -1).
 */
Vector2D Vector2D::down() {
    return Vector2D(0, -1);
}

/**
 * @return Vector2(-1, 0).
 */
Vector2D Vector2D::left() {
    return Vector2D(-1, 0);
}

/**
* @return Vector2(1, 0).
*/
Vector2D Vector2D::right() {
    return Vector2D(1, 0);
}

/**
 * @param a the starting point
 * @param b the ending point
 * @return a vector from a to b
 */
Vector2D Vector2D::moveTowards(const Vector2D &a, const Vector2D &b) {
    return {
            b.x - a.x,
            b.y - a.y
    };
}

/**
 * Clamp the vector.
 */
void Vector2D::clamp() {
    float xDecimal = x - (float)((int)x);
    if(xDecimal < 0.5)
        x = std::floor(x);
    else
        x = std::ceil(x);

    float yDecimal = y - (float)((int)y);
    if(yDecimal < 0.5)
        y = std::floor(y);
    else
        y = std::ceil(y);
}









