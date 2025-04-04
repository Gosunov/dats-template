#pragma once
#include <vector>
#include <nlohmann/json.hpp>

#include <common/vec2.h>

struct Brick {
    Vec2 position;
    Vec2 size;
};

struct Ball {
    Vec2 position;
    Vec2 speed;
    double radius;
};

struct Pad {
    Vec2 position;
    Vec2 size;
};

struct World {
    std::vector<Brick> bricks;
    Ball ball;
    Pad pad;
};

enum class Direction {
    Left,
    Right
};

struct Command {
    Direction direction;
};

struct WorldResponse {
    World world;
};

struct CommandResponse {};


NLOHMANN_JSON_SERIALIZE_ENUM(Direction, {
    {Direction::Left, "left"},
    {Direction::Right, "right"},
})

void to_json(nlohmann::json& j, const Brick& b);
void to_json(nlohmann::json& j, const Ball& b);
void to_json(nlohmann::json& j, const Pad& p);
void to_json(nlohmann::json& j, const World& w);
void to_json(nlohmann::json& j, const Command& w);
void to_json(nlohmann::json& j, const WorldResponse& w);
void to_json(nlohmann::json& j, const CommandResponse& w);

void from_json(const nlohmann::json& j, Brick& b);
void from_json(const nlohmann::json& j, Ball& b);
void from_json(const nlohmann::json& j, Pad& p);
void from_json(const nlohmann::json& j, World& w);
void from_json(const nlohmann::json& j, Command& w);
void from_json(const nlohmann::json& j, WorldResponse& w);
void from_json(const nlohmann::json& j, CommandResponse& w);