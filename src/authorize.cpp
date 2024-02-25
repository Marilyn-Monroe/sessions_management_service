#include "authorize.hpp"

namespace sessions_management_service {

void AuthorizeHandler::Authorize(authorization::AuthorizationBase::AuthorizeCall& call,
                              authorization::AuthorizationRequest&& request) {
  const auto& session_id = request.session_id();

  authorization::AuthorizationResponse response;
  response.set_success(session_id.empty() ? false : true);
  call.Finish(response);
}

void AppendAuthorize(userver::components::ComponentList& component_list) {
  component_list.Append<AuthorizeHandler>();
}

}  // namespace sessions_management_service
