#include "signals.h"

#include <iostream>

bool are_switch_routing_models_initialized = false;

using namespace std;

void init_railroad_state(RailroadState_t &rS){
    rS.shutdown = false;
}

void create_example_track(RailroadState_t &rS){
    int L4 = add_block(rS, "L4", BLOCK_SHAPE_SINK_1, BLOCK_DIR_TO_LEFT);
    int L3 = add_block(rS, "L3", BLOCK_SHAPE_SOURCE_1, BLOCK_DIR_TO_LEFT);
    connect_blocks(rS, L3, 0, L4, 0);

    int L10 = add_block(rS, "L10", BLOCK_SHAPE_SINK_1, BLOCK_DIR_TO_LEFT);
    int L9 = add_block(rS, "L9", BLOCK_SHAPE_1L_1R, BLOCK_DIR_TO_LEFT);
    connect_blocks(rS, L10, 0, L9, 0);
    int L8 = add_block(rS, "L8", BLOCK_SHAPE_1L_1R, BLOCK_DIR_TO_LEFT);
    connect_blocks(rS, L9, 1, L8, 0);
    int LY7 = add_block(rS, "LY7", BLOCK_SHAPE_1L_2R, BLOCK_DIR_TO_LEFT);
    connect_blocks(rS, L8, 1, LY7, 0);
    int LY13 = add_block(rS, "LY13", BLOCK_SHAPE_2L_1R, BLOCK_DIR_TO_LEFT);
    connect_blocks(rS, LY7, 1, LY13, 0);
    connect_blocks(rS, LY7, 2, LY13, 1);
    int L12 = add_block(rS, "L12", BLOCK_SHAPE_1L_1R, BLOCK_DIR_TO_LEFT);
    connect_blocks(rS, LY13, 2, L12, 0);
    int L11 = add_block(rS, "L11", BLOCK_SHAPE_SOURCE_1, BLOCK_DIR_TO_LEFT);
    connect_blocks(rS, L12, 1, L11, 0);

    int L14 = add_block(rS, "L14", BLOCK_SHAPE_SINK_1, BLOCK_DIR_TO_LEFT);
    int L15 = add_block(rS, "L15", BLOCK_SHAPE_SOURCE_1, BLOCK_DIR_TO_LEFT);
    connect_blocks(rS, L14, 0, L15, 0);


    int R2 = add_block(rS, "R2", BLOCK_SHAPE_SOURCE_1, BLOCK_DIR_TO_RIGHT);
    int R3 = add_block(rS, "R3", BLOCK_SHAPE_SOURCE_1, BLOCK_DIR_TO_RIGHT);
    int RX4 = add_block(rS, "RX4", BLOCK_SHAPE_2L_2R, BLOCK_DIR_TO_RIGHT);
    connect_blocks(rS, R2, 0, RX4, 0);
    connect_blocks(rS, R3, 0, RX4, 1);
    int R5 = add_block(rS, "R5", BLOCK_SHAPE_SINK_1, BLOCK_DIR_TO_RIGHT);
    connect_blocks(rS, RX4, 3, R5, 0);
    int R6 = add_block(rS, "R6", BLOCK_SHAPE_1L_1R, BLOCK_DIR_TO_RIGHT);
    connect_blocks(rS, RX4, 2, R6, 0);
    int RY7 = add_block(rS, "RY7", BLOCK_SHAPE_1L_2R, BLOCK_DIR_TO_RIGHT);
    connect_blocks(rS, R6, 1, RY7, 0);
    int RY10 = add_block(rS, "RY10", BLOCK_SHAPE_2L_1R, BLOCK_DIR_TO_RIGHT);
    connect_blocks(rS, RY7, 1, RY10, 1);
    connect_blocks(rS, RY7, 2, RY10, 0);
    int R11 = add_block(rS, "R11", BLOCK_SHAPE_SINK_1, BLOCK_DIR_TO_RIGHT);
    connect_blocks(rS, RY10, 2, R11, 0);

    int R12 = add_block(rS, "R12", BLOCK_SHAPE_SOURCE_1, BLOCK_DIR_TO_RIGHT);
    int R13 = add_block(rS, "R13", BLOCK_SHAPE_SINK_1, BLOCK_DIR_TO_RIGHT);
    connect_blocks(rS, R12, 0, R13, 0);

    make_blocks_shared(rS, RX4, L8);
    make_blocks_shared(rS, RX4, L9);
    make_blocks_shared(rS, R6, LY7);
    make_blocks_shared(rS, RY7, LY13);
    make_blocks_shared(rS, RY10, L12);

    SignalState_t s_state_default = SIGNAL_ST_LIGHT_RED;

    int H_InHB2 = add_signal(rS, "H_InHB2", SIGNAL_LIGHT_MAIN, s_state_default, true, L10);
    int H_InHB3 = add_signal(rS, "H_InHB3", SIGNAL_LIGHT_MAIN, s_state_default, true, L4);
    int H_L9 = add_signal(rS, "H_L9", SIGNAL_LIGHT_MAIN, s_state_default, false, L9);
    int HV_InHB2 = add_signal(rS, "HV_InHB2", SIGNAL_LIGHT_PRE_HV, s_state_default, false, L10);
    int V_InHB3 = add_signal(rS, "V_InHB3", SIGNAL_LIGHT_PRE, s_state_default, false, L4);
    int H_L8 = add_signal(rS, "H_L8", SIGNAL_LIGHT_MAIN, s_state_default, false, L8);
    int HV_L9 = add_signal(rS, "HV_L9", SIGNAL_LIGHT_PRE_HV, s_state_default, false, L9);
    int H_ExFK1 = add_signal(rS, "H_ExFK1", SIGNAL_LIGHT_MAIN, s_state_default, false, LY7);
    int HV_YY = add_signal(rS, "HV_YY", SIGNAL_LIGHT_PRE_HV, s_state_default, false, LY7);
    int H_ExFK2 = add_signal(rS, "H_ExFK2", SIGNAL_LIGHT_MAIN, s_state_default, false, LY7);
    int HV_ZZ = add_signal(rS, "HV_ZZ", SIGNAL_LIGHT_PRE_HV, s_state_default, false, LY7);
    int H_InFK2 = add_signal(rS, "H_InFK2", SIGNAL_LIGHT_MAIN, s_state_default, false, LY13);
    int HV_Z = add_signal(rS, "HV_Z", SIGNAL_LIGHT_PRE_HV, s_state_default, false, LY13);
    int H_ExES1 = add_signal(rS, "H_ExES1", SIGNAL_LIGHT_MAIN, s_state_default, true, L12);

    int H_ExES2 = add_signal(rS, "H_ExES2", SIGNAL_LIGHT_MAIN, s_state_default, true, L14);


    int H_ExHB3 = add_signal(rS, "H_ExHB3", SIGNAL_LIGHT_MAIN, s_state_default, true, RX4);
    int HV_X = add_signal(rS, "HV_X", SIGNAL_LIGHT_PRE_HV, s_state_default, false, RX4);
    int H_ExHB4 = add_signal(rS, "H_ExHB4", SIGNAL_LIGHT_MAIN, s_state_default, true, RX4);
    int HV_NX = add_signal(rS, "HV_NX", SIGNAL_LIGHT_PRE_HV, s_state_default, false, RX4);
    int H_ExHB5 = add_signal(rS, "H_ExHB5", SIGNAL_LIGHT_MAIN, s_state_default, false, R5);
    int H_R6 = add_signal(rS, "H_R6", SIGNAL_LIGHT_MAIN, s_state_default, false, R6);
    int HV_InFK1 = add_signal(rS, "HV_InFK1", SIGNAL_LIGHT_PRE_HV, s_state_default, false, RY7);
    int H_InFK1 = add_signal(rS, "H_InFK1", SIGNAL_LIGHT_MAIN, s_state_default, false, RY7);
    int HV_Y = add_signal(rS, "HV_Y", SIGNAL_LIGHT_PRE_HV, s_state_default, false, HV_Y);
    int H_ExFK3 = add_signal(rS, "H_ExFK3", SIGNAL_LIGHT_MAIN, s_state_default, false, RY10);
    int H_ExFK4 = add_signal(rS, "H_ExFK4", SIGNAL_LIGHT_MAIN, s_state_default, false, RY10);
    int V_InES1 = add_signal(rS, "V_InES1", SIGNAL_LIGHT_PRE, s_state_default, false, R11);
    int H_InES1 = add_signal(rS, "H_InES1", SIGNAL_LIGHT_MAIN, s_state_default, true, R11);

    int V_InES2 = add_signal(rS, "V_InES2", SIGNAL_LIGHT_PRE, s_state_default, false, R13);
    int H_InES2 = add_signal(rS, "H_InES2", SIGNAL_LIGHT_MAIN, s_state_default, true, R13);

    //TODO: Figure out what to connect the signals to
    int mH_InHB2 = add_magnet(rS, "mH_InHB2", H_InHB2, L9, L10);
    int mH_InHB3 = add_magnet(rS, "mH_InHB3", H_InHB3, L4, L3);
    int mH_L9 = add_magnet(rS, "mH_L9", H_L9, L8, L9);
    int mH_L8 = add_magnet(rS, "mH_L8", H_L8, LY7, L8);
    int mH_ExFK1 = add_magnet(rS, "mH_ExFK1", H_ExFK1, LY13, LY7);
    int mH_ExFK2 = add_magnet(rS, "mH_ExFK2", H_ExFK2, LY13, LY7);
    int mH_InFK2 = add_magnet(rS, "mH_InFK2", H_InFK2, L12, LY13);
    int mH_ExES1 = add_magnet(rS, "mH_ExES1", H_ExES1, L11, L12);
    int mH_ExES2 = add_magnet(rS, "mH_ExES2", H_ExES2, L15, L14);

    int mH_ExHB3 = add_magnet(rS, "mH_ExHB3", H_ExHB3, R2, RX4);
    int mH_ExHB4 = add_magnet(rS, "mH_ExHB4", H_ExHB4, R3, RX4);
    int mH_ExHB5 = add_magnet(rS, "mH_ExHB5", H_ExHB5, RX4, R5);
    int mH_R6 = add_magnet(rS, "mH_R6", H_R6, RX4, R6);
    int mH_InFK1 = add_magnet(rS, "mH_InFK1", H_InFK1, R6, RY7);
    int mH_ExFK3 = add_magnet(rS, "mH_ExFK3", H_ExFK3, RY7, RY10);
    int mH_ExFK4 = add_magnet(rS, "mH_ExFK4", H_ExFK4, RY7, RY10);
    int mH_InES1 = add_magnet(rS, "mH_InES1", H_InES1, RY10, R11);
    int mH_InES2 = add_magnet(rS, "mH_InES2", H_InES2, R12, R13);

    // Main to end

    int rME = add_route(rS, "rME");
    add_block_to_route(rS, rME, R2);
    add_block_to_route(rS, rME, RX4);
    add_block_to_route(rS, rME, R6);
    add_block_to_route(rS, rME, RY7);
    add_block_to_route(rS, rME, RY10);
    add_block_to_route(rS, rME, R11);

    // End to main

    int rEM = add_route(rS, "rEM");
    add_block_to_route(rS, rEM, L10);
    add_block_to_route(rS, rEM, L9);
    add_block_to_route(rS, rEM, L8);
    add_block_to_route(rS, rEM, LY7);
    add_block_to_route(rS, rEM, LY13);
    add_block_to_route(rS, rEM, L12);
    add_block_to_route(rS, rEM, L12);
    add_block_to_route(rS, rEM, L11);
}

/*void create_example_track(RailroadState_t &rS){
    // 0,1 - Main station top
    int b0 = add_block(rS, BLOCK_SHAPE_DRAIN_1, BLOCK_DIR_TO_RIGHT);

    int b1 = add_block(rS, BLOCK_SHAPE_DRAIN_1, BLOCK_DIR_TO_LEFT);
    make_blocks_shared(rS, b0,b1);
    // 2,3 - Main station bottom
    int b2 = add_block(rS, BLOCK_SHAPE_DRAIN_1, BLOCK_DIR_TO_RIGHT);
    int b3 = add_block(rS, BLOCK_SHAPE_DRAIN_1, BLOCK_DIR_TO_LEFT);
    make_blocks_shared(rS, b2,b3);
    // 4,5 - End station
    int b4 = add_block(rS, BLOCK_SHAPE_DRAIN_1, BLOCK_DIR_TO_RIGHT);
    int b5 = add_block(rS, BLOCK_SHAPE_DRAIN_1, BLOCK_DIR_TO_LEFT);
    make_blocks_shared(rS, b4,b5);
    // 6,7 - to Shoggental
    int b6 = add_block(rS, BLOCK_SHAPE_DRAIN_1, BLOCK_DIR_TO_RIGHT);
    int b7 = add_block(rS, BLOCK_SHAPE_DRAIN_1, BLOCK_DIR_TO_LEFT);
    make_blocks_shared(rS, b6,b7);
    // Main station 2x2
    int b8 = add_block(rS, BLOCK_SHAPE_2L_2R, BLOCK_DIR_TO_RIGHT);
    int b9 = add_block(rS, BLOCK_SHAPE_2L_2R, BLOCK_DIR_TO_LEFT);
    make_blocks_shared(rS, b8,b9);
    connect_blocks(rS, b0, 0, b8, 0);
    connect_blocks(rS, b1, 0, b9, 0);
    connect_blocks(rS, b2, 0, b8, 1);
    connect_blocks(rS, b3, 0, b9, 1);
    connect_blocks(rS, b8, 3, b6, 0);
    connect_blocks(rS, b9, 3, b7, 0);
    // Main to Fredikon, to right
    int b10 = add_block(rS, BLOCK_SHAPE_1L_1R, BLOCK_DIR_TO_RIGHT);
    make_blocks_shared(rS, b9,b10);
    connect_blocks(rS, b8, 2, b10, 0);
    // Fredikon Station, to right
    int b11 = add_block(rS, BLOCK_SHAPE_1L_2R, BLOCK_DIR_TO_RIGHT);
    int b12 = add_block(rS, BLOCK_SHAPE_2L_1R, BLOCK_DIR_TO_RIGHT);
    connect_blocks(rS, b10, 1, b11, 0);
    connect_blocks(rS, b11, 1, b12, 0);
    connect_blocks(rS, b11, 2, b12, 1);
    // Fredikon Station to End Station , to right
    int b13 = add_block(rS, BLOCK_SHAPE_1L_1R, BLOCK_DIR_TO_RIGHT);
    connect_blocks(rS, b12, 2, b13, 0);
    connect_blocks(rS, b13, 1, b4, 0);
    // Fredikon to Main, to left
    int b14 = add_block(rS, BLOCK_SHAPE_1L_1R, BLOCK_DIR_TO_LEFT);
    make_blocks_shared(rS, b11,b14);
    connect_blocks(rS, b9, 2, b14, 0);
    // Fredikon Station, to left
    int b15 = add_block(rS, BLOCK_SHAPE_1L_2R, BLOCK_DIR_TO_LEFT);
    int b16 = add_block(rS, BLOCK_SHAPE_2L_1R, BLOCK_DIR_TO_LEFT);
    make_blocks_shared(rS, b11,b15);
    make_blocks_shared(rS, b12,b16);
    make_blocks_shared(rS, b13,b16);
    connect_blocks(rS, b14, 1, b15, 0);
    connect_blocks(rS, b15, 1, b16, 0);
    connect_blocks(rS, b15, 2, b16, 1);
}*/

void add_input_event_to_test_queue(queue<InputEvent_t> &queue, InputEventType_t type, int entity_idx, int data){
    InputEvent_t event;
    event.type = type;
    event.entity_idx = entity_idx;
    event.data = data;
    queue.push(event);
}

void create_test_event_queue(RailroadState_t &rS, queue<InputEvent_t> &queue){
    //Switch events and manual signal events could be added to test list too

    //Reserve route Main->End
    add_input_event_to_test_queue(queue, INPUT_EVENT_ROUTE_ON, get_route_idx(rS, "rME"), 0);

    //Magnets are triggered as train goes forward
    add_input_event_to_test_queue(queue, INPUT_EVENT_MAGNET_TRIGGER, get_magnet_idx(rS, "mH_ExHB3"), 0);
    add_input_event_to_test_queue(queue, INPUT_EVENT_MAGNET_TRIGGER, get_magnet_idx(rS, "mH_R6"), 0);
    add_input_event_to_test_queue(queue, INPUT_EVENT_MAGNET_TRIGGER, get_magnet_idx(rS, "mH_InFK1"), 0);
    add_input_event_to_test_queue(queue, INPUT_EVENT_MAGNET_TRIGGER, get_magnet_idx(rS, "mH_ExFK3"), 0);
    add_input_event_to_test_queue(queue, INPUT_EVENT_MAGNET_TRIGGER, get_magnet_idx(rS, "mH_InES1"), 0);

    // Opposite train could be added to events too
}

int get_block_idx(RailroadState_t &rS, string name){
    for(int i = 0; i < rS.blocks.size(); i++){
        if(name == rS.blocks[i].name){
            return i;
        }
    }
    throw("Block not found");
    return -1;
}

int get_route_idx(RailroadState_t &rS, string name){
    for(int i = 0; i < rS.routes.size(); i++){
        if(name == rS.routes[i].name){
            return i;
        }
    }
    throw("Route not found");
    return -1;
}

int get_magnet_idx(RailroadState_t &rS, string name){
    for(int i = 0; i < rS.magnets.size(); i++){
        if(name == rS.magnets[i].name){
            return i;
        }
    }
    throw("Magnet not found");
    return -1;
}

int get_signal_idx(RailroadState_t &rS, string name){
    for(int i = 0; i < rS.signals.size(); i++){
        if(name == rS.signals[i].name){
            return i;
        }
    }
    throw("Signal not found");
    return -1;
}

int add_route(RailroadState_t &rS, std::string name){
    Route route;
    route.name = name;
    rS.routes.push_back(route);
    return rS.routes.size() - 1;
}

void add_block_to_route(RailroadState_t &rS, int route_idx, int block_idx){
    rS.routes[route_idx].blockIndices.push_back(block_idx);
}

int add_block(RailroadState_t &rS, std::string name, BlockShape_t shape, BlockDirection_t direction){
    Block_t block;
    block.blockShape = shape;
    block.blockState = BLOCK_ST_FREE;
    block.blockDirection = direction;
    block.is_reserved = false;
    block.is_occupied = false;
    block.name = name;
    rS.blocks.push_back(block);
    return rS.blocks.size() - 1;
}

void make_blocks_shared(RailroadState_t &rS, int index_1, int index_2){
    if(index_1 >= rS.blocks.size() || index_1 >= rS.blocks.size() ){
        throw("Block index out of range");
    }
    bool b1_already_added = false;
    for(int i = 0; i < rS.blocks[index_1].sharedBlocksIndices.size(); i++){
        if(rS.blocks[index_1].sharedBlocksIndices[i] == index_2){
            b1_already_added = true;
        }
    }
    bool b2_already_added = false;
    for(int i = 0; i < rS.blocks[index_2].sharedBlocksIndices.size(); i++){
        if(rS.blocks[index_2].sharedBlocksIndices[i] == index_1){
            b2_already_added = true;
        }
    }
    if(!b1_already_added){
        rS.blocks[index_1].sharedBlocksIndices.push_back(index_2);
    }
    if(!b2_already_added){
        rS.blocks[index_2].sharedBlocksIndices.push_back(index_1);
    }
}

void connect_blocks(RailroadState_t &rS, int index_1, int slot_1, int index_2, int slot_2){
    if(index_1 >= rS.blocks.size() || index_1 >= rS.blocks.size() ){
        throw("Block index out of range");
    }
    //TODO
}

int add_signal(RailroadState_t &rS, std::string name, SignalType_t signal_type, SignalState_t signal_state, bool is_manual, int block_idx){
    Signal_t signal;
    signal.signal_type = signal_type;
    signal.signal_state = signal_state;
    signal.block_idx = block_idx;
    signal.is_manual = is_manual;
    signal.name = name;
    rS.signals.push_back(signal);
    int signal_idx = rS.signals.size() - 1;
    rS.blocks[block_idx].signalIndices.push_back(signal_idx);
    return signal_idx;
}

void init_switch_routing_models();

int add_switch(RailroadState_t &rS, std::string name, SwitchState_t switch_state, const vector<SwitchRoute_t> *route_set, int block_idx){
    if(!are_switch_routing_models_initialized){
        init_switch_routing_models();
        are_switch_routing_models_initialized = true;
    }
    Switch_t sw;
    sw.state = switch_state;
    sw.routes = route_set;
    sw.block_idx = block_idx;
    sw.name = name;
    rS.switches.push_back(sw);
    int switch_idx = rS.switches.size() - 1;
    rS.blocks[block_idx].switchIndices.push_back(switch_idx);
    return switch_idx;
}

int add_magnet(RailroadState_t &rS, std::string name, int main_signal_idx, int block_to_free_idx, int block_to_occupy_idx){
    Magnet_t magnet;
    magnet.block_to_free_idx = block_to_free_idx;
    magnet.block_to_occupy_idx = block_to_occupy_idx;
    magnet.main_signal_idx = main_signal_idx;
    magnet.name = name;
    rS.magnets.push_back(magnet);
    int magnet_idx = rS.magnets.size() - 1;
    rS.blocks[block_to_free_idx].mangetIndicesFree.push_back(magnet_idx);
    rS.blocks[block_to_occupy_idx].mangetIndicesOccupy.push_back(magnet_idx);
    return magnet_idx;
}

void add_input_event(RailroadState_t &rS, InputEvent_t &event){
    rS.inputEvents.push(event);
}

void add_output_event(RailroadState_t &rS, OutputEvent_t &event){
    rS.outputEvents.push(event);
}


void process_input_event(RailroadState_t &rS, InputEvent_t &event){
    switch(event.type){
        case INPUT_EVENT_MAGNET_TRIGGER:
            cout << "Magnet trigger: " << rS.magnets[event.entity_idx].name << "\n";
            magnet_trigger(rS, event.entity_idx);
            break;
        case INPUT_EVENT_SWITCH_FORWARD:
            cout << "Switch forward: " << rS.switches[event.entity_idx].name << "\n";
            //TODO: Update signals if needed
            rS.switches[event.entity_idx].state = SWITCH_ST_FORWARD;
            break;
        case INPUT_EVENT_SWITCH_TURN:
            cout << "Switch turn: " << rS.switches[event.entity_idx].name << "\n";
            //TODO: Update signals if needed
            rS.switches[event.entity_idx].state = SWITCH_ST_TURN;
            break;
        case INPUT_EVENT_ROUTE_ON:
            cout << "Route on: " << rS.routes[event.entity_idx].name << "\n";
            //TODO: check if route was succesfully reserved and emit GUI output event
            reserve_route(rS, event.entity_idx);
            break;
    }
}

void process_output_event(RailroadState_t &rS, OutputEvent_t &event){
    switch(event.type){
        case OUTPUT_EVENT_T_SIGNAL_CHANGE_STATE:
            cout << "Signal change: " << rS.signals[event.entity_idx].name << " State: " << event.data << "\n";
            break;
    }
}

void change_signal_state(RailroadState_t &rS, int signal_idx, SignalState_t state){
    SignalState_t previous_state = rS.signals[signal_idx].signal_state;
    rS.signals[signal_idx].signal_state = state;
    if(state != previous_state){
        OutputEvent_t event;
        event.type = OUTPUT_EVENT_T_SIGNAL_CHANGE_STATE;
        event.entity_idx = signal_idx;
        event.data = state;
    }
}

bool reserve_route(RailroadState_t &rS, int route_idx){
    //TODO: Check if route is already reserved and return false if so.
    for(int i = 0; i < rS.routes[route_idx].blockIndices.size(); i++){
        reserve_block(rS, rS.routes[route_idx].blockIndices[i]);
    }
    return true;
}

void reserve_block(RailroadState_t &rS, int block_idx){
    rS.blocks[block_idx].is_reserved = true;
    //Turn lights green?
    for(int i = 0; i < rS.blocks[block_idx].signalIndices.size(); i++){
        int signal_idx = rS.blocks[block_idx].signalIndices[i];
        switch(rS.signals[signal_idx].signal_type){
            case SIGNAL_LIGHT_MAIN:
            case SIGNAL_LIGHT_PRE:
            case SIGNAL_LIGHT_PRE_HV:
                change_signal_state(rS, rS.blocks[block_idx].signalIndices[i], SIGNAL_ST_LIGHT_GREEN);
                break;
            case SIGNAL_LIGHT_DWARF:
                change_signal_state(rS, rS.blocks[block_idx].signalIndices[i], SIGNAL_ST_LIGHT_DWARF_FREE);
                break;
            case SIGNAL_SHAPE_DISC:
            default:
                change_signal_state(rS, rS.blocks[block_idx].signalIndices[i], SIGNAL_ST_DISC_GO);
                break;
        }
    }
}
void free_block(RailroadState_t &rS, int block_idx){
    rS.blocks[block_idx].is_reserved = false;
}

void occupy_block(RailroadState_t &rS, int block_idx){
    rS.blocks[block_idx].is_occupied = true;
    //does anything change when block gets occupied?
}

void leave_block(RailroadState_t &rS, int block_idx){
    rS.blocks[block_idx].is_occupied = false;
    //The block also gets de-reserved
    free_block(rS, block_idx);
    //Turn lights red
    for(int i = 0; i < rS.blocks[block_idx].signalIndices.size(); i++){
        int signal_idx = rS.blocks[block_idx].signalIndices[i];
        switch(rS.signals[signal_idx].signal_type){
            case SIGNAL_LIGHT_MAIN:
            case SIGNAL_LIGHT_PRE:
            case SIGNAL_LIGHT_PRE_HV:
                change_signal_state(rS, rS.blocks[block_idx].signalIndices[i], SIGNAL_ST_LIGHT_RED);
                break;
            case SIGNAL_LIGHT_DWARF:
                change_signal_state(rS, rS.blocks[block_idx].signalIndices[i], SIGNAL_ST_LIGHT_DWARF_STOP);
                break;
            case SIGNAL_SHAPE_DISC:
            default:
                change_signal_state(rS, rS.blocks[block_idx].signalIndices[i], SIGNAL_ST_DISC_STOP);
                break;
        }
    }
}

void magnet_trigger(RailroadState_t &rS, int magnet_idx){
    free_block(rS, rS.magnets[magnet_idx].block_to_free_idx);
    occupy_block(rS, rS.magnets[magnet_idx].block_to_occupy_idx);
}


//Default routing models for different kind of blocks:

//BLOCK_SHAPE_2L_1R
//Left to right
//Switch not used

//Right to left
vector<SwitchRoute_t> sw_route_2L_1R_RtL;

//BLOCK_SHAPE_2L_2R
//Left to right
vector<SwitchRoute_t> sw_route_2L_2R_LtR;

//Right to left
vector<SwitchRoute_t> sw_route_2L_2R_RtL;

//BLOCK_SHAPE_1L_2R
//Left to right
vector<SwitchRoute_t> sw_route_1L_2R_LtR;

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

void init_switch_routing_models(){
    //BLOCK_SHAPE_2L_1R
    //Left to right

    //Right to left
    {
        SwitchRoute_t r1;
        r1.input = 2;
        r1.output_forward = 0;
        r1.output_turn = 1;
        sw_route_2L_1R_RtL.push_back(r1);
    }

    //BLOCK_SHAPE_2L_2R
    //Left to right
    {
        SwitchRoute_t r1;
        r1.input = 0;
        r1.output_forward = 2;
        r1.output_turn = 3;
        SwitchRoute_t r2;
        r2.input = 1;
        r2.output_forward = 3;
        r2.output_turn = 2;
        sw_route_2L_2R_LtR.push_back(r1);
        sw_route_2L_2R_LtR.push_back(r2);
    }

    //Right to left
    {
        SwitchRoute_t r1;
        r1.input = 2;
        r1.output_forward = 0;
        r1.output_turn = 1;
        SwitchRoute_t r2;
        r2.input = 3;
        r2.output_forward = 1;
        r2.output_turn = 0;
        sw_route_2L_2R_RtL.push_back(r1);
        sw_route_2L_2R_RtL.push_back(r2);
    }

    //BLOCK_SHAPE_1L_2R
    //Left to right
    {
        SwitchRoute_t r1;
        r1.input = 0;
        r1.output_forward = 1;
        r1.output_turn = 2;
        sw_route_1L_2R_LtR.push_back(r1);
    }

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

}
