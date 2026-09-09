#include "vec4.h"
#include <cmath>
#include <stdexcept>


// Default constructor: initialize every component to zero.
vec4::vec4()
    : data{0.f, 0.f, 0.f, 0.f} {
}

// Component constructor.
vec4::vec4(float x, float y, float z, float w)
    : data{x, y, z, w} {
}

// Copy constructor.
vec4::vec4(const vec4& v2)
    : data{v2[0], v2[1], v2[2], v2[3]} {
}

// Read-only indexing.
float vec4::operator[](unsigned int index) const {
    if (index >= data.size()) {
        throw std::out_of_range("vec4 index out of range");
    }

    return data[index];
}

// Mutable indexing.
float& vec4::operator[](unsigned int index) {
    if (index >= data.size()) {
        throw std::out_of_range("vec4 index out of range");
    }

    return data[index];
}

// Assignment.
vec4& vec4::operator=(const vec4& v2) {
    if (this != &v2) {
        for (unsigned int i = 0; i < data.size(); ++i) {
            data[i] = v2[i];
        }
    }

    return *this;
}

// Exact component-wise equality.
bool vec4::operator==(const vec4& v2) const {
    for (unsigned int i = 0; i < data.size(); ++i) {
        if (data[i] != v2[i]) {
            return false;
        }
    }

    return true;
}

// Exact component-wise inequality.
bool vec4::operator!=(const vec4& v2) const {
    return !(*this == v2);
}

// Compound vector addition.
vec4& vec4::operator+=(const vec4& v2) {
    for (unsigned int i = 0; i < data.size(); ++i) {
        data[i] += v2[i];
    }

    return *this;
}

// Compound vector subtraction.
vec4& vec4::operator-=(const vec4& v2) {
    for (unsigned int i = 0; i < data.size(); ++i) {
        data[i] -= v2[i];
    }

    return *this;
}

// Compound scalar multiplication.
vec4& vec4::operator*=(float c) {
    for (float& component : data) {
        component *= c;
    }

    return *this;
}

// Compound scalar division.
vec4& vec4::operator/=(float c) {
    for (float& component : data) {
        component /= c;
    }

    return *this;
}

// Vector addition.
vec4 vec4::operator+(const vec4& v2) const {
    vec4 result(*this);
    result += v2;
    return result;
}

// Vector subtraction.
vec4 vec4::operator-(const vec4& v2) const {
    vec4 result(*this);
    result -= v2;
    return result;
}

// Vector multiplied by a scalar.
vec4 vec4::operator*(float c) const {
    vec4 result(*this);
    result *= c;
    return result;
}

// Vector divided by a scalar.
vec4 vec4::operator/(float c) const {
    vec4 result(*this);
    result /= c;
    return result;
}

// Four-dimensional dot product.
float dot(const vec4& v1, const vec4& v2) {
    float result = 0.f;

    for (unsigned int i = 0; i < 4; ++i) {
        result += v1[i] * v2[i];
    }

    return result;
}

// Three-dimensional cross product.
// The fourth component is always zero.
vec4 cross(const vec4& v1, const vec4& v2) {
    return vec4(
        v1[1] * v2[2] - v1[2] * v2[1],
        v1[2] * v2[0] - v1[0] * v2[2],
        v1[0] * v2[1] - v1[1] * v2[0],
        0.f
        );
}

// Geometric length measured across all four components.
float length(const vec4& v) {
    return std::sqrt(dot(v, v));
}

// Return a unit-length copy of the vector.
vec4 normalize(const vec4& v) {
    return v / length(v);
}

// Scalar multiplied by a vector.
vec4 operator*(float c, const vec4& v) {
    return v * c;
}

// Stream output.
std::ostream& operator<<(std::ostream& out, const vec4& v) {
    out << "("
        << v[0] << ", "
        << v[1] << ", "
        << v[2] << ", "
        << v[3] << ")";

    return out;
}