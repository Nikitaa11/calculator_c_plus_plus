#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template<typename Number>
class Calculator {
public:
    Calculator() = default;

    void Set(Number number) {
        mem_ = number;
    }

    Number GetNumber() const {
        return mem_.value_or(Number{});
    }

    std::optional<Error> Add(Number number) {
        if (mem_.has_value()) {
            mem_ = mem_.value() + number;
        }
        return std::nullopt;
    }

    std::optional<Error> Sub(Number number) {
        if (mem_.has_value()) {
            mem_ = mem_.value() - number;
        }
        return std::nullopt;
    }

    std::optional<Error> Mul(Number number) {
        if (mem_.has_value()) {
            mem_ = mem_.value() * number;
        }
        return std::nullopt;
    }

    std::optional<Error> Div(Number number) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if (number == Number{}) {
                return "Division by zero";
            }
        }
        if (mem_.has_value()) {
            mem_ = mem_.value() / number;
        }
        return std::nullopt;
    }

    std::optional<Error> Pow(Number number) {
        if constexpr (std::is_same_v<Number, Rational>) {
            if (mem_.value_or(Number{}) == Number{} && number == Number{}) {
                return "Zero power to zero";
            }
            if (number.GetDenominator() != 1 && number != Number{}) {
                return "Fractional power is not supported";
            }
            if (mem_.has_value()) {
                mem_ = ::Pow(mem_.value(), number);
            }

        } else if constexpr (std::is_integral_v<Number>) {
            if (mem_.value_or(Number{}) == Number{} && number == Number{}) {
                return "Zero power to zero";
            }
            if (number < Number{}) {
                return "Integer negative power";
            }
            if (mem_.has_value()) {
                mem_ = ::IntegerPow(mem_.value(), number);
            }
        }  else {
            if (mem_.has_value()) {
                mem_ = std::pow(mem_.value(), number);
            }
        }

        return std::nullopt;
    }

    bool GetHasMem() const {
        return mem_value_.has_value();
    }

    void Save() {
        mem_value_ = mem_;
    }

    void Load() {
        mem_ = mem_value_;
    }


private:
    std::optional<Number> mem_{};
    std::optional<Number> mem_value_{};
};
