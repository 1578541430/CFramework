#include "Framework.h"

// ImGui::Combo / List 用字符串
const char* BoxTypeList[]{ u8"简易", u8"四角" };
const char* CrosshairList[]{ u8"十字", u8"圆圈" };
std::vector<const char*> MenuStringList{ u8"视觉", u8"功能", u8"设置" };
std::vector<const char*> MenuIconList{ ICON_FA_EYE, ICON_FA_BARS, ICON_FA_GEAR };

void CFramework::RenderMenu()
{
    // Setup
    static int Index = 0;
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    ImGui::SetNextWindowBgAlpha(0.975f);
    ImGui::SetNextWindowSize(ImVec2(725.f, 450.f));
    ImGui::Begin(u8"SPT-AKI 4.0.X 外部修改器", &g.ShowMenu, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    //---// Child 0 //-----------------------------------//
    ImGui::BeginChild("##SelectChild", ImVec2(150.f, ImGui::GetContentRegionAvail().y), false);

    ImGui::SetCursorPosY(25.f);

    ImGui::PushFont(icon);

    for (int i = 0; i < MenuIconList.size(); i++) {
        if (ImGui::CustomButton(MenuIconList[i], MenuStringList[i], ImVec2(ImGui::GetContentRegionAvail().x, 35.f), Index == i ? true : false))
            Index = i;
    }

    ImGui::PopFont();

    ImGui::EndChild();
    //---// Child 0 End //-------------------------------//

    ImGui::SameLine();

    //---// Child 1 //-----------------------------------//
    ImGui::BeginChild("##MainChild", ImVec2(ImGui::GetContentRegionAvail()), false);

    //---// Left //--------------------------------------//
    ImGui::BeginChild("##LeftChild", ImVec2(ImGui::GetContentRegionAvail().x / 2.f - (style.WindowPadding.x * 2), ImGui::GetContentRegionAvail().y), false);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 1.f));

    switch (Index)
    {
    case 0: // 视觉
        ImGui::BeginChild("##C000", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y / 2.5f), true);

        ImGui::Text(u8"视觉功能");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox(u8"人物透视", &g.g_ESP);
        ImGui::Checkbox(u8"物品透视", &g.g_ESP_Item);
        ImGui::Checkbox(u8"尸体透视", &g.g_ESP_Corpse);
        ImGui::Checkbox(u8"撤离点透视", &g.g_ESP_Exfil);
        ImGui::Checkbox(u8"手雷透视", &g.g_ESP_Grenade);

        ImGui::EndChild();
        ImGui::BeginChild("##C001", ImVec2(ImGui::GetContentRegionAvail()), true);

        ImGui::Text(u8"透视选项");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox(u8"射线", &g.g_ESP_Line);
        ImGui::Checkbox(u8"方框", &g.g_ESP_Box);
        ImGui::Checkbox(u8"填充方框", &g.g_ESP_BoxFilled);
        ImGui::Checkbox(u8"骨骼", &g.g_ESP_Skeleton);
        ImGui::Checkbox(u8"距离", &g.g_ESP_Distance);
        ImGui::Checkbox(u8"名称", &g.g_ESP_Name);
        ImGui::Checkbox(u8"血条", &g.g_ESP_HealthBar);

        ImGui::EndChild();
        break;

    case 1: // 功能
        ImGui::BeginChild("##C010", ImVec2(ImGui::GetContentRegionAvail()), true);

        ImGui::Text(u8"杂项功能");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox(u8"无后坐力", &g.g_NoSway);
        ImGui::Checkbox(u8"无限体力", &g.g_InfStamina);
        ImGui::Checkbox(u8"无摔落伤害", &g.g_NoFallDmg);
        ImGui::Checkbox(u8"上帝模式", &g.g_GodMode);
        ImGui::Checkbox(u8"武器不卡壳", &g.g_NoJam);
        ImGui::Checkbox(u8"武器不掉耐久", &g.g_NoDurability);
        ImGui::Checkbox(u8"无限子弹", &g.g_InfAmmo);

        ImGui::EndChild();
        break;

    case 2: // 设置
        ImGui::BeginChild("##C020", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y / 3.f), true);
        ImGui::Text(u8"系统");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox(u8"直播防检测", &g.g_StreamProof);

        ImGui::EndChild();
        ImGui::BeginChild("##C021", ImVec2(ImGui::GetContentRegionAvail()), true);

        ImGui::Text(u8"准星");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox(u8"显示准星", &g.g_Crosshair);
        ImGui::CustomSliderInt(u8"准星大小", "##SizeCH", &g.g_CrosshairSize, 1, 10);
        ImGui::ColorEdit4(u8"准星颜色##C", &Col_Crosshair.Value.x);
        ImGui::Combo(u8"准星类型##C", &g.g_CrosshairType, CrosshairList, IM_ARRAYSIZE(CrosshairList));

        ImGui::EndChild();
        break;

    default:
        break;
    }

    ImGui::PopStyleColor();

    ImGui::EndChild();
    //---------------------------------------------------//

    ImGui::SameLine();

    //---// Right //--------------------------------------//
    ImGui::BeginChild("##RightChild", ImVec2(ImGui::GetContentRegionAvail()), false);

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 1.f));

    switch (Index)
    {
    case 0: // 视觉右侧
        ImGui::BeginChild("##C100", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y / 2.f), true);

        ImGui::Text(u8"透视设置");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::CustomSliderFloat(u8"人物距离", "##Dist", &g.g_ESP_MaxDistance, 100.f, 2000.f);
        ImGui::CustomSliderFloat(u8"物品距离", "##ItemDist", &g.g_ESP_MaxItemDistance, 10.f, 1000.f);
        ImGui::CustomSliderInt(u8"最低价格", "##ItemPrice", &g.g_ESP_ItemPrice, 1000, 100000);

        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Combo(u8"方框样式", &g.g_ESP_BoxStyle, BoxTypeList, IM_ARRAYSIZE(BoxTypeList));

        ImGui::EndChild();
        ImGui::BeginChild("##C101", ImVec2(ImGui::GetContentRegionAvail()), true);

        ImGui::Text(u8"透视颜色");
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::TreeNode(u8"玩家 / SCAV"))
        {
            ImGui::ColorEdit4(u8"PMC", &Col_ESP_PMC.Value.x);
            ImGui::ColorEdit4(u8"SCAV", &Col_ESP_Scav.Value.x);
            ImGui::ColorEdit4(u8"玩家SCAV", &Col_ESP_pScav.Value.x);
            ImGui::ColorEdit4(u8"特殊SCAV", &Col_ESP_SpecialScav.Value.x);
            ImGui::ColorEdit4(u8"Boss", &Col_ESP_Boss.Value.x);
            ImGui::ColorEdit4(u8"填充方框", &Col_ESP_Filled.Value.x);

            ImGui::TreePop();
        }
        if (ImGui::TreeNode(u8"游戏"))
        {
            ImGui::Text(u8"[+] 物品");
            ImGui::ColorEdit4(u8"尸体", &Col_ESP_Corpse.Value.x);
            ImGui::ColorEdit4(u8"普通", &Col_ESP_Item_Normal.Value.x);
            ImGui::ColorEdit4(u8"较稀有", &Col_ESP_Item_Mid.Value.x);
            ImGui::ColorEdit4(u8"稀有", &Col_ESP_Item_Rare.Value.x);

            ImGui::NewLine();
            ImGui::Spacing();

            ImGui::Text(u8"[+] 撤离点");
            ImGui::ColorEdit4(u8"开放", &Col_ESP_ExfilOpen.Value.x);
            ImGui::ColorEdit4(u8"关闭", &Col_ESP_ExfilClose.Value.x);

            ImGui::TreePop();
        }

        ImGui::EndChild();
        break;

    case 1: // 功能右侧
        ImGui::BeginChild("##C200", ImVec2(ImGui::GetContentRegionAvail()), true);

        ImGui::Text(u8"功能说明");
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::TextWrapped(u8"左侧可开关无后坐、无限体力、无摔伤等。");

        ImGui::EndChild();
        break;

    case 2: // 设置右侧
        ImGui::BeginChild("##C300", ImVec2(ImGui::GetContentRegionAvail()), true);

        ImGui::Text(u8"退出");
        ImGui::Separator();
        ImGui::Spacing();
        if (ImGui::Button(u8"退出程序", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
            g.process_active = false;

        ImGui::EndChild();
        break;

    default:
        break;
    }

    ImGui::PopStyleColor();

    ImGui::EndChild();
    ImGui::EndChild();
    //---------------------------------------------------//

    ImGui::End();
}