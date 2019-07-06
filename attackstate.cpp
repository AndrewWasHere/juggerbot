/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "attackstate.h"
#include "faceinteriorstate.h"
#include "scanstate.h"

extern ScanState scan;
extern FaceInteriorState face_interior;

AttackState::AttackState(State * parent, IRobot & robot) :
    RobotState("attack", parent, robot)
{}

Result AttackState::on_entry()
{
    m_robot.move(200);

    return OK;
}

bool AttackState::on_event(BoundaryEvent & event)
{
    m_robot.face_interior(event.m_direction);
    transition_to_state(face_interior);
    
    return true;
}

bool AttackState::on_event(ProximityEvent & event)
{
    int16_t const delta = 25;

    int16_t speed;
    switch(event.m_direction)
    {
    case NONE:
        transition_to_state(scan);
        break;
    case AHEAD:
        if (event.m_left_brightness >= 6)
        {
            speed = m_robot.ramming_speed;
        }
        else if (event.m_left_brightness = 5)
        {
            speed = m_robot.rushing_speed;
        }
        else
        {
            speed = m_robot.stalking_speed;
        }
        m_robot.move(speed);
        break;
    case LEFT:
        m_robot.change_speed_by(delta, 0);
        break;
    case RIGHT:
        m_robot.change_speed_by(0, delta);
        break;
    default:
        break;
    }

    return true;
}
