#include "delete_session.hpp"

#include "userver/components/component.hpp"
#include "userver/storages/redis/component.hpp"

namespace sessions_management_service::handlers {

namespace {

DeleteSessionHandler::DeleteSessionHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& component_context)
    : ::handlers::api::DeleteSessionBase::Component(config, component_context),
      redis_client_{component_context
                        .FindComponent<userver::components::Redis>("redis-db-1")
                        .GetClient("redis_db_1")},
      redis_cc_{std::chrono::seconds{15}, std::chrono::seconds{60}, 4} {}

void DeleteSessionHandler::DeleteSession(
    ::handlers::api::DeleteSessionBase::DeleteSessionCall& call,
    ::handlers::api::DeleteSessionRequest&& request) {
  ::handlers::api::DeleteSessionResponse response;

  const auto& session_id = request.session_id();

  try {
    auto result = redis_client_->Del(session_id, redis_cc_).Get();
    response.set_status(result != 0);
    call.Finish(response);
  } catch (const userver::redis::RequestFailedException& e) {
    call.FinishWithError(grpc::Status(grpc::StatusCode::UNAVAILABLE, e.what()));
  }
}

}  // namespace

void AppendDeleteSession(userver::components::ComponentList& component_list) {
  component_list.Append<DeleteSessionHandler>();
}

}  // namespace sessions_management_service::handlers
