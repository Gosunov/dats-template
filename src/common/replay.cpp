#include <vector>
#include <fstream>
#include <filesystem>

#include <common/replay.h>
#include <common/entities.h>

using json = nlohmann::json;
namespace fs = std::filesystem;

void to_json(json& j, const Frame& f) {
    j = json{
        {"world", f.world},
    };
}

void from_json(const json& j, Frame& f) {
    f.world = j["world"];
}

Replay::Replay(std::vector<Frame> frames) : frames(std::move(frames)) {}

Replay Replay::from_file(const std::string &path) {
    std::ifstream file(path);

    // Check if file is open
    if (!file.is_open()) {
        throw;
    }

    json j;
    file >> j;
    return Replay(j);
}

Replay Replay::empty() {
    return Replay({});
}

void Replay::add_frame(const Frame f) {
    frames.push_back(f);
}

void Replay::save(const std::string &path) {
    fs::path dir = fs::path(path).parent_path();
    if (!fs::exists(dir)) {
        if (!fs::create_directories(dir)) {
            throw std::runtime_error("Failed to create directory: " + dir.string());
        }
    }
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open: " + path);
    }
    json j = frames;
    file << j.dump();
}