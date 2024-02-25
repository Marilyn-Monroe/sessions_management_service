#include "signin.hpp"

namespace sessions_management_service {

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

void AppendSignIn(userver::components::ComponentList& component_list) {
  component_list.Append<SignInHandler>();
}

}  // namespace sessions_management_service
