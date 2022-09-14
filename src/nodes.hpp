//
// Created by yarik on 13.09.22.
//

#pragma once

#include <string>
#include <string_view>
#include <userver/components/component_list.hpp>

namespace yet_another_disk {

std::string GetNode(std::string name);

void AppendNodes(userver::components::ComponentList& component_list);
}