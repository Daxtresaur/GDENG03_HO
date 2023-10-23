#include "UIManager.h"

UIManager* UIManager::getInstance()
{
    return nullptr;
}

void UIManager::initialize(HWND windowHandle)
{
}

void UIManager::destroy()
{
}

void UIManager::drawAllUI()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < this->uiList.size(); i++)
    {
        this->uiList[i]->drawUI();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::~UIManager()
{
}
