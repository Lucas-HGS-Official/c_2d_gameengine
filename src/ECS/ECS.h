#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "bitmap_macros/bitmap_macros.h"


#define MAX_ENTITY_PER_SYSTEM 200

#define MAX_COMPONENTS 32
#define SIGNATURE_SIZE BITSLOT(MAX_COMPONENTS)

#define MAX_SYSTEMS 32


typedef struct Signature_t {
    char signature[SIGNATURE_SIZE];
} Signature_t;

typedef struct Entities_t {
    int16_t *id_list;
    int16_t length;
    bool is_enttities_initialized;
} Entities_t;

typedef struct System_t {
    Signature_t requirement;
    Entities_t entities;

    bool is_system_initialized;
} System_t;

typedef struct ComponentPool_t {
    void *data;
    int16_t length;

    void (*resize) (struct ComponentPool_t *, int16_t);
    void (*set_comp) (struct ComponentPool_t *, int16_t, void *);
    void *(*get_comp) (struct ComponentPool_t *, int16_t);
    void (*remove_comp) (struct ComponentPool_t *, int16_t);

    bool is_pool_initialized;
} ComponentPool_t;

typedef struct World_t {
    int16_t biggest_entity_id;
    Entities_t entities_to_be_added;
    Entities_t entities_to_be_destroyed;
    Signature_t *entities_components;
    int16_t entities_components_len;

    ComponentPool_t component_pools[MAX_COMPONENTS];
    System_t systems_list[MAX_SYSTEMS];

    bool is_world_initialized;
} World_t;


Entities_t entities_create_entities(void);

System_t system_create_system(int *comp_arr, int comp_arr_len);


World_t *init_world(void);
void destroy_world(World_t *world);

int16_t world_create_entity(World_t *world);

void world_set_component_to_entity(World_t *world, int16_t entt_id, int comp_type, void *comp);
void *world_get_component_of_entity(World_t *world, int16_t entt_id, int comp_type);
void world_remove_component_from_entity(World_t *world, int16_t entt_id, int comp_type);
bool world_entity_has_component(World_t *world, int16_t entt_id, int comp_type);

void world_remove_system(World_t *world, int system_to_remove);
bool world_has_system(World_t *world, int system_to_check);
void world_add_entity_to_systems(World_t *world, int16_t entt_id);
void world_remove_entity_from_systems(World_t *world, int16_t entt_id);
void world_update(World_t *world);
