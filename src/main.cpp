#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/storages/redis/component.hpp>
#include <userver/storages/secdist/component.hpp>
#include <userver/storages/secdist/provider_component.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/ugrpc/client/client_factory_component.hpp>
#include <userver/ugrpc/server/server_component.hpp>
#include <userver/utils/daemon_run.hpp>

#include "grpc_server_configurator.hpp"
#include "sessions_management_client.hpp"
#include "sessions_management_service.hpp"

int main(int argc, char* argv[]) {
  auto component_list =
      userver::components::MinimalServerComponentList()
          .Append<userver::server::handlers::Ping>()
          .Append<userver::components::TestsuiteSupport>()
          .Append<userver::components::HttpClient>()
          .Append<userver::clients::dns::Component>()
          .Append<userver::server::handlers::TestsControl>()
          .Append<userver::ugrpc::server::ServerComponent>()
          .Append<userver::ugrpc::client::ClientFactoryComponent>()
          .Append<userver::components::Secdist>()
          .Append<userver::components::DefaultSecdistProvider>()
          .Append<userver::components::Redis>("redis-db-1");

  sessions_management_service::AppendSessionsManagementService(component_list);
  sessions_management_service::AppendSessionsManagementClient(component_list);
  sessions_management_service::AppendGrpcServerConfigurator(component_list);

  return userver::utils::DaemonMain(argc, argv, component_list);
}
