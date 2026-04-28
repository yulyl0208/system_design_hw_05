#pragma once
#include <userver/clients/redis/client.hpp>

class RateLimiter {
public:
    RateLimiter(userver::clients::redis::ClientPtr redis)
        : redis_(redis) {}

    bool Allow(const std::string& user) {
        std::string key = "rate:" + user;

        auto val = redis_->Incr(key);

        if (val == 1) {
            redis_->Expire(key, std::chrono::seconds(60));
        }

        return val <= 50;
    }

private:
    userver::clients::redis::ClientPtr redis_;
};
