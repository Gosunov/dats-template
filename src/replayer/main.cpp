#include "common/entities.h"
#include <random>

#include <common/vec2.h>
#include <common/replay.h>

#include <rewind_viewer/colors.h>
#include <rewind_viewer/plot.h>
#include <rewind_viewer/rewind_client.h>

#include <spdlog/spdlog.h>

using namespace rewind_viewer::colors;
using namespace std::chrono_literals;

void draw_pattern(rewind_viewer::RewindClient &rc, const Vec2 &pos, int i) {
    rc.mask_circle(Vec2{pos.x + 15.0, pos.y + 75.0}, 6.0);
    rc.mask_circle_segment(Vec2{pos.x + 15.0, pos.y + 61.0}, 6.0, 2.443, 3.84);
    rc.mask_circle_segment(Vec2{pos.x + 15.0, pos.y + 61.0}, 6.0, -1.745, 1.745);
    rc.mask_arc(Vec2{pos.x + 15.0, pos.y + 47.0}, 6.0, 2.443, 3.84);
    rc.mask_arc(Vec2{pos.x + 15.0, pos.y + 47.0}, 6.0, -1.745, 1.745);

    rc.mask_triangle(Vec2{pos.x + 25.0, pos.y + 40.0},
                                     Vec2{pos.x + 35.0, pos.y + 20.0},
                                     Vec2{pos.x + 15.0, pos.y + 20.0});
    rc.mask_rectangle(Vec2{pos.x + 35.0, pos.y + 45.0}, Vec2{20.0, 20.0});

    rc.circle(Vec2{pos.x + 25.0, pos.y + 50.0}, 20.0, purple::Magenta, true);
    rc.arc(Vec2{pos.x + 50.0, pos.y + 12.0}, 6.0, 2.443, 3.84, purple::Magenta,
                 true);
    rc.arc(Vec2{pos.x + 50.0, pos.y + 12.0}, 6.0, -1.745, 1.745, purple::Magenta,
                 true);
    rc.circle_segment(Vec2{pos.x + 50.0, pos.y + 88.0}, 6.0, 2.443, 3.84,
                                        purple::Magenta, true);
    rc.circle_segment(Vec2{pos.x + 50.0, pos.y + 88.0}, 6.0, -1.745, 1.745,
                                        purple::Magenta, true);

    rc.circle(Vec2{pos.x + 75.0, pos.y + 50.0}, 20.0, purple::Magenta);
    rc.arc(Vec2{pos.x + 75.0, pos.y + 50.0}, 17.5, 2.443, 3.84, purple::Magenta);
    rc.arc(Vec2{pos.x + 75.0, pos.y + 50.0}, 17.5, -1.745, 1.745,
                 purple::Magenta);
    rc.circle_segment(Vec2{pos.x + 75.0, pos.y + 50.0}, 15.0, 2.443, 3.84,
                                        purple::Magenta);
    rc.circle_segment(Vec2{pos.x + 75.0, pos.y + 50.0}, 15.0, -1.745, 1.745,
                                        purple::Magenta);

    // Not supported for permanent frames
    if (i >= 0) {
        rc.popup_round(Vec2{pos.x + 75.0, pos.y + 50.0}, 20.0, "Round popup #%d",
                                     i);
    }
    rc.triangle(Vec2{pos.x + 25.0, pos.y + 50.0},
                            Vec2{pos.x + 45.0, pos.y + 15.0}, Vec2{pos.x + 5.0, pos.y + 15.0},
                            blue::Cyan, true);
    rc.triangle(Vec2{pos.x + 75.0, pos.y + 50.0},
                            Vec2{pos.x + 95.0, pos.y + 15.0},
                            Vec2{pos.x + 55.0, pos.y + 15.0}, blue::Cyan);
    rc.rectangle(Vec2{pos.x + 10.0, pos.y + 40.0}, Vec2{20.0, 40.0},
                             yellow::Yellow, true);
    rc.rectangle(Vec2{pos.x + 60.0, pos.y + 40.0}, Vec2{20.0, 40.0},
                             yellow::Yellow);

    // Not supported for permanent frames
    if (i >= 0) {
        rc.popup(Vec2{pos.x + 60.0, pos.y + 40.0}, Vec2{20.0, 40.0},
                         "Rectangular popup #%d", i);
    }

    rc.line(Vec2{pos.x + 5.0, pos.y + 5.0}, Vec2{pos.x + 95.0, pos.y + 95.0},
                    green::Green);
    rc.polyline<Vec2>(
            {Vec2{pos.x + 5.0, pos.y + 95.0}, Vec2{pos.x + 40.0, pos.y + 80.0},
             Vec2{pos.x + 60.0, pos.y + 20.0}, Vec2{pos.x + 95.0, pos.y + 5.0}},
            red::Crimson);
}

void draw_HUD(rewind_viewer::RewindClient &rc) {
    Vec2 zero;
    Vec2 text_pos_1{-40.0, 50.0};
    Vec2 text_pos_2{-40.0, 0.0};

    rc.set_layer(0, true, rewind_viewer::LayerOrigin::left_top);
    rc.circle(zero, 50, red::Crimson, true);
    rc.text(text_pos_1, 20.0, 0xFFFFFF00, "\U0001F434❤");
    rc.text(text_pos_2, 20.0, 0xFFFFFF00, "❤\U0001F984");
    rc.set_layer(1, true, rewind_viewer::LayerOrigin::left_center);
    rc.circle(zero, 50, pink::HotPink, true);
    rc.text(text_pos_1, 20.0, 0xFFFFFF00, "\U0001F434❤");
    rc.text(text_pos_2, 20.0, 0xFFFFFF00, "❤\U0001F984");
    rc.set_layer(2, true, rewind_viewer::LayerOrigin::left_bottom);
    rc.circle(zero, 50, orange::Tomato, true);
    rc.text(text_pos_1, 20.0, 0xFFFFFF00, "\U0001F434❤");
    rc.text(text_pos_2, 20.0, 0xFFFFFF00, "❤\U0001F984");
    rc.set_layer(3, true, rewind_viewer::LayerOrigin::right_top);
    rc.circle(zero, 50, yellow::Gold, true);
    rc.text(text_pos_1, 20.0, 0xFFFFFF00, "\U0001F434❤");
    rc.text(text_pos_2, 20.0, 0xFFFFFF00, "❤\U0001F984");
    rc.set_layer(4, true, rewind_viewer::LayerOrigin::right_center);
    rc.circle(zero, 50, purple::Orchid, true);
    rc.text(text_pos_1, 20.0, 0xFFFFFF00, "\U0001F434❤");
    rc.text(text_pos_2, 20.0, 0xFFFFFF00, "❤\U0001F984");
    rc.set_layer(5, true, rewind_viewer::LayerOrigin::right_bottom);
    rc.circle(zero, 50, green::LimeGreen, true);
    rc.text(text_pos_1, 20.0, 0xFFFFFF00, "\U0001F434❤");
    rc.text(text_pos_2, 20.0, 0xFFFFFF00, "❤\U0001F984");
    rc.set_layer(6, true, rewind_viewer::LayerOrigin::top_center);
    rc.circle(zero, 50, blue::SkyBlue, true);
    rc.text(text_pos_1, 20.0, 0xFFFFFF00, "\U0001F434❤");
    rc.text(text_pos_2, 20.0, 0xFFFFFF00, "❤\U0001F984");
    rc.set_layer(7, true, rewind_viewer::LayerOrigin::bottom_center);
    rc.circle(zero, 50, brown::Chocolate, true);
    rc.text(text_pos_1, 20.0, 0xFFFFFF00, "\U0001F434❤");
    rc.text(text_pos_2, 20.0, 0xFFFFFF00, "❤\U0001F984");
}

void draw_field(rewind_viewer::RewindClient &rc, Vec2 &map_size) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(0, 23);

    std::vector<uint32_t> field_colors;

    Vec2 cell_size{5.0, 10.0};
    Vec2 start_pos{0.0, 0.0};
    Vec2 pos = start_pos;
    uint16_t row_size = static_cast<uint16_t>(map_size.x / cell_size.x);
    while (pos.y < map_size.y) {
        pos.x = start_pos.x;
        while (pos.x < map_size.x) {
            uint32_t color = 127;
            if (pos.x < map_size.x * 0.5 || distrib(gen) != 4) {
                color |= static_cast<uint32_t>(255.0 * (pos.y / map_size.y)) << 24;
            }
            color |= static_cast<uint32_t>(255.0 * (pos.y / map_size.y)) << 8;
            color |= static_cast<uint32_t>(255.0 * (pos.x / map_size.x)) << 16;
            field_colors.push_back(color);
            pos.x += cell_size.x;
        }
        pos.y += cell_size.y;
    }
    rc.tiles(start_pos, cell_size, row_size, &field_colors, false);
}

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