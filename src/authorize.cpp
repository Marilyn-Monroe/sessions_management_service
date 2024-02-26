#include "authorize.hpp"

#include <userver/components/component.hpp>
#include <userver/storages/redis/component.hpp>

namespace sessions_management_service {

namespace {

AuthorizeHandler::AuthorizeHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& component_context)
    : authorization::AuthorizationBase::Component(config, component_context),
      redis_client_{component_context
                        .FindComponent<userver::components::Redis>("redis-db-1")
                        .GetClient("redis_db_1")},
      redis_cc_{std::chrono::seconds{15}, std::chrono::seconds{60}, 4} {}

void AuthorizeHandler::Authorize(
    authorization::AuthorizationBase::AuthorizeCall& call,
    authorization::AuthorizationRequest&& request) {
  const auto& session_id = request.session_id();

  authorization::AuthorizationResponse response;
  response.set_success(session_id.empty() ? false : true);
  call.Finish(response);
}

}  // namespace

void AppendAuthorize(userver::components::ComponentList& component_list) {
  component_list.Append<AuthorizeHandler>();
}

}  // namespace sessions_management_service
