#pragma once


#define SYSTEM_GET_COMP(registry, comp_type, entt_id) \
    registry->component_pools[comp_type].get_comp(&registry->component_pools[comp_type], entt_id)
