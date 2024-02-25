#pragma once

#include <handlers/authentication_service.usrv.pb.hpp>
#include <userver/components/component_list.hpp>

namespace sessions_management_service {

namespace {
class SignInHandler final
    : public authentication::AuthenticationBase::Component {
 public:
  static constexpr std::string_view kName = "handler-signin";

  SignInHandler(const userver::components::ComponentConfig& config,
                const userver::components::ComponentContext& component_context)
      : authentication::AuthenticationBase::Component(config,
                                                      component_context) {}

  void SignIn(authentication::AuthenticationBase::SignInCall& call,
              authentication::SignInRequest&& request) final;
};
}  // namespace

void AppendSignIn(userver::components::ComponentList& component_list);

}  // namespace sessions_management_service
