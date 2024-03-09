#pragma once

#include <handlers/create_session_service.usrv.pb.hpp>
#include "userver/components/component_list.hpp"
#include "userver/storages/redis/client.hpp"

namespace sessions_management_service::handlers {

namespace {

class CreateSessionHandler final
    : public ::handlers::api::CreateSessionBase::Component {
 public:
  static constexpr std::string_view kName = "handler-create-session";

  CreateSessionHandler(
      const userver::components::ComponentConfig& config,
      const userver::components::ComponentContext& component_context);

  void CreateSession(
      ::handlers::api::CreateSessionBase::CreateSessionCall& call,
      ::handlers::api::CreateSessionRequest&& request) final;

 private:
  userver::storages::redis::ClientPtr redis_client_;
  userver::storages::redis::CommandControl redis_cc_;
};

}  // namespace

void AppendCreateSession(userver::components::ComponentList& component_list);

}  // namespace sessions_management_service::handlers
