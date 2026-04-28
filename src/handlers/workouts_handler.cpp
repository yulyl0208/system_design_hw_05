class WorkoutsHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-workouts";

    using HttpHandlerBase::HttpHandlerBase;

    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext&) const override {

        auto& redis = GetContext()
            .FindComponent<userver::clients::redis::Component>()
            .GetClient("default");

        RateLimiter limiter(redis);

        std::string user = request.GetArg("user");

        if (!limiter.Allow(user)) {
            request.SetResponseStatus(
                userver::server::http::HttpStatus::kTooManyRequests);
            return "Too Many Requests";
        }

        return "Workout created";
    }
};
