#pragma once

#include <handlers/sessions_management_client.usrv.pb.hpp>
#include "userver/components/component.hpp"
#include "userver/components/component_list.hpp"
#include "userver/components/loggable_component_base.hpp"
#include "userver/ugrpc/client/client_factory_component.hpp"

namespace sessions_management_service {

class SessionsManagementClient final
    : public userver::components::LoggableComponentBase {
 public:
  static constexpr std::string_view kName = "sessions-management-client";

  SessionsManagementClient(
      const userver::components::ComponentConfig& config,
      const userver::components::ComponentContext& component_context);

  std::string CreateSession(std::string user_id);
  bool DeleteSession(std::string session_id);
  bool CheckSession(std::string session_id);

  static userver::yaml_config::Schema GetStaticConfigSchema();

 private:
  userver::ugrpc::client::ClientFactory& client_factory_;
  handlers::api::SessionsManagementServiceClient client_;
};

void AppendSessionsManagementClient(
    userver::components::ComponentList& component_list);

}  // namespace sessions_management_service

template <>
inline constexpr bool userver::components::kHasValidate<
    sessions_management_service::SessionsManagementClient> = true;
