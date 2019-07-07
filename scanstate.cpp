/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "attackstate.h"
#include "backupstate.h"
#include "scanstate.h"

extern AttackState attack;
extern BackupState backup;

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
    int16_t const delta = 100;

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

bool ScanState::on_event(ProximityEvent & event)
{
    if (event.m_direction != NONE)
    {
        m_robot.move(STALKING_SPEED);
        transition_to_state(attack);
    }

    return true;
}