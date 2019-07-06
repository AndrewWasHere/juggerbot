/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "faceinteriorstate.h"
#include "getoffedgestate.h"

extern GetOffEdgeState get_off_edge;

FaceInteriorState::FaceInteriorState(State * parent, IRobot & robot) :
    RobotState("face", parent, robot)
{}

bool FaceInteriorState::on_event(EncoderEvent & event)
{
    m_robot.move(m_robot.stalking_speed);
    m_robot.start_timer(250);
    transition_to_state(get_off_edge);

    return true;
}
