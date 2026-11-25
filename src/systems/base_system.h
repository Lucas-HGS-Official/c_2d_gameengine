#pragma once


#define SYSTEM_GET_COMP(world, comp_type, entt_id) \
    world->component_pools[comp_type].get_comp(&world->component_pools[comp_type], entt_id)
