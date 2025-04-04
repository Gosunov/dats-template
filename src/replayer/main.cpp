#include <common/vec2.h>
#include <common/replay.h>
#include <common/entities.h>

#include <rewind_viewer/colors.h>
#include <rewind_viewer/plot.h>
#include <rewind_viewer/rewind_client.h>

#include <spdlog/spdlog.h>

using namespace rewind_viewer::colors;
using namespace std::chrono_literals;

int main_(int argc, char *argv[]) {
    // Should be just 1 instance.
    // Pass it via reference, shared_ptr ot create singleton to access it.
    // Assume rewind viewer is started on the same host with default port.
    rewind_viewer::RewindClient rc("127.0.0.1", 9111);

    rc.start_proto();
    rc.end_proto();

    Replay replay = Replay::from_file("replays/last.replay");
    for (Frame frame : replay.frames) {
        World world = frame.world;
        for (Brick brick : world.bricks) {
            rc.rectangle(brick.position, brick.size, 0x4444AA, true);
        }
        rc.rectangle(world.pad.position, world.pad.size, 0xAA4444, true);
        rc.circle(world.ball.position, world.ball.radius, 0x44AAAA, true);
        rc.end_frame();
    }
    return 0;
}

int main(int argc, char *argv[]) {
    try {
        main_(argc, argv);
    } catch (const std::exception& err) {
        spdlog::error("Replayer failed: {}", err.what());
    }
}