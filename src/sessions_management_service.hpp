#pragma once

#include "sessions_management_client.hpp"

#include <handlers/sessions_management_service.usrv.pb.hpp>
#include "userver/components/component_list.hpp"
#include "userver/storages/redis/client.hpp"

namespace sessions_management_service {

namespace {

class SessionsManagementService final
    : public handlers::api::SessionsManagementServiceBase::Component {
 public:
  static constexpr std::string_view kName = "sessions-management-service";

  SessionsManagementService(
      const userver::components::ComponentConfig& config,
      const userver::components::ComponentContext& component_context);

  void CreateSession(
      handlers::api::SessionsManagementServiceBase::CreateSessionCall& call,
      handlers::api::CreateSessionRequest&& request) final;

  void DeleteSession(
      handlers::api::SessionsManagementServiceBase::DeleteSessionCall& call,
      handlers::api::DeleteSessionRequest&& request) final;

  void CheckSession(
      handlers::api::SessionsManagementServiceBase::CheckSessionCall& call,
      handlers::api::CheckSessionRequest&& request) final;

 private:
  userver::storages::redis::ClientPtr redis_client_;
  userver::storages::redis::CommandControl redis_cc_;
  SessionsManagementClient& client_;
};

}  // namespace

std::string GenerateSessionID(std::string_view user_id);

void AppendSessionsManagementService(
    userver::components::ComponentList& component_list);

}  // namespace sessions_management_service
