#include "common/entities.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <client/api.h>
#include <common/random.h>

using json = nlohmann::json;
using namespace std;

LocalAPI::LocalAPI() {
    w = {
        .bricks = {
            {
                .position = {2, 2},
                .size = {8, 3}
            }
        },
        .ball = { 
            .position = {1, 1},
            .speed = {5, 6},
            .radius = 3, 
        },
        .pad = { 
            .position = {0, 0}, 
            .size = {10, 2}
        },
    };
}

WorldResponse LocalAPI::get_world() {
    return WorldResponse{w};
}

CommandResponse LocalAPI::send_command(const Command& c) {
    double width = 100;
    double height = 100;

    switch (c.direction) {
        case Direction::Right:
            w.pad.position.x += 1;
            break;
        case Direction::Left:
            w.pad.position.x -= 1;
            break;
    }

    w.ball.position += w.ball.speed;
    if (w.ball.position.x < 0 || w.ball.position.x > width) {
        w.ball.speed.x = -w.ball.speed.x;
    }
    if (w.ball.position.y < 0 || w.ball.position.y > height) {
        w.ball.speed.y = -w.ball.speed.y;
    }

    if (randrange(0, 10) == 0) {
        w.bricks.push_back(
            Brick{ 
                .position = { 
                    (double)randint(0, width),
                    (double)randint(0, height) 
                }, 
                .size = {8, 3} 
            }
        );
    }

    auto is_colliding = [&](const Brick& b) {
        const Ball& ball = w.ball;
        double closest_x = std::clamp(ball.position.x, b.position.x, b.position.x + b.size.x);
        double closest_y = std::clamp(ball.position.y, b.position.y, b.position.y + b.size.y);

        // Calculate the distance from the closest point to the circle's center
        double dx = ball.position.x - closest_x;
        double dy = ball.position.y - closest_y;

        // Calculate the square of the distance
        double d = dx * dx + dy * dy;

        // If the distance squared is less than or equal to the square of the radius, they intersect
        return d <= ball.radius * ball.radius;
    };

    w.bricks.erase(
        std::remove_if(w.bricks.begin(), w.bricks.end(), is_colliding),
        w.bricks.end()
    );

    return CommandResponse{};
}

ServerAPI::ServerAPI(const string& host, const string& token) : host(host), token(token) {
    int max_size = 1048576 * 5;
    int max_files = 3;
    logger = spdlog::rotating_logger_mt("requests", "logs/requests.txt", max_size, max_files);
}

json ServerAPI::get(const std::string& endpoint) {
    std::string url = "https://" + host + endpoint;

    logger->info("Making request to {}", url);
    cpr::Response response = cpr::Get(
        cpr::Url{url},
        cpr::Header{{"Authorization", "Bearer " + token}},
        cpr::Timeout{1000}
    );    
    if (response.error) {
        throw std::runtime_error("Network Error: " + response.error.message);
    }
    logger->info("Got response {} {}", response.status_code, response.text);
    if (response.status_code != 200) {
        throw std::runtime_error("HTTP Error: " + std::to_string(response.status_code));
    }
    return json::parse(response.text);
}

json ServerAPI::post(const std::string& endpoint, const json& payload) {
    std::string url = "https://" + host + endpoint;
    cpr::Response response = cpr::Post(
        cpr::Url{url},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{payload.dump()},
        cpr::Header{{"Authorization", "Bearer " + token}},
        cpr::Timeout{1000}
    );
    if (response.error) {
        throw std::runtime_error("Network Error: " + response.error.message);
    }
    if (response.status_code != 200) {
        throw std::runtime_error("HTTP Error: " + std::to_string(response.status_code));
    }
    return json::parse(response.text);
}

WorldResponse ServerAPI::get_world() {
    World w = get("/api/world");
    return WorldResponse{w};
}

CommandResponse ServerAPI::send_command(const Command& c) {
    return get("/api/command");
}
