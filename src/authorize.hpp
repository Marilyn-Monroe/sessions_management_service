#pragma once

#include <handlers/authorization_service.usrv.pb.hpp>
#include <userver/components/component_list.hpp>
#include <userver/storages/redis/client.hpp>

namespace sessions_management_service {

namespace {

class AuthorizeHandler final
    : public authorization::AuthorizationBase::Component {
 public:
  static constexpr std::string_view kName = "handler-authorize";

  AuthorizeHandler(
      const userver::components::ComponentConfig& config,
      const userver::components::ComponentContext& component_context);

  void Authorize(authorization::AuthorizationBase::AuthorizeCall& call,
                 authorization::AuthorizationRequest&& request) final;

 private:
  userver::storages::redis::ClientPtr redis_client_;
  userver::storages::redis::CommandControl redis_cc_;
};

}  // namespace

void AppendAuthorize(userver::components::ComponentList& component_list);

}  // namespace sessions_management_service
