#pragma once
#include <nlohmann/json.hpp>

struct Vec2 {
public:
    double x, y;

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2& operator+=(const Vec2& other);
    Vec2& operator-=(const Vec2& other);
};

void to_json(nlohmann::json& j, const Vec2& v);
void from_json(const nlohmann::json& j, Vec2& v);