#include "signals.h"
#include <thread>
#include <chrono>



using namespace std;

RailroadState_t railroadState;

int main(){
    init_railroad_state(railroadState);
    create_example_track(railroadState);
    // Command polling initial positions of switches needs to be added here

    // Loop will go until shutdown event is encountered
    // Events are normally added during program runtime by the GUI and input handler
    while(!railroadState.shutdown){
        while(!railroadState.inputEvents.empty()){
            process_input_event(railroadState, railroadState.inputEvents.front());
        }
        while(!railroadState.outputEvents.empty()){
            process_output_event(railroadState, railroadState.outputEvents.front());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // There should be procedures for polling the GUI and input events here
    }
    return;
}
