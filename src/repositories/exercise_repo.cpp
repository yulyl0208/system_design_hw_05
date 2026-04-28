#include <userver/storages/postgres/component.hpp>

class ExerciseRepo {
public:
    ExerciseRepo(userver::storages::postgres::ClusterPtr db) : db_(db) {}

    std::string GetAll() {
        auto res = db_->Execute(
            userver::storages::postgres::ClusterHostType::kMaster,
            "SELECT id, name FROM exercises"
        );

        return res.AsSingleRow<std::string>();
    }

private:
    userver::storages::postgres::ClusterPtr db_;
};
