#ifndef ON_OFF_CONTROLLER_HPP
#define ON_OFF_CONTROLLER_HPP

#include "HeaterController.hpp"

class OnOffController : public HeaterController {
    private:
        bool heaterOn;
    public:     
        OnOffController(double setTemp);
        ~OnOffController();
        void Do() override;
        void Start();
        void Stop();
};

#endif