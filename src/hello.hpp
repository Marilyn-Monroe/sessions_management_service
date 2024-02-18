#pragma once

#include <string>
#include <string_view>

#include <userver/components/component_list.hpp>

namespace sessions_management_service {

std::string SayHelloTo(std::string_view name);

void AppendHello(userver::components::ComponentList &component_list);

} // namespace sessions_management_service
