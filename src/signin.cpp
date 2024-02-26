#include "signin.hpp"

#include <userver/components/component.hpp>
#include <userver/storages/redis/component.hpp>

namespace sessions_management_service {

namespace {

SignInHandler::SignInHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& component_context)
    : authentication::AuthenticationBase::Component(config, component_context),
      redis_client_{component_context
                        .FindComponent<userver::components::Redis>("redis-db-1")
                        .GetClient("redis_db_1")},
      redis_cc_{std::chrono::seconds{15}, std::chrono::seconds{60}, 4} {}

void SignInHandler::SignIn(authentication::AuthenticationBase::SignInCall& call,
                           authentication::SignInRequest&& request) {
  const auto& login = request.login();
  const auto& password = request.password();

  if (!login.empty() && !password.empty()) {
    authentication::SignInResponse response;
    response.set_session_id("0x0");
    call.Finish(response);
  }
}

}  // namespace

void AppendSignIn(userver::components::ComponentList& component_list) {
  component_list.Append<SignInHandler>();
}

}  // namespace sessions_management_service
