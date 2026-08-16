#pragma once
#include <Windows.h>

struct Globals
{
    // System
    bool process_active = true;
    bool ShowMenu = true;

    // GameWindow Data
    HWND GameHwnd;
    RECT GameRect{};
    POINT GamePoint{};

    // Visual
    bool g_ESP      = true;
    bool g_ESP_Item      = true;
    bool g_ESP_Corpse = true;
    bool g_ESP_Exfil     = true;
    bool g_ESP_Grenade   = true;
    bool g_ESP_Line      = false;
    bool g_ESP_Box       = true;
    bool g_ESP_BoxFilled = false;
    bool g_ESP_Skeleton  = true;
    bool g_ESP_Distance  = true;
    bool g_ESP_Name      = true;
    bool g_ESP_HealthBar = true;
    int  g_ESP_BoxStyle  = 1;
    int g_ESP_ItemPrice = 50000;
    float g_ESP_MaxDistance = 500.f;
    float g_ESP_MaxItemDistance = 50.f;

    // Misc
    bool g_GodMode = false;
    bool g_NoSway     = true;
    bool g_InfStamina = true;
    bool g_NoFallDmg  = true;
    bool g_NoJam = false;
    bool g_NoDurability = true;
    bool g_InfAmmo = false;

    // System
    bool g_StreamProof = true;
    bool g_Crosshair = true;
    int g_CrosshairSize = 3;
    int g_CrosshairType = 0;

    // Key
    int g_MenuKey = VK_INSERT;
    int g_AimKey0 = VK_RBUTTON;
    int g_AimKey1 = VK_LBUTTON;
};

extern Globals g;