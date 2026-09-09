// Base code written by Jan Allbeck, Chris Czyzewicz, Cory Boatright, Tiantian Liu, Benedict Brown, and Adam Mally
// University of Pennsylvania

// At least some C++ compilers do funny things
// to C's math.h header if you don't define this
#define _USE_MATH_DEFINES

#include "vec4.h"
#include "mat4.h"
#include <iostream>
#include <math.h>
using namespace std;

void vec4AddTest() {
	vec4 a = vec4(1.f, 2.f, 3.f, 4.f);
	vec4 b = vec4(2.f, 4.f, 6.f, 8.f);
	std::cout << "vec4 + vec4 expected value: (3.0, 6.0, 9.0, 12.0)" << std::endl;
	std::cout << "vec4 + vec4 actual value: " << (a + b) << std::endl;
}


void printTestHeader(const char* name) {
    cout << "\n========================================\n";
    cout << name << '\n';
    cout << "========================================\n";
}

void testVec4Constructors() {
    printTestHeader("vec4 constructors");

    // Default constructor
    vec4 defaultVector;

    cout << "Default constructor expected: (0, 0, 0, 0)\n";
    cout << "Default constructor actual:   "
         << defaultVector << "\n\n";

    // Component constructor
    vec4 componentVector(1.f, 2.f, 3.f, 4.f);

    cout << "Component constructor expected: (1, 2, 3, 4)\n";
    cout << "Component constructor actual:   "
         << componentVector << "\n\n";

    // Copy constructor
    vec4 copiedVector(componentVector);

    cout << "Copy constructor expected: (1, 2, 3, 4)\n";
    cout << "Copy constructor actual:   "
         << copiedVector << '\n';
}

void testVec4Assignment() {
    printTestHeader("vec4 assignment operator");

    vec4 original(5.f, 6.f, 7.f, 8.f);
    vec4 assigned;

    assigned = original;

    cout << "Expected: (5, 6, 7, 8)\n";
    cout << "Actual:   " << assigned << '\n';
}

void testVec4Equality() {
    printTestHeader("vec4 equality and inequality");

    vec4 a(1.f, 2.f, 3.f, 4.f);
    vec4 b(1.f, 2.f, 3.f, 4.f);
    vec4 c(1.f, 2.f, 3.f, 5.f);

    cout << boolalpha;

    cout << "a == b expected: true\n";
    cout << "a == b actual:   " << (a == b) << "\n\n";

    cout << "a == c expected: false\n";
    cout << "a == c actual:   " << (a == c) << "\n\n";

    cout << "a != b expected: false\n";
    cout << "a != b actual:   " << (a != b) << "\n\n";

    cout << "a != c expected: true\n";
    cout << "a != c actual:   " << (a != c) << '\n';
}

void testDotProduct() {
    printTestHeader("vec4 dot product");

    vec4 a(1.f, 2.f, 3.f, 4.f);
    vec4 b(2.f, 3.f, 4.f, 5.f);

    // 1*2 + 2*3 + 3*4 + 4*5 = 40
    cout << "Expected: 40\n";
    cout << "Actual:   " << dot(a, b) << '\n';
}

void testCrossProduct() {
    printTestHeader("vec4 cross product");

    vec4 xAxis(1.f, 0.f, 0.f, 5.f);
    vec4 yAxis(0.f, 1.f, 0.f, 9.f);

    // The fourth elements are ignored.
    cout << "Expected: (0, 0, 1, 0)\n";
    cout << "Actual:   " << cross(xAxis, yAxis) << '\n';
}

void testNormalize() {
    printTestHeader("vec4 normalize");

    vec4 input(3.f, 0.f, 0.f, 4.f);

    // Length is 5, so the normalized vector is:
    // (3/5, 0, 0, 4/5)
    cout << "Expected: (0.6, 0, 0, 0.8)\n";
    cout << "Actual:   " << normalize(input) << "\n\n";

    cout << "Normalized length expected: 1\n";
    cout << "Normalized length actual:   "
         << length(normalize(input)) << '\n';
}

void testMat4Constructors() {
    printTestHeader("mat4 constructors");

    // Default constructor
    mat4 defaultMatrix;

    cout << "Default constructor expected:\n";
    cout << "[(1, 0, 0, 0)\n";
    cout << " (0, 1, 0, 0)\n";
    cout << " (0, 0, 1, 0)\n";
    cout << " (0, 0, 0, 1)]\n";

    cout << "Default constructor actual:\n";
    cout << defaultMatrix << "\n\n";

    // Diagonal constructor
    mat4 diagonalMatrix(2.f);

    cout << "Diagonal constructor expected:\n";
    cout << "[(2, 0, 0, 0)\n";
    cout << " (0, 2, 0, 0)\n";
    cout << " (0, 0, 2, 0)\n";
    cout << " (0, 0, 0, 2)]\n";

    cout << "Diagonal constructor actual:\n";
    cout << diagonalMatrix << "\n\n";

    // Four-column constructor
    mat4 columnMatrix(
        vec4(1.f, 2.f, 3.f, 4.f),
        vec4(5.f, 6.f, 7.f, 8.f),
        vec4(9.f, 10.f, 11.f, 12.f),
        vec4(13.f, 14.f, 15.f, 16.f)
        );

    cout << "Four-column constructor expected:\n";
    cout << "[(1, 5, 9, 13)\n";
    cout << " (2, 6, 10, 14)\n";
    cout << " (3, 7, 11, 15)\n";
    cout << " (4, 8, 12, 16)]\n";

    cout << "Four-column constructor actual:\n";
    cout << columnMatrix << "\n\n";

    // Copy constructor
    mat4 copiedMatrix(columnMatrix);

    cout << "Copy constructor expected:\n";
    cout << columnMatrix << '\n';

    cout << "Copy constructor actual:\n";
    cout << copiedMatrix << '\n';
}

void testMat4Assignment() {
    printTestHeader("mat4 assignment operator");

    mat4 original(3.f);
    mat4 assigned;

    assigned = original;

    cout << "Expected:\n";
    cout << original << '\n';

    cout << "Actual:\n";
    cout << assigned << '\n';
}

void testMat4Equality() {
    printTestHeader("mat4 equality and inequality");

    mat4 a = mat4::identity();
    mat4 b = mat4::identity();
    mat4 c = mat4::scale(2.f, 1.f, 1.f);

    cout << boolalpha;

    cout << "a == b expected: true\n";
    cout << "a == b actual:   " << (a == b) << "\n\n";

    cout << "a == c expected: false\n";
    cout << "a == c actual:   " << (a == c) << "\n\n";

    cout << "a != b expected: false\n";
    cout << "a != b actual:   " << (a != b) << "\n\n";

    cout << "a != c expected: true\n";
    cout << "a != c actual:   " << (a != c) << '\n';
}

void testRotation() {
    printTestHeader("mat4 rotate");

    // Test 1: rotate 90 degrees around the Z axis.
    mat4 expectedZ90(
        vec4(0.f, 1.f, 0.f, 0.f),
        vec4(-1.f, 0.f, 0.f, 0.f),
        vec4(0.f, 0.f, 1.f, 0.f),
        vec4(0.f, 0.f, 0.f, 1.f)
        );

    mat4 actualZ90 = mat4::rotate(
        90.f,
        0.f,
        0.f,
        1.f
        );

    cout << "90-degree Z rotation expected:\n";
    cout << expectedZ90 << '\n';

    cout << "90-degree Z rotation actual:\n";
    cout << actualZ90 << "\n\n";

    vec4 xAxis(1.f, 0.f, 0.f, 1.f);

    cout << "Rotated X-axis expected: approximately (0, 1, 0, 1)\n";
    cout << "Rotated X-axis actual:   "
         << actualZ90 * xAxis << "\n\n";

    // Test 2: rotate 180 degrees around the X axis.
    mat4 expectedX180(
        vec4(1.f, 0.f, 0.f, 0.f),
        vec4(0.f, -1.f, 0.f, 0.f),
        vec4(0.f, 0.f, -1.f, 0.f),
        vec4(0.f, 0.f, 0.f, 1.f)
        );

    mat4 actualX180 = mat4::rotate(
        180.f,
        1.f,
        0.f,
        0.f
        );

    cout << "180-degree X rotation expected:\n";
    cout << expectedX180 << '\n';

    cout << "180-degree X rotation actual:\n";
    cout << actualX180 << '\n';

    cout << "\nSmall values such as -0.000000087 are normal ";
    cout << "floating-point approximations of zero.\n";
}

void testMatrixMatrixMultiplication() {
    printTestHeader("matrix-matrix multiplication");

    mat4 first = mat4::scale(2.f, 3.f, 4.f);
    mat4 second = mat4::scale(5.f, 6.f, 7.f);

    mat4 expected = mat4::scale(10.f, 18.f, 28.f);
    mat4 actual = first * second;

    cout << "Expected:\n";
    cout << expected << '\n';

    cout << "Actual:\n";
    cout << actual << '\n';
}

void testMatrixVectorMultiplication() {
    printTestHeader("matrix-vector multiplication");

    mat4 translation = mat4::translate(10.f, 20.f, 30.f);
    vec4 point(1.f, 2.f, 3.f, 1.f);

    vec4 actual = translation * point;

    cout << "Expected: (11, 22, 33, 1)\n";
    cout << "Actual:   " << actual << '\n';
}

void testVectorMatrixMultiplication() {
    printTestHeader("vector-matrix multiplication");

    vec4 rowVector(1.f, 2.f, 3.f, 1.f);
    mat4 scale = mat4::scale(2.f, 3.f, 4.f);

    vec4 actual = rowVector * scale;

    cout << "Expected: (2, 6, 12, 1)\n";
    cout << "Actual:   " << actual << '\n';
}

int main() {
    testVec4Constructors();
    testVec4Assignment();
    testVec4Equality();
    testDotProduct();
    testCrossProduct();
    testNormalize();

    testMat4Constructors();
    testMat4Assignment();
    testMat4Equality();
    testRotation();
    testMatrixMatrixMultiplication();
    testMatrixVectorMultiplication();
    testVectorMatrixMultiplication();

    cout << "\nAll required tests finished.\n";

    return 0;
}