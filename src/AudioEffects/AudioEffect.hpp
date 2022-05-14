#pragma once

#include "string"

class AudioEffect {
    public:
        virtual void processAudio(float &sample) = 0;
        
    private: 
        std::string name;
};