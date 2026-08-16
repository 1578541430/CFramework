#include "Framework.h"

void CFramework::MultiFeatures()
{
    // BasePointer
    uintptr_t Physics = m.Read<uintptr_t>(m_localplayer.m_address + offset::Player::pPhysics);
    uintptr_t BreathEffector = m.Read<uintptr_t>(m_localplayer.m_pWeaponAnimation + offset::WeaponAnimations::Breath);
    uintptr_t Stamina = m.Read<uintptr_t>(Physics + offset::Physics::Stamina);

    // No Recoil/Sway
    if (g.g_NoSway)
    {
        uintptr_t pwa = m_localplayer.m_pWeaponAnimation;
        if (!pwa) return;

        uintptr_t shooting = m.Read<uintptr_t>(pwa + 0x50);          // Shootingg
        if (shooting)
        {
            uintptr_t newShotRecoil = m.Read<uintptr_t>(shooting + 0x18); // NewShotRecoil
            if (newShotRecoil)
                m.Write<bool>(newShotRecoil + 0x49, false);           // RecoilEffectOn = false
        }

        uintptr_t breath = m.Read<uintptr_t>(pwa + 0x30);
        if (breath)
            m.Write<float>(breath + 0xA4, 0.f);                       // Intensity = 0

        uintptr_t motionReact = m.Read<uintptr_t>(pwa + 0x40);
        if (motionReact)
            m.Write<float>(motionReact + 0xD0, 0.f);                  // Intensity = 0

        uintptr_t walk = m.Read<uintptr_t>(pwa + 0x38);
        if (walk)
            m.Write<float>(walk + 0x44, 0.f);                         // Intensity = 0

        uintptr_t handsContainer = m.Read<uintptr_t>(pwa + 0x20);
        if (handsContainer)
        {
            uintptr_t handsPos = m.Read<uintptr_t>(handsContainer + 0x38);
            uintptr_t handsRot = m.Read<uintptr_t>(handsContainer + 0x40);

            Vector3 zero = { 0.f, 0.f, 0.f };
            if (handsPos)
                m.Write<Vector3>(handsPos + 0x80, zero);              // Current = 0
            if (handsRot)
                m.Write<Vector3>(handsRot + 0x80, zero);              // Current = 0
        }

        m.Write<int>(pwa + 0x140, 1);
    }

    // InfStamina
    if (g.g_InfStamina && m.Read<float>(Stamina + 0x48) < 85.f)
        m.Write<float>(Stamina + 0x48, 100.f);

    // NoFall Damage
    if (g.g_NoFallDmg && m.Read<float>(Physics + offset::Physics::FallDamageMultiplier) != 0.f)
        m.Write<float>(Physics + offset::Physics::FallDamageMultiplier, 0.f);

    //  GodMode
    if (g.g_GodMode)
    {
        uintptr_t healthCtrl = m.Read<uintptr_t>(m_localplayer.m_address + offset::Player::pHealthController);
        if (!healthCtrl)
            return;

        m.Write<float>(healthCtrl + offset::HealthController::FallSafeHeight, 9999999.f);

        for (int i = 0; i < 2; i++)
        {
            uintptr_t healthValue = m.Read<uintptr_t>(healthCtrl + offset::HealthController::HealthValue_0 + (i * 0x8));
            if (healthValue)
            {
                uintptr_t valueStruct = m.Read<uintptr_t>(healthValue + 0x10);
                if (valueStruct)
                {
                    float maximum = m.Read<float>(valueStruct + offset::ValueStruct::Maximum);
                    if (maximum > 0.f)
                        m.Write<float>(valueStruct + offset::ValueStruct::Current, maximum);
                }
            }
        }

        if (m_localplayer.m_pBodyController)
        {
            for (int j = 0; j < 7; j++)
            {
                uintptr_t body_part = m.Read<uintptr_t>(m_localplayer.m_pBodyController + 0x30 + (j * 0x18));
                if (!body_part) continue;

                uintptr_t health_container = m.Read<uintptr_t>(body_part + 0x10);
                if (!health_container) continue;

                m.Write<float>(health_container + 0x14, 999.f);

                m.Write<float>(health_container + 0x10, 999.f);
            }
        }
        auto ClearEffectList = [&](uintptr_t listAddr)
            {
                uintptr_t list = m.Read<uintptr_t>(listAddr);
                if (!list) return;

                int size = m.Read<int>(list + 0x18);
                if (size <= 0 || size > 64) return;

                uintptr_t items = m.Read<uintptr_t>(list + 0x10);
                if (!items) return;

                for (int i = 0; i < size; i++)
                {
                    uintptr_t effect = m.Read<uintptr_t>(items + 0x20 + (i * 0x8));
                    if (!effect) continue;

                    int state = m.Read<int>(effect + 0x30);
                    if (state != 4)
                        m.Write<int>(effect + 0x30, 4);
                }
            };

        ClearEffectList(healthCtrl + 0x88); // List_1
        ClearEffectList(healthCtrl + 0x90); // List_2
    }
	//NoJam/NoDurability
    if (g.g_NoJam || g.g_NoDurability)
    {
        uintptr_t handsCtrl = m.Read<uintptr_t>(m_localplayer.m_address + 0x680); // _handsController
        if (!handsCtrl)
            return;

        uintptr_t weapon = m.Read<uintptr_t>(handsCtrl + 0x68); // item_0
        if (!weapon)
            return;

        uintptr_t templateAddr = m.Read<uintptr_t>(weapon + 0x48); // WeaponTemplate
        if (templateAddr)
        {
            m.Write<float>(templateAddr + 0x1C, 0.f);  // BaseMalfunctionChance = 0
            m.Write<float>(templateAddr + 0x20, 0.f);  // AllowJam = false
            m.Write<float>(templateAddr + 0x24, 0.f);  // AllowMisfire = false
            m.Write<float>(templateAddr + 0x28, 0.f);  // AllowFeed = true
            m.Write<float>(templateAddr + 0x2C, 0.f);  // FailureToFeed = 0
            m.Write<float>(templateAddr + 0x30, 0.f);  // FailureToEject = 0
            m.Write<float>(templateAddr + 0x34, 0.f);  // Overheat = 0
            m.Write<float>(templateAddr + 0x38, 0.f);  // JamChance = 0
        }

        if (g.g_NoDurability)
        {
            uintptr_t repairable = m.Read<uintptr_t>(weapon + 0x90); // Repairable
            if (repairable)
            {
                float maxDur = m.Read<float>(repairable + 0x20); // MaxDurability
                float curDur = m.Read<float>(repairable + 0x24); // Durability

                if (maxDur > 0.f && curDur < maxDur)
                    m.Write<float>(repairable + 0x24, maxDur);
            }
        }
    }
    //Infinite Ammo
    if (g.g_InfAmmo)
    {
        uintptr_t handsCtrl = m.Read<uintptr_t>(m_localplayer.m_address + 0x680);
        if (!handsCtrl) return;

        uintptr_t weapon = m.Read<uintptr_t>(handsCtrl + 0x68);
        if (!weapon) return;

        uintptr_t magSlot = m.Read<uintptr_t>(weapon + 0xC8);
        if (!magSlot) return;

        uintptr_t magazine = m.Read<uintptr_t>(magSlot + 0x38);
        if (!magazine) return;

        m.Write<int>(magazine + 0xA8, 999);

        uintptr_t stackSlot = m.Read<uintptr_t>(magazine + 0xA0);
        if (stackSlot)
        {
            uintptr_t itemsList = m.Read<uintptr_t>(stackSlot + 0x10);
            if (itemsList)
            {
                int size = m.Read<int>(itemsList + 0x18);
                uintptr_t itemsArr = m.Read<uintptr_t>(itemsList + 0x10);

                if (itemsArr && size > 0 && size < 32)
                {
                    for (int i = 0; i < size; i++)
                    {
                        uintptr_t ammo = m.Read<uintptr_t>(itemsArr + 0x20 + (i * 0x8));
                        if (!ammo) continue;

                        int maxCount = m.Read<int>(ammo + 0x38); // StackSlot::MaxCount
                        if (maxCount > 0)
                        {
                            m.Write<int>(ammo + 0x64, maxCount); // StackObjectsCount = MaxCount
                        }
                    }
                }
            }
        }
    }
}

void CFramework::GetESPInfo(const int& SpawnType, std::string& vOutStr, ImColor& vOutColor)
{
    switch (SpawnType)
    {
    case SCAV:
        vOutStr = "";
        vOutColor = Col_ESP_Scav;
        break;
    case SNIPER_SCAV:
        vOutStr = "Sniper";
        vOutColor = Col_ESP_Scav;
        break;
    case RESHALA_BOSS:
        vOutStr = "Reshala";
        vOutColor = Col_ESP_Boss;
        break;
    case RESHALA_FOLLOW:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KILLA_BOSS:
        vOutStr = "Killa";
        vOutColor = Col_ESP_Boss;
        break;
    case SHTURMAN_BOSS:
        vOutStr = "Shturman";
        vOutColor = Col_ESP_Boss;
        break;
    case SHTURMAN_FOLLOW:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case GLUKHAR_BOSS:
        vOutStr = "Glukhar";
        vOutColor = Col_ESP_Boss;
        break;
    case GLUKHAR_FOLLOW_01:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case GLUKHAR_FOLLOW_02:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case GLUKHAR_FOLLOW_03:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case SANITOR_BOSS:
        vOutStr = "Sanitor";
        vOutColor = Col_ESP_Boss;
        break;
    case SANITOR_FOLLOW:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case NORMAL_SCAV:
        vOutStr = "Scav";
        vOutColor = Col_ESP_Scav;
        break;
    case CULTIST_01_SCAV:
        vOutStr = "Cultist";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case CULTIST_02_SCAV:
        vOutStr = "Cultist";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case TAGILLA_BOSS:
        vOutStr = "Tagilla";
        vOutColor = Col_ESP_Boss;
        break;
    case ROGUE_SCAV:
        vOutStr = "Rogue";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case ZRYACHIY_BOSS:
        vOutStr = "Zryachiy";
        vOutColor = Col_ESP_Boss;
        break;
    case ZRYACHIY_FOLLOW:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KABAN_BOSS:
        vOutStr = "Kaban";
        vOutColor = Col_ESP_Boss;
        break;
    case KABAN_FOLLOW_0:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KABAN_FOLLOW_1:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KABAN_FOLLOW_2:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KABAN_FOLLOW_3:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KOLLONTAY_BOSS:
        vOutStr = "Kollontay";
        vOutColor = Col_ESP_Boss;
        break;
    case KOLLONTAY_FOLLOW_01:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KOLLONTAY_FOLLOW_02:
        vOutStr = "follower";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case BTR_VEHICLE:
        vOutStr = "BTR-82";
        vOutColor = ImColor(1.f, 1.f, 1.f, 1.f);
        break;
    case SCAV_PARTISAN:
        vOutStr = "Partisan";
        vOutColor = Col_ESP_Scav;
        break;
    case RAIDER_SCAV:
        vOutStr = "Raider";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case KNIGHT_SCAV:
        vOutStr = "Knight";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case BIGPIPE_SCAV:
        vOutStr = "BigPipe";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case BRIDEYE_SCAV:
        vOutStr = "Birdeye";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case BLOODHOUND_SCAV:
        vOutStr = "Bloodhound";
        vOutColor = Col_ESP_SpecialScav;
        break;
    case PMC_BEAR_PvE:
        vOutStr = "BEAR";
        vOutColor = Col_ESP_PMC;
        break;
    case PMC_USEC_PvE:
        vOutStr = "USEC";
        vOutColor = Col_ESP_PMC;
        break;
    case PMC_BEAR_NEW:
        vOutStr = "BEAR";
        vOutColor = Col_ESP_PMC;
        break;
    case PMC_USEC_NEW:
        vOutStr = "USEC";
        vOutColor = Col_ESP_PMC;
        break;
    default:
        vOutStr = "InValid";
        vOutColor = ImColor(1.f, 1.f, 1.f, 1.f);
        break;
    };
}