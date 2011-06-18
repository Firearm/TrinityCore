/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
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
#include "oculus.h"

#define GOSSIP_ITEM_DRAKES         "So where do we go from here?"
#define GOSSIP_ITEM_BELGARISTRASZ1 "I want to fly on the wings of the Red Flight"
#define GOSSIP_ITEM_BELGARISTRASZ2 "What abilities do Ruby Drakes have?"
#define GOSSIP_ITEM_VERDISA1       "I want to fly on the wings of the Green Flight"
#define GOSSIP_ITEM_VERDISA2       "What abilities do Emerald Drakes have?"
#define GOSSIP_ITEM_ETERNOS1       "I want to fly on the wings of the Bronze Flight"
#define GOSSIP_ITEM_ETERNOS2       "What abilities do Amber Drakes have?"

#define HAS_ESSENCE(a) ((a)->HasItemCount(ITEM_EMERALD_ESSENCE, 1) || (a)->HasItemCount(ITEM_AMBER_ESSENCE, 1) || (a)->HasItemCount(ITEM_RUBY_ESSENCE, 1))

enum Drakes
{
    GOSSIP_TEXTID_DRAKES                          = 13267,
    GOSSIP_TEXTID_BELGARISTRASZ1                  = 12916,
    GOSSIP_TEXTID_BELGARISTRASZ2                  = 13466,
    GOSSIP_TEXTID_BELGARISTRASZ3                  = 13254,
    GOSSIP_TEXTID_VERDISA1                        = 1,
    GOSSIP_TEXTID_VERDISA2                        = 1,
    GOSSIP_TEXTID_VERDISA3                        = 1,
    GOSSIP_TEXTID_ETERNOS1                        = 1,
    GOSSIP_TEXTID_ETERNOS2                        = 1,
    GOSSIP_TEXTID_ETERNOS3                        = 13256,

    ITEM_EMERALD_ESSENCE                          = 37815,
    ITEM_AMBER_ESSENCE                            = 37859,
    ITEM_RUBY_ESSENCE                             = 37860,

    NPC_VERDISA                                   = 27657,
    NPC_BELGARISTRASZ                             = 27658,
    NPC_ETERNOS                                   = 27659,

	SPELL_SHOCK_CHARGE                            = 49836,
	SPELL_MARTYR                                  = 50253
};

class npc_oculus_drake : public CreatureScript
{
public:
    npc_oculus_drake() : CreatureScript("npc_oculus_drake") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch(pCreature->GetEntry())
        {
        case NPC_VERDISA: //Verdisa
            switch(uiAction)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (!HAS_ESSENCE(pPlayer))
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VERDISA1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VERDISA2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VERDISA1, pCreature->GetGUID());
                }
                else
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_VERDISA2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VERDISA2, pCreature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
            {
                ItemPosCountVec dest;
                uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_EMERALD_ESSENCE, 1);
                if (msg == EQUIP_ERR_OK)
                    pPlayer->StoreNewItem(dest, ITEM_EMERALD_ESSENCE, true);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 3:
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VERDISA3, pCreature->GetGUID());
                break;
            }
            break;
        case NPC_BELGARISTRASZ: //Belgaristrasz
            switch(uiAction)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (!HAS_ESSENCE(pPlayer))
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BELGARISTRASZ1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BELGARISTRASZ2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_BELGARISTRASZ1, pCreature->GetGUID());
                }
                else
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BELGARISTRASZ2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_BELGARISTRASZ2, pCreature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
            {
                ItemPosCountVec dest;
                uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_RUBY_ESSENCE, 1);
                if (msg == EQUIP_ERR_OK)
                    pPlayer->StoreNewItem(dest, ITEM_RUBY_ESSENCE, true);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 3:
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_BELGARISTRASZ3, pCreature->GetGUID());
                break;
            }
            break;
        case NPC_ETERNOS: //Eternos
            switch(uiAction)
            {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (!HAS_ESSENCE(pPlayer))
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ETERNOS1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ETERNOS2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ETERNOS1, pCreature->GetGUID());
                }
                else
                {
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ETERNOS2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ETERNOS2, pCreature->GetGUID());
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
            {
                ItemPosCountVec dest;
                uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_AMBER_ESSENCE, 1);
                if (msg == EQUIP_ERR_OK)
                    pPlayer->StoreNewItem(dest, ITEM_AMBER_ESSENCE, true);
                pPlayer->CLOSE_GOSSIP_MENU();
                break;
            }
            case GOSSIP_ACTION_INFO_DEF + 3:
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ETERNOS3, pCreature->GetGUID());
                break;
            }
            break;
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            if (instance->GetBossState(DATA_DRAKOS_EVENT) == DONE)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DRAKES, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DRAKES, creature->GetGUID());
            }
        }

        return true;
    }

};



class spell_emerald_drake_touch_the_nightmare : public SpellScriptLoader
{
public:
    spell_emerald_drake_touch_the_nightmare() : SpellScriptLoader("spell_emerald_drake_touch_the_nightmare") { }

    class spell_emerald_drake_touch_the_nightmare_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_emerald_drake_touch_the_nightmare_SpellScript);

        void OnHitEffect()
        {
            if(GetCaster())
                GetCaster()->DealDamage(GetCaster(), (GetCaster()->GetMaxHealth()*3/10)/2);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_emerald_drake_touch_the_nightmare_SpellScript::OnHitEffect);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_emerald_drake_touch_the_nightmare_SpellScript();
    }
};

class spell_amber_drake_schock_lance : public SpellScriptLoader
{
public:
    spell_amber_drake_schock_lance() : SpellScriptLoader("spell_amber_drake_schock_lance") { }

    class spell_amber_drake_schock_lance_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_amber_drake_schock_lance_SpellScript);

        void RecalculateDamage()
        {
            if(Aura* aur = GetHitUnit()->GetAura(SPELL_SHOCK_CHARGE, GetHitUnit()->GetGUID()))
            {
                SetHitDamage(6525*aur->GetStackAmount());
                aur->Remove();
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_amber_drake_schock_lance_SpellScript::RecalculateDamage);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_amber_drake_schock_lance_SpellScript();
    }
};

class spell_amber_drake_time_stop : public SpellScriptLoader
{
public:
    spell_amber_drake_time_stop() : SpellScriptLoader("spell_amber_drake_time_stop") { }

    class spell_amber_drake_time_stop_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_amber_drake_time_stop_SpellScript);

        void OnHitEffect()
        {
            if(GetHitUnit())
            {
                GetHitUnit()->SetAuraStack(SPELL_SHOCK_CHARGE, GetHitUnit(), 5);
                if(GetCaster() && GetCaster()->HasAura(SPELL_SHOCK_CHARGE))
                    GetCaster()->RemoveAura(SPELL_SHOCK_CHARGE);
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_amber_drake_time_stop_SpellScript::OnHitEffect);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_amber_drake_time_stop_SpellScript();
    }
};

class spell_amber_drake_temporal_rift : public SpellScriptLoader
{
    public:
        spell_amber_drake_temporal_rift() : SpellScriptLoader("spell_amber_drake_temporal_rift") { }

        class spell_amber_drake_temporal_rift_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_amber_drake_temporal_rift_AuraScript);

            uint32 TargetHealth;
            uint32 damage;

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {	
                if(GetTarget())
                    TargetHealth = GetTarget()->GetHealth();
                damage = 0;
            }

            void HandlePeriodicTick(AuraEffect const* /*aurEff*/)
            {
                if(damage = damage + (TargetHealth - GetTarget()->GetHealth()))
                {
                    for( ; damage >= 15000; damage=damage-15000)
                        GetTarget()->AddAura(SPELL_SHOCK_CHARGE, GetTarget());
                    TargetHealth = GetTarget()->GetHealth();
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_amber_drake_temporal_rift_AuraScript::OnApply, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_amber_drake_temporal_rift_AuraScript::HandlePeriodicTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_amber_drake_temporal_rift_AuraScript();
        }
};

class npc_oculus_drakes : public CreatureScript
{
public:
    npc_oculus_drakes() : CreatureScript("npc_oculus_drakes") { }

    struct npc_oculus_drakesAI : public ScriptedAI
    {
        npc_oculus_drakesAI(Creature *c) : ScriptedAI(c) {}

        void Reset()
        {
            me->SetSpeed(MOVE_FLIGHT, (float)2.8);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
	    return new npc_oculus_drakesAI(creature);
    }
};

void AddSC_oculus()
{
    new npc_oculus_drake();
    new spell_emerald_drake_touch_the_nightmare();
    new spell_amber_drake_schock_lance();
    new spell_amber_drake_time_stop();
    new spell_amber_drake_temporal_rift();
    new npc_oculus_drakes();
}
