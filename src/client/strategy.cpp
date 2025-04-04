#include <common/entities.h>

class Strategy {
private:
public:
    Strategy() {}

    Command get_command(const World& world) {
        double pad_center_x = world.pad.position.x + world.pad.size.x / 2;
        Direction d = pad_center_x < world.ball.position.x ? Direction::Right : Direction::Left;
        return Command{.direction = d};
    }
};