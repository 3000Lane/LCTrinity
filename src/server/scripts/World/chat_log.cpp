/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "Channel.h"
#include "Guild.h"
#include "Group.h"

#include <stdarg.h>
#include <stdio.h>

class ChatLogScript : public PlayerScript
{
public:
    ChatLogScript() : PlayerScript("ChatLogScript") { }

    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg)
    {
        switch (type)
        {
            case CHAT_MSG_ADDON:
                if (sWorld->getBoolConfig(CONFIG_CHATLOG_ADDON))
                    /*sLog->outChat("[ADDON] Player %s sends: %s",
                        player->GetName(), msg.c_str());*/
                break;

            case CHAT_MSG_SAY:
                if (sWorld->getBoolConfig(CONFIG_CHATLOG_PUBLIC))
					sLog->outChatDB("SAY", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), "Null", player->GetZoneId());
				break;

            case CHAT_MSG_EMOTE:
                if (sWorld->getBoolConfig(CONFIG_CHATLOG_PUBLIC))
					sLog->outChatDB("EMOTE", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), "Null", player->GetZoneId());
                break;

            case CHAT_MSG_YELL:
                if (sWorld->getBoolConfig(CONFIG_CHATLOG_PUBLIC))
						sLog->outChatDB("YELL", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), "Null", player->GetZoneId());
                break;
        }
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* receiver)
    {
        if (lang != LANG_ADDON && sWorld->getBoolConfig(CONFIG_CHATLOG_WHISPER))
           /* sLog->outChat("[WHISPER] Player %s tells %s: %s",
                player->GetName(), receiver ? receiver->GetName() : "<unknown>", msg.c_str());*/
			sLog->outChatDB("WHISPER", player->GetSession()->GetPlayerName(), receiver ? receiver->GetSession()->GetPlayerName() : "<unknown>", msg.c_str(), "Null", player->GetZoneId());
        else if (lang == LANG_ADDON && sWorld->getBoolConfig(CONFIG_CHATLOG_ADDON))
            /*sLog->outChat("[ADDON] Player %s tells %s: %s",
                player->GetName(), receiver ? receiver->GetName() : "<unknown>", msg.c_str());*/
			sLog->outChatDB("ADDON_WHISPER", player->GetSession()->GetPlayerName(), receiver ? receiver->GetSession()->GetPlayerName() : "<unknown>", msg.c_str(), "Null", player->GetZoneId());
    }

    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Group* group)
    {
        //! NOTE:
        //! LANG_ADDON can only be sent by client in "PARTY", "RAID", "GUILD", "BATTLEGROUND", "WHISPER"
        switch (type)
        {
            case CHAT_MSG_PARTY:
                if (lang != LANG_ADDON && sWorld->getBoolConfig(CONFIG_CHATLOG_PARTY))
					sLog->outChatDB("PARTY", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), group ? group->GetLeaderName() : "<unknown>", player->GetZoneId());
                else if (lang == LANG_ADDON && sWorld->getBoolConfig(CONFIG_CHATLOG_ADDON))
					sLog->outChatDB("ADDON_PARTY", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), group ? group->GetLeaderName() : "<unknown>", player->GetZoneId());
                break;

            case CHAT_MSG_PARTY_LEADER:
                if (sWorld->getBoolConfig(CONFIG_CHATLOG_PARTY))
					sLog->outChatDB("PARTY", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), group ? group->GetLeaderName() : "<unknown>", player->GetZoneId());
                break;

            case CHAT_MSG_RAID:
                if (lang != LANG_ADDON && sWorld->getBoolConfig(CONFIG_CHATLOG_RAID))
					sLog->outChatDB("RAID", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), group ? group->GetLeaderName() : "<unknown>", player->GetZoneId());
                else if (lang == LANG_ADDON && sWorld->getBoolConfig(CONFIG_CHATLOG_ADDON))
					sLog->outChatDB("ADDON_RAID", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), group ? group->GetLeaderName() : "<unknown>", player->GetZoneId());
                break;

            case CHAT_MSG_RAID_LEADER:
                if (sWorld->getBoolConfig(CONFIG_CHATLOG_RAID))
					sLog->outChatDB("RAID", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), group ? group->GetLeaderName() : "<unknown>", player->GetZoneId());
                break;

            case CHAT_MSG_RAID_WARNING:
                if (sWorld->getBoolConfig(CONFIG_CHATLOG_RAID))
					sLog->outChatDB("RAID", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), group ? group->GetLeaderName() : "<unknown>", player->GetZoneId());
                break;

            case CHAT_MSG_BATTLEGROUND:
                if (lang != LANG_ADDON && sWorld->getBoolConfig(CONFIG_CHATLOG_BGROUND))
					sLog->outChatDB("BATTLEGROUND", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), group ? group->GetLeaderName() : "<unknown>", player->GetZoneId());
                else if (lang == LANG_ADDON && sWorld->getBoolConfig(CONFIG_CHATLOG_ADDON))
					sLog->outChatDB("BATTLEGROUND", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), group ? group->GetLeaderName() : "<unknown>", player->GetZoneId());
                break;

            case CHAT_MSG_BATTLEGROUND_LEADER:
                if (sWorld->getBoolConfig(CONFIG_CHATLOG_BGROUND))
					sLog->outChatDB("BATTLEGROUND", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), group ? group->GetLeaderName() : "<unknown>", player->GetZoneId());
                break;
        }
    }

    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild)
    {
        switch (type)
        {
            case CHAT_MSG_GUILD:
                if (lang != LANG_ADDON && sWorld->getBoolConfig(CONFIG_CHATLOG_GUILD))
					sLog->outChatDB("GUILD", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), guild ? guild->GetName().c_str() : "<unknown>", player->GetZoneId());
                else if (lang == LANG_ADDON && sWorld->getBoolConfig(CONFIG_CHATLOG_ADDON))
					sLog->outChatDB("ADDON_GUILD", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), guild ? guild->GetName().c_str() : "<unknown>", player->GetZoneId());
                break;

            case CHAT_MSG_OFFICER:
                if (sWorld->getBoolConfig(CONFIG_CHATLOG_GUILD))
					sLog->outChatDB("OFFICER_GUILD", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), guild ? guild->GetName().c_str() : "<unknown>", player->GetZoneId());
                break;
        }
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Channel* channel)
    {
        bool isSystem = channel &&
                        (channel->HasFlag(CHANNEL_FLAG_TRADE) ||
                         channel->HasFlag(CHANNEL_FLAG_GENERAL) ||
                         channel->HasFlag(CHANNEL_FLAG_CITY) ||
                         channel->HasFlag(CHANNEL_FLAG_LFG));


        if (sWorld->getBoolConfig(CONFIG_CHATLOG_SYSCHAN) && isSystem)
			sLog->outChatDB("SYSTEM_CHANNEL", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), channel ? channel->GetName().c_str() : "<unknown>", player->GetZoneId());

		else if (sWorld->getBoolConfig(CONFIG_CHATLOG_CHANNEL))
			sLog->outChatDB("PLAYER_CHANNEL", player->GetSession()->GetPlayerName(), "Null", msg.c_str(), channel ? channel->GetName().c_str() : "<unknown>", player->GetZoneId());
		}
};

void AddSC_chat_log()
{
    new ChatLogScript();
}
