#pragma once
#include "../Framework/ImGui/imgui.h"
#include "../Framework/ImGui/imgui_impl_win32.h"
#include "../Framework/ImGui/imgui_impl_dx11.h"
#include "../Framework/ImGui/Custom.h"
#include "../Framework/ImGui/Fonts/fa.h"
#include "../Framework/ImGui/Fonts/RobotoRegular.h"
#include "../Framework/ImGui/Fonts/IconsFontAwesome6.h"
#include "SDK/CPlayer/CPlayer.h"
#include "SDK/CExfil/CExfil.h"
#include "SDK/CItem/CItem.h"
#include <mutex>

class CFramework
{
public:
    bool Init();
    void UpdateList();
    void UpdateStaticList();
	void RenderInfo();
	void RenderMenu();
	void RenderESP();
    void MultiFeatures();
private:
    ImFont* icon{ nullptr };
    CGame tarkov;
    
    // スレッドセーフにする
    std::mutex m_mtx_fast;
    std::mutex m_mtx_slow;
    CPlayer m_localplayer;
    std::vector<CPlayer> m_vecEntityList;
    std::vector<CExfil> m_vecExfilList;
    std::vector<CItem> m_vecItemList;
    std::vector<uintptr_t> m_vecGrenadeList;

    // Colors(UI)
    ImColor Col_Text_Default{ 1.f, 1.f, 1.f, 1.f };
    ImColor Col_Text_Attention{ 1.f, 1.f, 0.f, 1.f };
    ImColor Col_Text_Warning{ 1.f, 0.f, 0.f, 1.f };
    ImColor Col_Crosshair{ 0.f, 1.f, 0.f, 1.f };

    // Colors(Player/NPC)
    ImColor Col_ESP_PMC{ 1.f, 0.f, 0.85f, 1.f };
    ImColor Col_ESP_Team{ 0.f, 1.f, 0.f, 0.f };
    ImColor Col_ESP_Scav{ 1.f, 1.f, 1.f, 1.f };
    ImColor Col_ESP_pScav{ 1.f, 1.f, 0.f, 1.f };
    ImColor Col_ESP_SpecialScav{ 1.f, 0.5f, 0.f, 1.f };
    ImColor Col_ESP_Boss{ 1.f, 0.f, 0.f, 1.f };
    ImColor Col_ESP_Filled{ 0.f, 0.f, 0.f, 0.25f };

    ImColor Col_ESP_ExfilOpen{ 0.f, 1.f, 0.f, 0.5f };
    ImColor Col_ESP_ExfilClose{ 1.f, 0.3f, 0.f, 0.5f };

    ImColor Col_ESP_Corpse{ 1.f, 1.f, 1.f, 0.9f };
    ImColor Col_ESP_Item_Normal{ 1.f, 1.f, 1.f, 0.7f };
    ImColor Col_ESP_Item_Mid{ 1.f, 0.6f, 0.f, 0.7f };
    ImColor Col_ESP_Item_Rare{ 1.f, 0.f, 0.f, 0.7f };

    void GetESPInfo(const int& SpawnType, std::string& vOutStr, ImColor& vOutColor);
};

class Renderer
{
public:
    ImColor TEXT_COLOR{ 1.f, 1.f, 1.f, 1.f };

    // Render.cpp
    ImVec2 ToImVec2(const ImVec2& value); // Convert to int
    ImVec2 ToImVec2(const Vector2& value);
    ImColor ApplyAlpha(const ImColor& color, const float& alpha);
    float GetHueFromTime(float speed = 5.0f);
    ImColor GenerateRainbow(float speed = 5.0f);
    void Line(const Vector2 p1, const Vector2 p2, ImColor color, float thickness = 1.f);
    void Circle(const Vector2 pos, float size, ImColor color);
    void Rect(Vector2 min, Vector2 max, ImColor color);
    void CorneredBox(Vector2 min, Vector2 max, int scale, ImColor color);
    void RectFilled(int x0, int y0, int x1, int y1, ImColor color);
    void HealthBar(int x, int y, int w, int h, int value, int v_max);
    void String(const Vector2 pos, ImColor color, const char* text);
    void StringEx(Vector2 pos, ImColor shadow_color,  float font_size, const char* text);
};