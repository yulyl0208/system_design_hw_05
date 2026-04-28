#pragma once
#include <userver/clients/redis/client.hpp>

class CacheService {
public:
    CacheService(userver::clients::redis::ClientPtr redis)
        : redis_(redis) {}

    std::optional<std::string> Get(const std::string& key) {
        auto result = redis_->Get(key);
        if (result) return result.value();
        return std::nullopt;
    }

    void Set(const std::string& key, const std::string& value, int ttl) {
        redis_->Set(key, value, std::chrono::seconds(ttl));
    }

    void Invalidate(const std::string& key) {
        redis_->Del(key);
    }

private:
    userver::clients::redis::ClientPtr redis_;
};
