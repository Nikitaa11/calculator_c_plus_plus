#pragma once

#include <iostream>
#include <cstdlib>
#include <numeric>
#include <cstdint>

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {}

    Rational(int numerator, int denominator)
        : numerator_(numerator), denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
    }

    Rational(int value)
        : numerator_(value), denominator_(1) {}

    Rational(const Rational& r)
        : numerator_(r.numerator_), denominator_(r.denominator_) {}

    int GetNumerator() const { return numerator_; }
    int GetDenominator() const { return denominator_; }

    Rational Inv() const {
        if (numerator_ == 0) {
            std::abort();
        }
        return Rational(denominator_, numerator_);
    }

    Rational operator+() const { return *this; }
    Rational operator-() const { return {-numerator_, denominator_}; }

    friend std::istream& operator>>(std::istream& is, Rational& r);
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);

    Rational& operator=(const Rational& r) = default;
    Rational& operator=(int value) {
        numerator_ = value;
        denominator_ = 1;
        return *this;
    }

    Rational& operator*=(const Rational& r) {
        numerator_ *= r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& r) {
        numerator_ *= r.denominator_;
        denominator_ *= r.numerator_;
        Reduction();
        return *this;
    }

    Rational& operator+=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ + denominator_ * r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ - denominator_ * r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational operator+(const Rational& r2) const {
        Rational other{*this};
        other += r2;
        return other;
    }

    Rational operator-(const Rational& r2) const {
        Rational other{*this};
        other -= r2;
        return other;
    }

    Rational operator*(const Rational& r2) const {
        Rational other{*this};
        other *= r2;
        return other;
    }

    Rational operator/(const Rational& r2) const {
        Rational other{*this};
        other /= r2;
        return other;
    }

private:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.numerator_;
    if (r.denominator_ != 1) {
        os << " / " << r.denominator_;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int n, d;
    char div;

    if (!(is >> n)) {
        return is;
    }

    if (!(is >> std::ws >> div)) {
        r = Rational(n, 1);
        is.clear();
        return is;
    }

    if (div != '/') {
        r = Rational(n, 1);
        is.unget();
        return is;
    }

    if (!(is >> d) || (d == 0)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    r = Rational(n, d);
    return is;
}

inline auto operator<=>(const Rational& r1, const Rational& r2) {
    std::int64_t c1 = static_cast<std::int64_t>(r1.GetNumerator()) * r2.GetDenominator();
    std::int64_t c2 = static_cast<std::int64_t>(r2.GetNumerator()) * r1.GetDenominator();
    return c1 <=> c2;
}

inline bool operator==(const Rational& r1, const Rational& r2) {
    return r1.GetNumerator() * r2.GetDenominator() == r2.GetNumerator() * r1.GetDenominator();
}
