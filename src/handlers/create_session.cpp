#include "create_session.hpp"

#include "userver/components/component.hpp"
#include "userver/storages/redis/component.hpp"
#include "userver/utils/uuid4.hpp"

namespace sessions_management_service::handlers {

namespace {

CreateSessionHandler::CreateSessionHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& component_context)
    : ::handlers::api::CreateSessionBase::Component(config, component_context),
      redis_client_{component_context
                        .FindComponent<userver::components::Redis>("redis-db-1")
                        .GetClient("redis_db_1")},
      redis_cc_{std::chrono::seconds{15}, std::chrono::seconds{60}, 4} {}

void CreateSessionHandler::CreateSession(
    ::handlers::api::CreateSessionBase::CreateSessionCall& call,
    ::handlers::api::CreateSessionRequest&& request) {
  ::handlers::api::CreateSessionResponse response;

  const auto& user_id = request.user_id();
  const auto thirty_days = std::chrono::hours{24 * 30};
  auto session_id = userver::utils::generators::GenerateUuid();
  try {
    redis_client_->Set(session_id, user_id, thirty_days, redis_cc_).Get();
    response.set_session_id(session_id);
    call.Finish(response);
  } catch (const userver::redis::RequestFailedException& e) {
    grpc::Status error_status(grpc::StatusCode::UNAVAILABLE, e.what());
    call.FinishWithError(error_status);
  }
}

}  // namespace

void AppendCreateSession(userver::components::ComponentList& component_list) {
  component_list.Append<CreateSessionHandler>();
}

}  // namespace sessions_management_service::handlers
