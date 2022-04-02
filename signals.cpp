#include "signals.h"

using namespace std;

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
