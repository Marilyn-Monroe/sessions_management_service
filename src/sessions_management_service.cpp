#include "sessions_management_service.hpp"

#include "userver/components/component.hpp"
#include "userver/storages/redis/component.hpp"
#include "userver/utils/uuid7.hpp"

namespace sessions_management_service {

namespace {

SessionsManagementService::SessionsManagementService(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& component_context)
    : handlers::api::SessionsManagementServiceBase::Component(
          config, component_context),
      redis_client_{component_context
                        .FindComponent<userver::components::Redis>("redis-db-1")
                        .GetClient("redis_db_1")},
      redis_cc_{std::chrono::seconds{15}, std::chrono::seconds{60}, 4},
      client_(component_context.FindComponent<SessionsManagementClient>()) {}

void SessionsManagementService::CreateSession(
    handlers::api::SessionsManagementServiceBase::CreateSessionCall& call,
    handlers::api::CreateSessionRequest&& request) {
  handlers::api::CreateSessionResponse response;

  auto user_id = request.user_id();

  auto session_id = GenerateSessionID(user_id);
  try {
    const auto thirty_days = std::chrono::hours{24 * 30};
    redis_client_->Set(session_id, user_id, thirty_days, redis_cc_).Get();
    response.set_session_id(session_id);
    call.Finish(response);
  } catch (const userver::redis::RequestFailedException& e) {
    call.FinishWithError(grpc::Status(grpc::StatusCode::UNAVAILABLE, e.what()));
  }
}

void SessionsManagementService::DeleteSession(
    handlers::api::SessionsManagementServiceBase::DeleteSessionCall& call,
    handlers::api::DeleteSessionRequest&& request) {
  handlers::api::DeleteSessionResponse response;

  auto session_id = request.session_id();

  try {
    auto result = redis_client_->Del(session_id, redis_cc_).Get();
    response.set_status(result != 0);
    call.Finish(response);
  } catch (const userver::redis::RequestFailedException& e) {
    call.FinishWithError(grpc::Status(grpc::StatusCode::UNAVAILABLE, e.what()));
  }
}

void SessionsManagementService::CheckSession(
    handlers::api::SessionsManagementServiceBase::CheckSessionCall& call,
    handlers::api::CheckSessionRequest&& request) {
  handlers::api::CheckSessionResponse response;

  auto session_id = request.session_id();

  try {
    auto result = redis_client_->Get(session_id, redis_cc_).Get();
    response.set_status(result ? true : false);
    call.Finish(response);
  } catch (const userver::redis::RequestFailedException& e) {
    call.FinishWithError(grpc::Status(grpc::StatusCode::UNAVAILABLE, e.what()));
  }
}

}  // namespace

std::string GenerateSessionID(std::string_view user_id) {
  auto session_id = userver::utils::generators::GenerateUuidV7();
  return session_id;
}

void AppendSessionsManagementService(
    userver::components::ComponentList& component_list) {
  component_list.Append<SessionsManagementService>();
}

}  // namespace sessions_management_service
