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

#include <set>
#include <map>

class MultiClassSpell
{
public:
    uint8 ClassID;
    uint32 SpellID;
    std::string SpellName;
    std::string SpellSubText;
    uint32 ReqSpellID;
    uint8 ReqLevel;
    bool AllowHorde;
    bool AllowAlliance;
    bool IsTalent;
    bool IsLearnedByTalent;
};

class MasterSkill
{
public:
    uint32 SpellID;
    uint8 ClassID;
    std::list<MultiClassSpell> Spells;
};

struct PlayerClassInfoItem
{
    uint8 ClassID;
    std::string ClassName;
    uint8 Level;
    uint8 UseSharedQuests;
};

struct PlayerClassSettings
{
    uint32 GUID;
    uint8 ClassID;
    bool UseSharedQuests;
};

struct PlayerControllerData
{
    uint32 GUID;
    uint8 NextClass;
    uint8 ActiveClassQuests;
};

class MultiClassMod
{
private:
    MultiClassMod();

    std::map<uint32, std::map<uint32, MultiClassSpell>> ClassSpellsByClassAndSpellID;
    std::set<uint32> ClassSpellIDs;
    std::map<uint32, MasterSkill> MasterSkillsBySpellID;

    bool DoesSavedClassDataExistForPlayer(Player* player, uint8 lookupClass);
    bool IsValidRaceClassCombo(uint8 lookupClass, uint8 lookupRace);
    std::list<MasterSkill> GetKnownMasterSkillsForPlayer(Player* player);
    std::list<MasterSkill> GetKnownMasterSkillsForPlayerForClass(Player* player, uint8 classID);

    void CopyCharacterDataIntoModCharacterTable(Player* player, CharacterDatabaseTransaction& transaction);
    void MoveTalentsToModTalentsTable(Player* player, CharacterDatabaseTransaction& transaction);
    void MoveClassSpellsToModSpellsTable(Player* player, CharacterDatabaseTransaction& transaction);
    void MoveClassSkillsToModSkillsTable(Player* player, CharacterDatabaseTransaction& transaction);
    void ReplaceModClassActionCopy(Player* player, CharacterDatabaseTransaction& transaction);
    void MoveGlyphsToModGlyhpsTable(Player* player, CharacterDatabaseTransaction& transaction);
    void MoveAuraToModAuraTable(Player* player, CharacterDatabaseTransaction& transaction);
    void MoveEquipToModInventoryTable(Player* player, CharacterDatabaseTransaction& transaction);

    void UpdateCharacterFromModCharacterTable(uint32 playerGUID, uint8 pullClassID, CharacterDatabaseTransaction& transaction);
    void CopyModSpellTableIntoCharacterSpells(uint32 playerGUID, uint8 pullClassID, CharacterDatabaseTransaction& transaction);
    void CopyModActionTableIntoCharacterAction(uint32 playerGUID, uint8 pullClassID, CharacterDatabaseTransaction& transaction);
    void CopyModSkillTableIntoCharacterSkills(uint32 playerGUID, uint8 pullClassID, CharacterDatabaseTransaction& transaction);

    void GetSpellLearnAndUnlearnsForPlayer(Player* player, std::list<int32>& outSpellUnlearns, std::list<int32>& outSpellLearns);
    uint8 GetTokenCountToIssueForPlayer(Player* player, uint8 classID);
    bool RefundTokenCountForPlayerClass(Player* player, uint8 classID, uint8 tokenCountToRefund);
    void UpdateTokenIssueCountForPlayerClass(Player* player, uint8 tokenCount, uint8 classID);

public:
    static MultiClassMod* instance()
    {
        static MultiClassMod instance;
        return &instance;
    }
    ~MultiClassMod();

    bool LoadClassAbilityData();

    bool MarkClassChangeOnNextLogout(ChatHandler* handler, Player* player, uint8 newClass);
    bool MarkChangeQuestShareForCurrentClassOnNextLogout(Player* player, bool doQuestShare);
    bool PerformClassSwitch(Player* player, PlayerControllerData controllerData);
    bool PerformQuestDataSwitch(uint32 playerGUID, uint8 prevQuestDataClass, uint8 nextQuestDataClass);
    bool PerformPlayerDelete(ObjectGuid guid);
    void PerformKnownSpellUpdateFromMasterSkills(Player* player);
    bool PerformTokenIssuesForPlayerClass(Player* player, uint8 classID);
    void ResetMasterSkillsForPlayerClass(Player* player, uint8 playerClass);

    std::map<uint8, uint8> GetClassLevelsByClassForPlayer(Player* player);
    std::map<std::string, PlayerClassInfoItem> GetPlayerClassInfoByClassNameForPlayer(Player* player);
    bool IsSpellAMasterSkill(uint32 spellID);

    PlayerControllerData GetPlayerControllerData(Player* player);
    void SetPlayerControllerData(PlayerControllerData controllerData);
    PlayerClassSettings GetPlayerClassSettings(Player* player, uint8 classID);
    void SetPlayerClassSettings(PlayerClassSettings classSettings);
};

std::string GetClassStringFromID(uint8 classID);
uint32 GetTokenItemIDForClass(uint8 classID);

#define MultiClass MultiClassMod::instance()

#endif //MASTER_CLASS_TRAINERS_H
