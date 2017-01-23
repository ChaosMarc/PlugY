/*=================================================================
	File created by Yohann NICOLAS.

	Unassign Skill Point for futher re-assignment.

=================================================================*/
#pragma once

#include "common.h"

extern bool active_SkillsPoints;
extern bool unassignSkillsPointsOneByOne;
extern int posXUnassignSkillBtn, posYUnassignSkillBtn;

void UnassignAllSkillsPoints(Unit* ptChar);
void client_UnassignAllSkillsPoints();

void Install_SkillsPoints();

/*================================= END OF FILE =================================*/