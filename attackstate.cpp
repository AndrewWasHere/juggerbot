/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "attackstate.h"
#include "backupstate.h"
#include "scanstate.h"

extern ScanState scan;
extern BackupState backup;

AttackState::AttackState(State * parent, IRobot & robot) :
    RobotState("attack", parent, robot)
{}

Result AttackState::on_entry()
{
    m_robot.move(STALKING_SPEED);

    return OK;
}

bool AttackState::on_event(BoundaryEvent & event)
{
    int16_t delta = 100;

    switch(event.m_direction)
    {
    case LEFT:
        m_robot.move(-RAMMING_SPEED, -(RAMMING_SPEED - delta));
        break;
    case AHEAD:
        m_robot.move(-RAMMING_SPEED);
        break;
    case RIGHT:
        m_robot.move(-(RAMMING_SPEED - delta), -RAMMING_SPEED);
        break;
    }
    m_robot.start_timer(100);
    transition_to_state(backup);
    
    return true;
}

bool AttackState::on_event(ProximityEvent & event)
{
    uint8_t const brightness_threshold = 5;
    int16_t const delta = 25;

    int16_t speed, lms, rms; 
    if 
    (
        event.m_left_brightness >= brightness_threshold || 
        event.m_right_brightness >= brightness_threshold
    )
    {
        speed = RAMMING_SPEED;
    }
    else
    {
        speed = RUSHING_SPEED;
    }

    switch(event.m_direction)
    {
    case NONE:
        transition_to_state(scan);
        break;
    case AHEAD:
        m_robot.move(speed);
        break;
    case LEFT:
        m_robot.get_speed(lms, rms);
        if (rms != speed)
        {
            m_robot.move(speed - delta, speed);
        }
        else
        {
            m_robot.change_speed_by(-delta, 0);
        }
        break;
    case RIGHT:
        m_robot.get_speed(lms, rms);
        if (lms != speed)
        {
            m_robot.move(speed, speed - delta);
        }
        else
        {
            m_robot.change_speed_by(0, -delta);
        }
        break;
    default:
        break;
    }

    return true;
}
