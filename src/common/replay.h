#include <vector>
#include <nlohmann/json.hpp>

#include <common/entities.h>

struct Frame {
    World world;
};

void to_json(nlohmann::json& j, const Frame& f);
void from_json(const nlohmann::json& j, Frame& f);

class Replay {
public:
    std::vector<Frame> frames;

    Replay(std::vector<Frame> frames);

    static Replay from_file(const std::string& path);
    static Replay empty();

    void add_frame(const Frame f);
    void save(const std::string& path);
};