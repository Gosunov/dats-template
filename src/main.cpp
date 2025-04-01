#include <spdlog/spdlog.h>
#include <cpr/cpr.h>
#include <argparse/argparse.hpp>

#include "api.h"
#include "strategy.cpp"

int main(int argc, const char** argv) {
    argparse::ArgumentParser program("datscity-client");
    program.add_argument("--token").metavar("TOKEN").help("Specify the authentication token");

    auto &group = program.add_mutually_exclusive_group(true);
    group.add_argument("--local").flag().help("Use LocalAPI (mock)");
    group.add_argument("--server").metavar("HOST").help("Use ServerAPI with specified HOST");        
    
    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        spdlog::error(err.what());
        exit(1);
    }

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
    for (int tick = 0; tick < 10; ++tick) {
        spdlog::info("Tick: {}", tick);
        World world;
        try {
            spdlog::info("Getting state from API");
            WorldResponse r = api->get_world();
            world = r.world;
        } catch (const std::exception& err) {
            spdlog::error(err.what());
            exit(1);
        }

        spdlog::info("Strategy calculating response");
        Command command = strategy.get_command(world);

        spdlog::info("Sendind response to API");
        api->send_command(command);
    }
    return 0;
}