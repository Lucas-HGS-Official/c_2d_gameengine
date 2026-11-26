#pragma once


#define SYSTEM_GET_COMP(world, comp_type, entt_id) \
    world->component_pools_darr[comp_type].get_comp(&world->component_pools_darr[comp_type], entt_id)
