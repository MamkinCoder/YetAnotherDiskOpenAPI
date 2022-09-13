//
// Created by yarik on 13.09.22.
//

#include "nodes.hpp"

#include <fmt/format.h>

#include <string>
#include <iostream>
#include <userver/clients/dns/component.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/io/row_types.hpp>

#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>

namespace yet_another_disk {

struct item{
  std::string id;
  std::string url;
  std::optional<std::string> parentId;
  int size;
  std::string type;
};

namespace {

class Nodes final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-nodes";

  Nodes(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context)
      : HttpHandlerBase(config, component_context),
        pg_cluster_(
            component_context
                .FindComponent<userver::components::Postgres>("postgres-db-1")
                .GetCluster()) {}

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
    const auto& id = request.GetArg("id");


//    if (!id.empty()) {
      auto result = pg_cluster_->Execute(
          userver::storages::postgres::ClusterHostType::kMaster,
          "SELECT * FROM file_schema.items WHERE id=$1",
          id);

//    }

    using MyRowType = std::tuple<std::string, std::string>;
    auto iteration = result.AsSetOf<yet_another_disk::item>(userver::storages::postgres::kRowTag);

    std::string json = R"({ "id": )";
    //бессмысленный цикл for
    for(auto row : iteration){
      json += row.id;
      json += R"(, "url": )";
      json += row.url;
      json += R"(, "parentId": )";
      if (row.parentId.has_value())
      {
        json += row.parentId.value();
      }
      else {
        json  += "null";
      }
      json += R"(, "size": )";
      json += std::to_string(row.size);
      json += R"( })";
    }


    return yet_another_disk::GetNode(json);
  }

  userver::storages::postgres::ClusterPtr pg_cluster_;
};

}  // namespace

std::string GetNode(std::string name) {

  return name;

  UASSERT(false);
}

void AppendNodes(userver::components::ComponentList& component_list) {
  component_list.Append<Nodes>();
}

}  // namespace YetAnotherDiskOpenAPI
