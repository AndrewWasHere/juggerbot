/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "attackstate.h"
#include "faceinteriorstate.h"
#include "scanstate.h"

extern AttackState attack;
extern FaceInteriorState face_interior;

ScanState::ScanState(State * parent, IRobot & robot) :
    RobotState("scan", parent, robot)
{}

Result ScanState::on_entry()
{
    m_robot.scan();
    return OK;
}

bool ScanState::on_event(BoundaryEvent & event)
{
    m_robot.face_interior(event.m_direction);
    transition_to_state(face_interior);
    
    return true;
}

bool ScanState::on_event(ProximityEvent & event)
{
    if (event.m_direction != NONE)
    {
        transition_to_state(attack);
    }

    return true;
}