/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#pragma once

#include "robotstate.h"

class FaceInteriorState : public RobotState
{
public:
    FaceInteriorState(State * parent, IRobot & robot);

protected:
    bool on_event(EncoderEvent & event) override;
};

