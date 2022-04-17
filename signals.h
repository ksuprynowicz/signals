#pragma once

#include <vector>
#include <deque>
#include <string>

typedef enum {
    SIGNAL_LIGHT_MAIN,
    SIGNAL_LIGHT_PRE,
    SIGNAL_LIGHT_DWARF,
    SIGNAL_SHAPE_DISC
} SignalType_t;

typedef enum {
    SIGNAL_ST_LIGHT_RED,
    SIGNAL_ST_LIGHT_YELLOW,
    SIGNAL_ST_LIGHT_YELLOW_GREEN,
    SIGNAL_ST_LIGHT_GREEN,
    SIGNAL_ST_LIGHT_DWARF_STOP,
    SIGNAL_ST_LIGHT_DWARF_FREE,
    SIGNAL_ST_LIGHT_DWARF_FREE_NX_STOP,
    SIGNAL_ST_DISC_STOP,
    SIGNAL_ST_DISC_GO
} SignalState_t;

typedef struct Signal {
    SignalType_t signal_type;
    SignalState_t signal_state;
    int block_idx;
} Signal_t;

typedef enum {
    SWITCH_ST_FORWARD,
    SWITCH_ST_TURN
} SwitchState_t;

typedef struct SwitchRoute {
    int input;
    int output_forward;
    int output_turn;
} SwitchRoute_t;

typedef struct Switch {
    SwitchState_t state;
    const vector<SwitchRoute_t> *routes;
    int block_idx;
} Switch_t;

typedef enum {
    MAGNET_ST_ON,
    MAGNET_ST_OFF
} MagnetState_t;

typedef enum {
    MAGNET_EV_ON,
    MAGNET_EV_OFF
} MagnetEvent_t;

typedef struct Magnet {
    MagnetState_t state;
    int block_idx;
} Magnet_t;

typedef enum {
    BLOCK_SHAPE_DRAIN_1,
    BLOCK_SHAPE_1L_1R,
    BLOCK_SHAPE_2L_1R,
    BLOCK_SHAPE_2L_2R,
    BLOCK_SHAPE_1L_2R,
    BLOCK_SHAPE_2L_3R,
    BLOCK_SHAPE_3L_2R
} BlockShape_t;

typedef enum {
    BLOCK_DIR_TO_RIGHT,
    BLOCK_DIR_TO_LEFT
} BlockDirection_t;

typedef enum {
    BLOCK_ST_OCCUPIED,
    BLOCK_ST_FREE
} BlockState_t;

typedef struct Block {
    std::vector<int> signalIndices;
    std::vector<int> switchIndices;
    std::vector<int> mangetIndices;
    std::vector<int> sharedBlocksIndices; // Blocks that share space with a given block
    std::vector<int> connectedBlocksIndices;
    BlockState_t blockState;
    BlockShape_t blockShape;
    BlockDirection_t blockDirection;
} Block_t;

/*typedef enum {
    ROUTE_ST_OCCUPIED,
    ROUTE_ST_FREE
} RouteState_t;*/

typedef struct Route {
    std::vector<int> blockIndices;
    bool is_reserved;
    bool is_occupied;
} Route_t;

typedef enum {
    INPUT_EVENT_MAGNET_ON,
    INPUT_EVENT_MAGNET_OFF,
    INPUT_EVENT_SWITCH_FORWARD,
    INPUT_EVENT_SWITCH_TURN
//    INPUT_EVENT_ROUTE_ON,
//    INPUT_EVENT_ROUTE_OFF
} InputEventType_t;

typedef struct InputEvent {
    int event_entity_idx;
} InputEvent_t;

typedef enum {
    OUTPUT_EVENT_T_SIGNAL_CHANGE_STATE //new state to be set is stored in out_event_data
} OutputEventType_t;

typedef struct OutputEvent {
    int event_entity_idx;
    int out_event_data;
} OutputEvent_t;

typedef struct RailoradState {
    std::vector<Signal_t> signals;
    std::vector<Switch_t> switches;
    std::vector<Magnet_t> magnets;
    std::vector<Block_t> blocks;
    std::vector<Route_t> routes;

    std::deque<InputEvent_t> inputEvents;
    std::deque<OutputEvent_t> outputEvents;
} RailroadState_t;


int add_signal(RailroadState_t &rS, SignalType_t signal_type, int block_idx);

int add_switch(RailroadState_t &rS, int block_idx);

int add_magnet(RailroadState_t &rS, int block_idx);

void add_input_event(RailroadState_t &rS, InputEvent_t &event);
void add_output_event(RailroadState_t &rS, OutputEvent_t &event);

bool process_input_event(RailroadState_t &rS);
bool process_output_event(RailroadState_t &rS);

bool reserve_route(RailroadState_t &rS, int route_idx);
bool free_route(RailroadState_t &rS, int route_idx);

void reserve_block(RailroadState_t &rS, int block_idx);
void free_block(RailroadState_t &rS, int block_idx);

void occupy_block(RailroadState_t &rS, int block_idx);
void leave_block(RailroadState_t &rS, int block_idx);

void create_example_track(RailroadState_t &rS);
void load_track_from_file(RailroadState_t &rS, std::string filename);
int add_block(RailroadState_t &rS, BlockShape_t shape, BlockDirection_t direction);
void make_blocks_shared(RailroadState_t &rS, int index_1, int index_2);
void connect_blocks(RailroadState_t &rS, int index_1, int slot_1, int index_2, int slot_2);

//Default routing models for different kind of blocks:

//BLOCK_SHAPE_2L_1R
//Left to right
//Switch not used

//Right to left
extern vector<SwitchRoute_t> sw_route_2L_1R_RtL;

//BLOCK_SHAPE_2L_2R
//Left to right
extern vector<SwitchRoute_t> sw_route_2L_2R_LtR;

//Right to left
extern vector<SwitchRoute_t> sw_route_2L_2R_RtL;

//BLOCK_SHAPE_1L_2R
//Left to right
extern vector<SwitchRoute_t> sw_route_1L_2R_LtR;

//Right to left
//Switch not used

//BLOCK_SHAPE_2L_3R
//Left to right
//TODO

//Right to left
//TODO

//BLOCK_SHAPE_3L_2R
//Left to right
//TODO

//Right to left
//TODO
