#include <userver/components/component_list.hpp>
#include <userver/components/run.hpp>

#include <userver/clients/redis/component.hpp>
#include <userver/storages/postgres/component.hpp>

#include "handlers/exercises_handler.cpp"
#include "handlers/workouts_handler.cpp"

int main(int argc, char* argv[]) {
    auto component_list = userver::components::MinimalServerComponentList()
        .Append<userver::clients::redis::Component>()
        .Append<userver::components::Postgres>("postgres-db")
        .Append<ExercisesHandler>()
        .Append<WorkoutsHandler>();

    return userver::components::Run(argc, argv, component_list);
}
