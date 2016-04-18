/*=================================================================
	File created by Yohann NICOLAS.

	Unassign Skill Point for futher re-assignment.

=================================================================*/

#ifndef __SKILLSPOINTS_H__INCLUDED
#define __SKILLSPOINTS_H__INCLUDED

extern bool active_SkillsPoints;
extern bool unassignSkillsPointsOneByOne;
extern int posXUnassignSkillBtn, posYUnassignSkillBtn;

void UnassignAllSkillsPoints(Unit* ptChar);
void client_UnassignAllSkillsPoints();

void Install_SkillsPoints();

#endif