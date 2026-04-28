#include <userver/server/handlers/http_handler_base.hpp>

class ExercisesHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-exercises";

    using HttpHandlerBase::HttpHandlerBase;

    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext&) const override {

        auto& redis = GetContext().FindComponent<userver::clients::redis::Component>()
            .GetClient("default");

        CacheService cache(redis);

        auto cached = cache.Get("exercises");
        if (cached) return *cached;

        std::string data = R"([{"id":1,"name":"pushups"}])";

        cache.Set("exercises", data, 600);

        return data;
    }
};
