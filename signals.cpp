#include "signals.h"

bool are_switch_routing_models_initialized = false;

using namespace std;

void init_railroad_state(RailroadState_t &rS){
    rS.shutdown = false;
}

void create_example_track(RailroadState_t &rS){
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
}

int add_block(RailroadState_t &rS, BlockShape_t shape, BlockDirection_t direction){
    Block_t block;
    block.blockShape = shape;
    block.blockState = BLOCK_ST_FREE;
    block.blockDirection = direction;
    rS.blocks.push_back(block);
    return rS.blocks.size()-1;
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

int add_signal(RailroadState_t &rS, SignalType_t signal_type, SignalState_t signal_state, int block_idx){
    Signal_t signal;
    signal.signal_type = signal_type;
    signal.signal_state = signal_state;
    signal.block_idx = block_idx;
    rS.signals.push_back(signal);
    int signal_idx = rS.signals.size() - 1;
    rS.blocks[block_idx].signalIndices.push_back(signal_idx);
    return signal_idx;
}

void init_switch_routing_models();

int add_switch(RailroadState_t &rS, SwitchState_t switch_state, const vector<SwitchRoute_t> *route_set, int block_idx){
    if(!are_switch_routing_models_initialized){
        init_switch_routing_models();
        are_switch_routing_models_initialized = true;
    }
    Switch_t sw;
    sw.state = switch_state;
    sw.routes = route_set;
    sw.block_idx = block_idx;
    rS.switches.push_back(sw);
    int switch_idx = rS.switches.size() - 1;
    rS.blocks[block_idx].switchIndices.push_back(switch_idx);
    return switch_idx;
}

int add_magnet(RailroadState_t &rS, MagnetState_t state, int block_idx){
    Magnet_t magnet;
    magnet.state = state;
    magnet.block_idx = block_idx;
    rS.magnets.push_back(magnet);
    int magnet_idx = rS.magnets.size() - 1;
    rS.blocks[block_idx].mangetIndices.push_back(magnet_idx);
    return magnet_idx;
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
