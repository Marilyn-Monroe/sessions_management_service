#pragma once

#include <handlers/delete_session_service.usrv.pb.hpp>
#include "userver/components/component_list.hpp"
#include "userver/storages/redis/client.hpp"

namespace sessions_management_service::handlers {

namespace {

class DeleteSessionHandler final
    : public ::handlers::api::DeleteSessionBase::Component {
 public:
  static constexpr std::string_view kName = "handler-delete-session";

  DeleteSessionHandler(
      const userver::components::ComponentConfig& config,
      const userver::components::ComponentContext& component_context);

  void DeleteSession(
      ::handlers::api::DeleteSessionBase::DeleteSessionCall& call,
      ::handlers::api::DeleteSessionRequest&& request) final;

 private:
  userver::storages::redis::ClientPtr redis_client_;
  userver::storages::redis::CommandControl redis_cc_;
};

}  // namespace

void AppendDeleteSession(userver::components::ComponentList& component_list);

}  // namespace sessions_management_service::handlers
