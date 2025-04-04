#include <string>

#include <spdlog/spdlog.h>
#include <cpr/cpr.h>
#include <argparse/argparse.hpp>

#include <common/replay.h>
#include <client/api.h>
#include <client/strategy.cpp>


int main(int argc, const char** argv) {
    argparse::ArgumentParser program("client");
    program.add_argument("--token").metavar("TOKEN").help("Specify the authentication token");
    program.add_argument("--save-replay").flag();
    program.add_argument("--replay-path").metavar("PATH").default_value<std::string>("replays/last.replay");

    auto &group = program.add_mutually_exclusive_group(true);
    group.add_argument("--local").flag().help("Use LocalAPI (mock)");
    group.add_argument("--server").metavar("HOST").help("Use ServerAPI with specified HOST");        
    
    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        spdlog::error(err.what());
        exit(1);
    }

    bool save_replay = program.get<bool>("--save-replay");

    API* api;
    if (program.get<bool>("--local")) {
        api = new LocalAPI();
        spdlog::info("Using LocalAPI (mock)");
    } else {
        std::string host = program.get<std::string>("--server");
        if (!program.is_used("--token")) {
            spdlog::error("--token argument must be provided, when using ServerAPI");
            exit(1);
        }
        std::string token = program.get<std::string>("--token");

        api = new ServerAPI(host, token);
        spdlog::info("Using ServerAPI on host {}", host);
    }

    Strategy strategy;
    Replay replay = Replay::empty();
    for (int tick = 0; tick < 1000; ++tick) {
        spdlog::info("Tick: {}", tick);
        spdlog::info("Getting state from API");

        World world;
        try {
            WorldResponse r = api->get_world();
            world = r.world;
        } catch (const std::exception& err) {
            spdlog::error(err.what());
            break;
        }

        if (save_replay) {
            replay.add_frame(Frame{world});
        }

        spdlog::info("Strategy calculating response");
        Command command = strategy.get_command(world);

        spdlog::info("Sending response to API");
        try {
            api->send_command(command);
        } catch (const std::exception& err) {
            spdlog::error(err.what());
            break;
        }
    }
    if (save_replay) {
        std::string replay_path = program.get<std::string>("--replay-path");
        try {
            replay.save(replay_path);
            spdlog::info("Replay was saved to {}", replay_path);
        } catch (const std::exception& err) {
            spdlog::error("Replay save failed: {}", err.what());
        }
    }
    return 0;
}