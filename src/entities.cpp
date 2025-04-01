#include <nlohmann/json.hpp>

#include "entities.h"

using json = nlohmann::json;

void to_json(json& j, const Brick& b) {
    j = json{
        {"position", b.position},
        {"size", b.size},
    };
}

void from_json(const json& j, Brick& b) {
    b.position = j["position"];
    b.size = j["size"];
}

void to_json(json& j, const Ball& b) {
    j = json{
        {"position", b.position},
        {"speed", b.speed},
        {"radius", b.radius},
    };
}

void from_json(const json& j, Ball& b) {
    b.position = j["position"];
    b.speed = j["speed"];
    b.radius = j["radius"];
}

void to_json(json& j, const Pad& p) {
    j = json{
        {"position", p.position},
        {"size", p.size},
    };
}

void from_json(const json& j, Pad& p) {
    p.position = j["position"];
    p.size = j["size"];
}

void to_json(json& j, const World& w) {
    j = json{
        {"bricks", w.bricks},
        {"ball", w.ball},
        {"pad", w.pad}
    };
}

void from_json(const json& j, World& w) {
    w.bricks = j["bricks"];
    w.ball = j["ball"];
    w.pad = j["pad"];
}

void to_json(json& j, const Command& c) {
    j = json{
        {"direction", c.direction},
    };
}

void from_json(const json& j, Command& c) {
    c.direction = j["direction"];
}

void to_json(json& j, const WorldResponse& w) {
    j = json{
        {"world", w.world},
    };
}

void from_json(const json& j, WorldResponse& w) {
    w.world = j["world"];
}

void to_json(json&, const CommandResponse&) {}

void from_json(const json&, CommandResponse&) {}