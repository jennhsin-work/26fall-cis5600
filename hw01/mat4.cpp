#include "mat4.h"
#include <cmath>
#include <stdexcept>

// Default constructor: create an identity matrix.
mat4::mat4()
    : data{
          vec4(1.f, 0.f, 0.f, 0.f),
          vec4(0.f, 1.f, 0.f, 0.f),
          vec4(0.f, 0.f, 1.f, 0.f),
          vec4(0.f, 0.f, 0.f, 1.f)
      } {
}

// Create a diagonal matrix.
mat4::mat4(float diag)
    : data{
          vec4(diag, 0.f, 0.f, 0.f),
          vec4(0.f, diag, 0.f, 0.f),
          vec4(0.f, 0.f, diag, 0.f),
          vec4(0.f, 0.f, 0.f, diag)
      } {
}

// Create a matrix from four columns.
mat4::mat4(
    const vec4& col0,
    const vec4& col1,
    const vec4& col2,
    const vec4& col3
    )
    : data{col0, col1, col2, col3} {
}

// Copy constructor.
mat4::mat4(const mat4& m2)
    : data{m2[0], m2[1], m2[2], m2[3]} {
}

// Read-only column indexing.
vec4 mat4::operator[](unsigned int index) const {
    if (index >= data.size()) {
        throw std::out_of_range("mat4 column index out of range");
    }

    return data[index];
}

// Mutable column indexing.
vec4& mat4::operator[](unsigned int index) {
    if (index >= data.size()) {
        throw std::out_of_range("mat4 column index out of range");
    }

    return data[index];
}

// Create a rotation matrix using Rodrigues' rotation formula.
mat4 mat4::rotate(float angle, float x, float y, float z) {
    // Normalize the rotation axis.
    float axisLength = std::sqrt(x * x + y * y + z * z);

    x /= axisLength;
    y /= axisLength;
    z /= axisLength;

    // Convert the angle from degrees to radians.
    const float pi = std::acos(-1.f);
    float radians = angle * pi / 180.f;

    float c = std::cos(radians);
    float s = std::sin(radians);
    float t = 1.f - c;

    // The constructor takes columns, not rows.
    vec4 col0(
        t * x * x + c,
        t * x * y + s * z,
        t * x * z - s * y,
        0.f
        );

    vec4 col1(
        t * x * y - s * z,
        t * y * y + c,
        t * y * z + s * x,
        0.f
        );

    vec4 col2(
        t * x * z + s * y,
        t * y * z - s * x,
        t * z * z + c,
        0.f
        );

    vec4 col3(0.f, 0.f, 0.f, 1.f);

    return mat4(col0, col1, col2, col3);
}

// Create a translation matrix.
mat4 mat4::translate(float x, float y, float z) {
    return mat4(
        vec4(1.f, 0.f, 0.f, 0.f),
        vec4(0.f, 1.f, 0.f, 0.f),
        vec4(0.f, 0.f, 1.f, 0.f),
        vec4(x, y, z, 1.f)
        );
}

// Create a scale matrix.
mat4 mat4::scale(float x, float y, float z) {
    return mat4(
        vec4(x,   0.f, 0.f, 0.f),
        vec4(0.f, y,   0.f, 0.f),
        vec4(0.f, 0.f, z,   0.f),
        vec4(0.f, 0.f, 0.f, 1.f)
        );
}

// Create an identity matrix.
mat4 mat4::identity() {
    return mat4();
}

// Assignment.
mat4& mat4::operator=(const mat4& m2) {
    if (this != &m2) {
        for (unsigned int column = 0; column < data.size(); ++column) {
            data[column] = m2[column];
        }
    }

    return *this;
}

// Exact matrix equality.
bool mat4::operator==(const mat4& m2) const {
    for (unsigned int column = 0; column < data.size(); ++column) {
        if (data[column] != m2[column]) {
            return false;
        }
    }

    return true;
}

// Exact matrix inequality.
bool mat4::operator!=(const mat4& m2) const {
    return !(*this == m2);
}

// Compound element-wise addition.
mat4& mat4::operator+=(const mat4& m2) {
    for (unsigned int column = 0; column < data.size(); ++column) {
        data[column] += m2[column];
    }

    return *this;
}

// Compound element-wise subtraction.
mat4& mat4::operator-=(const mat4& m2) {
    for (unsigned int column = 0; column < data.size(); ++column) {
        data[column] -= m2[column];
    }

    return *this;
}

// Compound scalar multiplication.
mat4& mat4::operator*=(float c) {
    for (vec4& column : data) {
        column *= c;
    }

    return *this;
}

// Compound scalar division.
mat4& mat4::operator/=(float c) {
    for (vec4& column : data) {
        column /= c;
    }

    return *this;
}

// Element-wise matrix addition.
mat4 mat4::operator+(const mat4& m2) const {
    mat4 result(*this);
    result += m2;
    return result;
}

// Element-wise matrix subtraction.
mat4 mat4::operator-(const mat4& m2) const {
    mat4 result(*this);
    result -= m2;
    return result;
}

// Matrix multiplied by a scalar.
mat4 mat4::operator*(float c) const {
    mat4 result(*this);
    result *= c;
    return result;
}

// Matrix divided by a scalar.
mat4 mat4::operator/(float c) const {
    mat4 result(*this);
    result /= c;
    return result;
}

// Matrix-matrix multiplication.
mat4 mat4::operator*(const mat4& m2) const {
    // Each result column is this matrix multiplied by the
    // corresponding column of m2.
    return mat4(
        (*this) * m2[0],
        (*this) * m2[1],
        (*this) * m2[2],
        (*this) * m2[3]
        );
}

// Matrix-column-vector multiplication.
vec4 mat4::operator*(const vec4& v) const {
    return vec4(
        dot(row(*this, 0), v),
        dot(row(*this, 1), v),
        dot(row(*this, 2), v),
        dot(row(*this, 3), v)
        );
}

// Return a row of the matrix.
vec4 row(const mat4& m, unsigned int index) {
    if (index >= 4) {
        throw std::out_of_range("mat4 row index out of range");
    }

    return vec4(
        m[0][index],
        m[1][index],
        m[2][index],
        m[3][index]
        );
}

// Return the transpose of the matrix.
mat4 transpose(const mat4& m) {
    return mat4(
        row(m, 0),
        row(m, 1),
        row(m, 2),
        row(m, 3)
        );
}

// Scalar multiplied by a matrix.
mat4 operator*(float c, const mat4& m) {
    return m * c;
}

// Row-vector multiplied by a matrix.
vec4 operator*(const vec4& v, const mat4& m) {
    return vec4(
        dot(v, m[0]),
        dot(v, m[1]),
        dot(v, m[2]),
        dot(v, m[3])
        );
}

// Print the matrix in row-major visual form.
std::ostream& operator<<(std::ostream& out, const mat4& m) {
    out << "[" << row(m, 0) << "\n"
        << " " << row(m, 1) << "\n"
        << " " << row(m, 2) << "\n"
        << " " << row(m, 3) << "]";

    return out;
}