//ALPHA RMATH.h V1.0

#ifndef RMATH_H
#define RMATH_H

#include <atomic>
#include <stdexcept>
#include <cmath>
#include <limits>
#include <random>
#include <vector>
#include <numeric>
#include <complex>
#include <algorithm>
#include <array>
#include <bitset>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <iterator>
#include <chrono>
#include <thread>
#include <future>

class RMATH {
public:
    static constexpr double PI = 3.1415;
    static constexpr double A_PI = 3.141592653589793;
    static constexpr double E = 2.7182;
    static constexpr double A_E = 2.718281828459045;
    static constexpr double PHI = 1.6180;
    static constexpr double A_PHI = 1.618033988749895;
    static constexpr double SQRT2 = 1.4142;
    static constexpr double A_SQRT2 = 1.4142135623730951;
    static constexpr double SQRT3 = 1.7320;
    static constexpr double A_SQRT3 = 1.7320508075688772;
    static constexpr double GOLDEN_RATIO = 1.6180;
    static constexpr double A_GOLDEN_RATIO = 1.618033988749895;
    static constexpr double LN2 = 0.6931;
    static constexpr double A_LN2 = 0.6931471805599453;
    static constexpr double LN10 = 2.3025;
    static constexpr double A_LN10 = 2.302585092994046;
    static constexpr double DEGREES_TO_RADIANS = PI / 180.0;
    static constexpr double RADIANS_TO_DEGREES = 180.0 / PI;
    
    static int Add(int a, int b);
    static int Subtract(int a, int b);
    static int Multiply(int a, int b);
    static double Divide(int a, int b);
    static double Power(double base, int exponent);
    static long long Factorial(int n);
    static double Sine(double radians);
    static double Cosine(double radians);
    static double Tangent(double radians);
    static double Logarithm(double value);
    static double SquareRoot(double value);
    static double Max(double a, double b);
    static double Min(double a, double b);
    static int RandomInt(int min, int max);
    static double RandomDouble(double min, double max);

    static double Exponential(double x);
    static double Absolute(double x);
    static double RadiansToDegrees(double radians);
    static double DegreesToRadians(double degrees);

    static void AtomicAdd(std::atomic<int>& target, int value);
    static void AtomicSubtract(std::atomic<int>& target, int value);
    static void AtomicMultiply(std::atomic<int>& target, int value);
    static void AtomicDivide(std::atomic<int>& target, int value);

    static int AtomicRandomInt(int min, int max);
    static double AtomicRandomDouble(double min, double max);

    static std::vector<double> AddVectors(const std::vector<double>& a, const std::vector<double>& b);
    static double DotProduct(const std::vector<double>& a, const std::vector<double>& b);
    static double Magnitude(const std::vector<double>& a);

    static std::vector<std::vector<double>> AddMatrices(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b);
    static std::vector<std::vector<double>> MultiplyMatrices(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b);

    static double Round(double value);
    static double Floor(double value);
    static double Ceiling(double value);

    static double ArcSine(double value);
    static double ArcCosine(double value);
    static double ArcTangent(double value);

    struct Vec2 {
        double x, y;

        Vec2(double x = 0, double y = 0) : x(x), y(y) {}

        Vec2 operator+(const Vec2& other) const {
            return Vec2(x + other.x, y + other.y);
        }

        Vec2 operator-(const Vec2& other) const {
            return Vec2(x - other.x, y - other.y);
        }

        Vec2 operator*(double scalar) const {
            return Vec2(x * scalar, y * scalar);
        }

        double Dot(const Vec2& other) const {
            return x * other.x + y * other.y;
        }

        double Magnitude() const {
            return std::sqrt(x * x + y * y);
        }

        Vec2 Normalize() const {
            double mag = Magnitude();
            if (mag == 0) throw std::invalid_argument("Cannot normalize a zero vector.");
            return *this * (1.0 / mag);
        }
    };

    struct Vec3 {
        double x, y, z;

        Vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

        Vec3 operator+(const Vec3& other) const {
            return Vec3(x + other.x, y + other.y, z + other.z);
        }

        Vec3 operator-(const Vec3& other) const {
            return Vec3(x - other.x, y - other.y, z - other.z);
        }

        Vec3 operator*(double scalar) const {
            return Vec3(x * scalar, y * scalar, z * scalar);
        }

        Vec3 Cross(const Vec3& other) const {
            return Vec3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            );
        }

        double Dot(const Vec3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        double Magnitude() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vec3 Normalize() const {
            double mag = Magnitude();
            if (mag == 0) throw std::invalid_argument("Cannot normalize a zero vector.");
            return *this * (1.0 / mag);
        }

        Vec3 ProjectOnto(const Vec3& other) const {
            double dotProduct = Dot(other);
            double otherMagnitudeSquared = other.Magnitude() * other.Magnitude();
            return other * (dotProduct / otherMagnitudeSquared);
        }

        Vec3 Rotate(const Vec3& axis, double angleRadians) const {
            Vec3 normalizedAxis = axis.Normalize();
            double cosAngle = std::cos(angleRadians);
            double sinAngle = std::sin(angleRadians);

            return (*this * cosAngle) +
                   (normalizedAxis.Cross(*this) * sinAngle) +
                   (normalizedAxis * (normalizedAxis.Dot(*this) * (1 - cosAngle)));
        }
    };
};

inline int RMATH::Add(int a, int b) {
    return a + b;
}

inline int RMATH::Subtract(int a, int b) {
    return a - b;
}

inline int RMATH::Multiply(int a, int b) {
    return a * b;
}

inline double RMATH::Divide(int a, int b) {
    if (b == 0) throw std::invalid_argument("Division by zero.");
    return static_cast<double>(a) / b;
}

inline double RMATH::Power(double base, int exponent) {
    return std::pow(base, exponent);
}

inline long long RMATH::Factorial(int n) {
    if (n < 0) throw std::invalid_argument("Factorial of negative number.");
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

inline double RMATH::Sine(double radians) {
    return std::sin(radians);
}

inline double RMATH::Cosine(double radians) {
    return std::cos(radians);
}

inline double RMATH::Tangent(double radians) {
    return std::tan(radians);
}

inline double RMATH::Logarithm(double value) {
    if (value <= 0) throw std::invalid_argument("Logarithm of non-positive number.");
    return std::log(value);
}

inline double RMATH::SquareRoot(double value) {
    if (value < 0) throw std::invalid_argument("Square root of negative number.");
    return std::sqrt(value);
}

inline int RMATH::RandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

inline double RMATH::RandomDouble(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

inline double RMATH::Exponential(double x) {
    return std::exp(x);
}

inline double RMATH::Absolute(double x) {
    return std::fabs(x);
}

inline double RMATH::RadiansToDegrees(double radians) {
    return radians * RADIANS_TO_DEGREES;
}

inline double RMATH::DegreesToRadians(double degrees) {
    return degrees * DEGREES_TO_RADIANS;
}

inline void RMATH::AtomicAdd(std::atomic<int>& target, int value) {
    target.fetch_add(value);
}

inline void RMATH::AtomicSubtract(std::atomic<int>& target, int value) {
    target.fetch_sub(value);
}

inline void RMATH::AtomicMultiply(std::atomic<int>& target, int value) {
    int expected = target.load();
    while (!target.compare_exchange_weak(expected, expected * value));
}

inline void RMATH::AtomicDivide(std::atomic<int>& target, int value) {
    if (value == 0) throw std::invalid_argument("Division by zero.");
    int expected = target.load();
    while (!target.compare_exchange_weak(expected, expected / value));
}

inline int RMATH::AtomicRandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

inline double RMATH::AtomicRandomDouble(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

inline std::vector<double> RMATH::AddVectors(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) throw std::invalid_argument("Vectors must be of the same size.");
    std::vector<double> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
}

inline double RMATH::DotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) throw std::invalid_argument("Vectors must be of the same size.");
    double result = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

inline double RMATH::Magnitude(const std::vector<double>& a) {
    return std::sqrt(DotProduct(a, a));
}

inline std::vector<std::vector<double>> RMATH::AddMatrices(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b) {
    if (a.size() != b.size() || a[0].size() != b[0].size()) throw std::invalid_argument("Matrices must have the same dimensions.");
    std::vector<std::vector<double>> result(a.size(), std::vector<double>(a[0].size()));
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a[i].size(); ++j) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    return result;
}

inline std::vector<std::vector<double>> RMATH::MultiplyMatrices(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b) {
    if (a[0].size() != b.size()) throw std::invalid_argument("Invalid matrix dimensions for multiplication.");
    std::vector<std::vector<double>> result(a.size(), std::vector<double>(b[0].size(), 0));
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b[0].size(); ++j) {
            for (size_t k = 0; k < a[0].size(); ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

inline double RMATH::Round(double value) {
    return std::round(value);
}

inline double RMATH::Floor(double value) {
    return std::floor(value);
}

inline double RMATH::Ceiling(double value) {
    return std::ceil(value);
}

inline double RMATH::ArcSine(double value) {
    return std::asin(value);
}

inline double RMATH::ArcCosine(double value) {
    return std::acos(value);
}

inline double RMATH::ArcTangent(double value) {
    return std::atan(value);
}

#endif
