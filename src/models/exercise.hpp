#pragma once

#include <string>
#include <userver/formats/json/value_builder.hpp>
#include <userver/formats/json/value.hpp>

struct Exercise {
    int id;
    std::string name;
};

inline userver::formats::json::Value ToJson(const Exercise& ex) {
    userver::formats::json::ValueBuilder builder;

    builder["id"] = ex.id;
    builder["name"] = ex.name;

    return builder.ExtractValue();
}


inline Exercise FromJson(const userver::formats::json::Value& json) {
    Exercise ex;
    ex.id = json["id"].As<int>();
    ex.name = json["name"].As<std::string>();
    return ex;
}
