/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#pragma once

#include "robotstate.h"

class GetOffEdgeState : public RobotState
{
public:
    GetOffEdgeState(State * parent, IRobot & robot);

protected:
    bool on_event(ProximityEvent & event) override;
    bool on_event(TimerEvent & event) override;
};

