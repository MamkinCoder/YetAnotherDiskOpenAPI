#pragma once

#include <string>
#include <string_view>

#include <userver/components/component_list.hpp>

namespace yet_another_disk {

enum class UserType { kFirstTime, kKnown };
std::string SayHelloTo(std::string_view name, UserType type);

void AppendHello(userver::components::ComponentList& component_list);

}  // namespace pg_service_template
