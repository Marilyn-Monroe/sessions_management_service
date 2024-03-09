#include "check_session.hpp"

#include "userver/components/component.hpp"
#include "userver/storages/redis/component.hpp"

namespace sessions_management_service::handlers {

namespace {

CheckSessionHandler::CheckSessionHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& component_context)
    : ::handlers::api::CheckSessionBase::Component(config, component_context),
      redis_client_{component_context
                        .FindComponent<userver::components::Redis>("redis-db-1")
                        .GetClient("redis_db_1")},
      redis_cc_{std::chrono::seconds{15}, std::chrono::seconds{60}, 4} {}

void CheckSessionHandler::CheckSession(
    ::handlers::api::CheckSessionBase::CheckSessionCall& call,
    ::handlers::api::CheckSessionRequest&& request) {
  ::handlers::api::CheckSessionResponse response;

  const auto& session_id = request.session_id();

  try {
    auto result = redis_client_->Get(session_id, redis_cc_).Get();
    response.set_status(result ? true : false);
    call.Finish(response);
  } catch (const userver::redis::RequestFailedException& e) {
    grpc::Status error_status(grpc::StatusCode::UNAVAILABLE, e.what());
    call.FinishWithError(error_status);
  }
}

}  // namespace

void AppendCheckSession(userver::components::ComponentList& component_list) {
  component_list.Append<CheckSessionHandler>();
}

}  // namespace sessions_management_service::handlers
