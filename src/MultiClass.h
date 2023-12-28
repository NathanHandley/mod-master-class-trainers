/*
** Made by Nathan Handley https://github.com/NathanHandley
** AzerothCore 2019 http://www.azerothcore.org/
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU Affero General Public License as published by the
* Free Software Foundation; either version 3 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MASTER_CLASS_TRAINERS_H
#define MASTER_CLASS_TRAINERS_H

#include "Common.h"

#include <list>
#include <map>

struct MultiClassTrainerClassData
{
    uint32 SpellID;
    std::string SpellName;
    std::string SpellSubText;
    uint32 ReqSpellID;
    uint32 ReqSkillLine;
    uint16 ReqSkillRank;
    uint16 ReqLevel;
    bool AllowHorde;
    bool AllowAlliance;
    uint32 DefaultCost;
    uint32 ModifiedCost;
    bool IsTalent;
};

class MultiClassMod
{
private:
    MultiClassMod();

    //bool mIsInitialized;
    std::map<uint16, std::list<MultiClassTrainerClassData>> ClassTrainerDataByClass;

public:
    static MultiClassMod* instance()
    {
        static MultiClassMod instance;
        return &instance;
    }

    ~MultiClassMod();

    bool LoadClassTrainerData();

    bool ChangeClass(ChatHandler* handler, Player* player, uint8 newClass);

    //bool GetIsInitialized() { return mIsInitialized; }
};

#define MultiClass MultiClassMod::instance()

#endif //MASTER_CLASS_TRAINERS_H
