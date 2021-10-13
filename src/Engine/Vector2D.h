//
// Created by KRATSTOM on 11.04.21.
//

#pragma once

#include <cmath>
#include <string>

class Vector2D {
private:
public:

    float x = 0, y = 0;

    Vector2D() = default;
    Vector2D(const Vector2D & other) = default;
    Vector2D(const float & x, const float & y);

    Vector2D operator + (const Vector2D & other) const;
    Vector2D operator - (const Vector2D & other) const;
    Vector2D operator * (const Vector2D & other) const;

    Vector2D operator * (const float & value) const;
    Vector2D operator / (const float & value) const;

    Vector2D & operator += (const Vector2D & other);
    Vector2D & operator -= (const Vector2D & other);
    Vector2D & operator *= (const float & val);
    Vector2D & operator /= (const float & val);

    bool operator == (const Vector2D & other) const;

    /**
     * Normalize this vector
     */
    void normalize();

    /**
     * @return normalized copy of this vector
     */
    Vector2D normalized() const;

    /**
     * @return magnitude of this vector
     */
    float getMagnitude() const;

    void clamp();

    /**
     * Converts this vector to string <br>
     * @return { x=val, y=val }
     */
    std::string toString() const;


    /**
     * Calculates the distance between two vectors.
     * @param a vector a
     * @param b vector b
     * @return the distance between a and b
     */
    static float distance(const Vector2D & a, const Vector2D & b);

    static Vector2D moveTowards(const Vector2D & a, const Vector2D & b);

    /**
     * @return Vector2(0, 1).
     */
    static Vector2D up();

    /**
     * @return Vector2(0, -1).
     */
    static Vector2D down();

    /**
     * @return Vector2(-1, 0).
     */
    static Vector2D left();

    /**
     * @return Vector2(1, 0).
     */
    static Vector2D right();
};


