#pragma once

#include <handlers/check_session_service.usrv.pb.hpp>
#include "userver/components/component_list.hpp"
#include "userver/storages/redis/client.hpp"

namespace sessions_management_service::handlers {

namespace {

class CheckSessionHandler final
    : public ::handlers::api::CheckSessionBase::Component {
 public:
  static constexpr std::string_view kName = "handler-check-session";

  CheckSessionHandler(
      const userver::components::ComponentConfig& config,
      const userver::components::ComponentContext& component_context);

  void CheckSession(::handlers::api::CheckSessionBase::CheckSessionCall& call,
                    ::handlers::api::CheckSessionRequest&& request) final;

 private:
  userver::storages::redis::ClientPtr redis_client_;
  userver::storages::redis::CommandControl redis_cc_;
};

}  // namespace

void AppendCheckSession(userver::components::ComponentList& component_list);

}  // namespace sessions_management_service::handlers
