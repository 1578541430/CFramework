#include "Framework.h"

float Renderer::GetHueFromTime(float speed) {
    float t = static_cast<float>(ImGui::GetTime());
    return fmodf(t / speed, 1.0f);
}

ImColor Renderer::GenerateRainbow(float speed) {
    float hue = GetHueFromTime(speed);
    return ImColor::HSV(hue, 1.0f, 1.0f);
}

ImVec2 Renderer::ToImVec2(const ImVec2& value) {
    return ImVec2((int)value.x, (int)value.y);
}

ImVec2 Renderer::ToImVec2(const Vector2& value) {
    return ImVec2((int)value.x, (int)value.y);
}

ImColor Renderer::ApplyAlpha(const ImColor& color, const float& alpha) {
    return ImColor(color.Value.x, color.Value.y, color.Value.z, alpha);
}

void Renderer::Line(const Vector2 p1, const Vector2 p2, ImColor color, float thickness)
{
    ImGui::GetBackgroundDrawList()->AddLine(ToImVec2(p1), ToImVec2(p2), color, thickness);
}

void Renderer::Circle(const Vector2 pos, float size, ImColor color)
{
    ImGui::GetBackgroundDrawList()->AddCircle(ToImVec2(pos), size, color);
}

void Renderer::Rect(Vector2 min, Vector2 max, ImColor color)
{
    ImGui::GetBackgroundDrawList()->AddRect(ToImVec2(Vector2(min)), ToImVec2(Vector2(max)), color);
}

void Renderer::CorneredBox(Vector2 min, Vector2 max, int scale, ImColor color)
{
    Line(Vector2(min.x, min.y), Vector2(min.x + scale, min.y), color); // Top
    Line(Vector2(max.x, min.y), Vector2(max.x - scale, min.y), color);
    Line(Vector2(min.x, min.y), Vector2(min.x, min.y + scale), color); // Left
    Line(Vector2(min.x, max.y), Vector2(min.x, max.y - scale), color);
    Line(Vector2(max.x, min.y), Vector2(max.x, min.y + scale), color); // Right
    Line(Vector2(max.x, max.y), Vector2(max.x, max.y - scale), color);
    Line(Vector2(min.x, max.y), Vector2(min.x + scale, max.y), color); // Bottom
    Line(Vector2(max.x + 1, max.y), Vector2(max.x - scale, max.y), color);
}

void Renderer::RectFilled(int x0, int y0, int x1, int y1, ImColor color)
{
    ImGui::GetBackgroundDrawList()->AddRectFilled(ToImVec2(Vector2(x0, y0)), ToImVec2(Vector2(x1, y1)), color);
}

void Renderer::HealthBar(int x, int y, int w, int h, int value, int v_max)
{
    RectFilled(x, y, x + w, y + h, ImColor(0.f, 0.f, 0.f, 0.85f));
    RectFilled(x, y, x + w, y + ((h / float(v_max)) * (float)value), ImColor(min(510 * (v_max - value) / 100, 255), min(510 * value / 100, 255), 25, 255));
}

void Renderer::String(const Vector2 pos, ImColor color, const char* text)
{
    ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ToImVec2(pos), color, text, text + strlen(text), 512);
}

void Renderer::StringEx(Vector2 pos, ImColor shadow_color, float font_size, const char* text)
{
    ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), font_size, ToImVec2(Vector2(pos.x + 1.f, pos.y + 1.f)), shadow_color, text, text + strlen(text), 512, 0); // Shadow
    ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ToImVec2(pos), TEXT_COLOR, text, text + strlen(text), 512); // Text
}