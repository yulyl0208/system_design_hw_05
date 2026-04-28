#pragma once

#include <vector>
#include <string>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/json/value.hpp>

struct WorkoutExercise {
    int exercise_id;
    int reps;
};

struct Workout {
    int id;
    int user_id;
    std::string created_at;
    std::vector<WorkoutExercise> exercises;
};


inline userver::formats::json::Value ToJson(const WorkoutExercise& we) {
    userver::formats::json::ValueBuilder builder;

    builder["exercise_id"] = we.exercise_id;
    builder["reps"] = we.reps;

    return builder.ExtractValue();
}


inline userver::formats::json::Value ToJson(const Workout& w) {
    userver::formats::json::ValueBuilder builder;

    builder["id"] = w.id;
    builder["user_id"] = w.user_id;
    builder["created_at"] = w.created_at;

    userver::formats::json::ValueBuilder exercises_builder;

    for (const auto& ex : w.exercises) {
        exercises_builder.PushBack(ToJson(ex));
    }

    builder["exercises"] = exercises_builder.ExtractValue();

    return builder.ExtractValue();
}


inline Workout FromJson(const userver::formats::json::Value& json) {
    Workout w;

    w.user_id = json["user_id"].As<int>();

    for (const auto& item : json["exercises"]) {
        WorkoutExercise we;
        we.exercise_id = item["exercise_id"].As<int>();
        we.reps = item["reps"].As<int>();
        w.exercises.push_back(we);
    }

    return w;
}
