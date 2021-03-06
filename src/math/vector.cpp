
#include <cmath>
#include "math/vector.h"

namespace math {

Vector Vector::zero_vec = Vector(0);
Vector Vector::one_vec = Vector(1);
Vector Vector::x_axis = Vector(1, 0, 0);
Vector Vector::y_axis = Vector(0, 1, 0);
Vector Vector::z_axis = Vector(0, 0, 1);

Vector::Vector() noexcept {
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(double scale) noexcept {
    x = scale;
    y = scale;
    z = scale;
}

Vector::Vector(double x, double y, double z) noexcept {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(const Vector& vec) noexcept {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

bool Vector::operator==(const Vector& vec) const {
    return this->x == vec.x && this->y == vec.y && this->z == vec.z;
}

bool Vector::operator!=(const Vector& vec) const {
    return this->x != vec.x || this->y != vec.y || this->z != vec.z;
}

Vector Vector::operator-() const {
    return Vector(-x, -y, -z);
}

Vector Vector::operator+(const Vector& vec) const {
    return Vector(x + vec.x, y + vec.y, z + vec.z);
}

Vector Vector::operator-(const Vector& vec) const {
    return Vector(x - vec.x, y - vec.y, z - vec.z);
}

Vector Vector::operator*(const Vector& vec) const {
    return Vector(x * vec.x, y * vec.y, z * vec.z);
}

Vector Vector::operator/(const Vector& vec) const {
    return Vector(x / vec.x, y / vec.y, z / vec.z);
}

double Vector::operator|(const Vector& vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector Vector::operator^(const Vector& vec) const {
    return Vector(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

Vector& Vector::operator+=(const Vector& vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Vector& Vector::operator-=(const Vector& vec) {
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

Vector& Vector::operator*=(const Vector& vec) {
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

Vector& Vector::operator/=(const Vector& vec) {
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}

double Vector::dot(const Vector& vec) const {
    return *this | vec;
}

Vector Vector::cross(const Vector& vec) const {
    return *this ^ vec;
}

double Vector::distance_sq(const Vector& vec) const {
    return std::pow(x - vec.x, 2) + std::pow(y - vec.y, 2) + std::pow(z - vec.z, 2);
}

double Vector::distance(const Vector& vec) const {
    return std::sqrt(std::pow(x - vec.x, 2) + std::pow(y - vec.y, 2) + std::pow(z - vec.z, 2));
}

double Vector::length() const {
    return std::sqrt(x*x + y*y + z*z);
}

Vector Vector::get_normalized() const {
    double inv_sq = 1/length();
    if (inv_sq == 0)
        return Vector::zero_vec;
    return Vector(x * inv_sq, y * inv_sq, z * inv_sq);
}

Vector& Vector::normalize() {
    double inv_sq = 1/length();
    if (inv_sq == 0)
        return *this;
    x *= inv_sq;
    y *= inv_sq;
    z *= inv_sq;
    return *this;
}

double Vector::distance_sq(const Vector& a, const Vector& b) {
    return std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2) + std::pow(a.z - b.z, 2);
}

double Vector::distance(const Vector& a, const Vector& b) {
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2) + std::pow(a.z - b.z, 2));
}

}
