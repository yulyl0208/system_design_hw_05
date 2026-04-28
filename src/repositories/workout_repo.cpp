#include <userver/storages/postgres/cluster.hpp>
#include <userver/formats/json.hpp>

class WorkoutRepo {
public:
    explicit WorkoutRepo(userver::storages::postgres::ClusterPtr db)
        : db_(db) {}

    int CreateWorkout(int user_id) {
        auto res = db_->Execute(
            userver::storages::postgres::ClusterHostType::kMaster,
            "INSERT INTO workouts(user_id) VALUES($1) RETURNING id",
            user_id
        );

        return res.AsSingleRow<int>();
    }

   void AddExercise(int workout_id, int exercise_id, int reps) {
        db_->Execute(
            userver::storages::postgres::ClusterHostType::kMaster,
            "INSERT INTO workout_exercises(workout_id, exercise_id, reps) "
            "VALUES($1, $2, $3)",
            workout_id, exercise_id, reps
        );
    }

    userver::formats::json::Value GetHistory(int user_id) {
        auto res = db_->Execute(
            userver::storages::postgres::ClusterHostType::kMaster,
            R"(
            SELECT w.id, w.created_at
            FROM workouts w
            WHERE w.user_id = $1
            ORDER BY w.created_at DESC
            )",
            user_id
        );

        userver::formats::json::ValueBuilder builder;

        for (const auto& row : res) {
            builder.PushBack({
                {"id", row["id"].As<int>()},
                {"created_at", row["created_at"].As<std::string>()}
            });
        }

        return builder.ExtractValue();
    }

    userver::formats::json::Value GetStats(int user_id) {
        auto res = db_->Execute(
            userver::storages::postgres::ClusterHostType::kMaster,
            R"(
            SELECT 
                COUNT(DISTINCT w.id) as total_workouts,
                SUM(we.reps) as total_reps
            FROM workouts w
            JOIN workout_exercises we ON w.id = we.workout_id
            WHERE w.user_id = $1
            )",
            user_id
        );

        const auto row = res.Front();

        userver::formats::json::ValueBuilder builder;
        builder["total_workouts"] = row["total_workouts"].As<int>(0);
        builder["total_reps"] = row["total_reps"].As<int>(0);

        return builder.ExtractValue();
    }

private:
    userver::storages::postgres::ClusterPtr db_;
};
