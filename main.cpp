#include "signals.h"
#include <thread>
#include <chrono>

using namespace std;

RailroadState_t rS;

int main(){
    init_railroad_state(rS);
    create_example_track(rS);
    queue<InputEvent_t> testEventList;
    create_test_event_queue(rS, testEventList);
    // Command polling initial positions of switches needs to be added here

    // Loop will go until shutdown event is encountered
    // Events are normally added during program runtime by the GUI and input handler
    while(!rS.shutdown){
        while(!rS.inputEvents.empty()){
            process_input_event(rS, rS.inputEvents.front());
            rS.inputEvents.pop();
        }
        while(!rS.outputEvents.empty()){
            process_output_event(rS, rS.outputEvents.front());
            rS.outputEvents.pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // There should be procedures for polling the GUI and input events here
        // For now we don't have them yet, so let's process events from test list instead
        if(!testEventList.empty()){
            add_input_event(rS, testEventList.front());
            testEventList.pop();
        }else{
            rS.shutdown = true;
        }
    }
    return 0;
}
