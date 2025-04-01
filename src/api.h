#pragma once
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include "entities.h"

class API {
public:
    virtual ~API() {}

    virtual WorldResponse get_world() = 0;
    virtual CommandResponse send_command(const Command& c) = 0;
};


class LocalAPI : public API {
private:
    World w;
public:
    LocalAPI();

    WorldResponse get_world() override;
    CommandResponse send_command(const Command& c) override;
};

class ServerAPI : public API {
private:
    std::string host;
    std::string token;

    std::shared_ptr<spdlog::logger> logger;

    nlohmann::json get(const std::string& endpoint);
    nlohmann::json post(const std::string& endpoint, const nlohmann::json& payload);
public:
    ServerAPI(const std::string& host, const std::string& token);

    WorldResponse get_world() override;
    CommandResponse send_command(const Command& c) override;
};