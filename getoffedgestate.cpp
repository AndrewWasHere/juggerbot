/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "attackstate.h"
#include "getoffedgestate.h"
#include "scanstate.h"

extern AttackState attack;
extern ScanState scan;

GetOffEdgeState::GetOffEdgeState(State * parent, IRobot & robot) :
    RobotState("get off", parent, robot)
{}

bool GetOffEdgeState::on_event(ProximityEvent & event)
{
    if (event.m_direction != NONE)
    {
        transition_to_state(attack);
    }

    return true;
}

bool GetOffEdgeState::on_event(TimerEvent & event)
{
    transition_to_state(scan);

    return true;
}
