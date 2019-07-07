/*
    Copyright 2019, Andrew Lin.

    This source code is released under the 3-Clause BSD license. See 
    LICENSE.txt, or https://opensource.org/licenses/BSD-3-Clause.
 */
#include "attackstate.h"
#include "backupstate.h"
#include "scanstate.h"

extern AttackState attack;
extern ScanState scan;

BackupState::BackupState(State * parent, IRobot & robot) :
    RobotState("backup", parent, robot)
{}

bool BackupState::on_event(TimerEvent & event)
{
    transition_to_state(scan);

    return true;
}
