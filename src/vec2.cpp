#include <nlohmann/json.hpp>
#include "vec2.h"

using json = nlohmann::json;

Vec2 Vec2::operator+(const Vec2& other) const {
    return Vec2{x + other.x, y + other.y};
}

Vec2 Vec2::operator-(const Vec2& other) const {
    return Vec2{x - other.x, y - other.y};
}

Vec2& Vec2::operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

void to_json(json& j, const Vec2& v) {
    j = json{
        {"x", v.x},
        {"y", v.y},
    };
}

void from_json(const nlohmann::json& j, Vec2& v) {
    v.x = j.value("x", 0);
    v.y = j.value("y", 0);
}
