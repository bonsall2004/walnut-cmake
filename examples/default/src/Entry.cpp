/*
 * netmon-gui
 * Author: bonsall2004
 * Description: GUI network monitoring solution
 */


#include "Walnut/Application.h"
#include "Walnut/Image.h"
#include "Walnut/EntryPoint.h"
#include "Walnut/UI/UI.h"

class ExampleLayer : public Walnut::Layer
{
 public:
  void OnUIRender() override
  {
    ImGui::Begin("Hello");
    ImGui::Button("Button");
    ImGui::End();

    ImGui::ShowDemoWindow();

    UI_DrawAboutModal();
  }

  void UI_DrawAboutModal()
  {
    if(!m_AboutModalOpen)
    {
      return;
    }

    ImGui::OpenPopup("About");
    m_AboutModalOpen = ImGui::BeginPopupModal("About", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if(m_AboutModalOpen)
    {
      auto image = Walnut::Application::Get().GetApplicationIcon();
      ImGui::Image(image->GetDescriptorSet(), {
        48,
        48 });

      ImGui::SameLine();
      Walnut::UI::ShiftCursorX(20.0f);

      ImGui::BeginGroup();
      ImGui::Text("Walnut application framework");
      ImGui::Text("by Studio Cherno.");
      ImGui::EndGroup();

      if(Walnut::UI::ButtonCentered("Close"))
      {
        m_AboutModalOpen = false;
        ImGui::CloseCurrentPopup();
      }

      ImGui::EndPopup();
    }
  }

  void ShowAboutModal()
  {
    m_AboutModalOpen = true;
  }

 private:
  bool m_AboutModalOpen = false;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
  Walnut::ApplicationSpecification spec;
  spec.Name = "Walnut Example";
  spec.CustomTitlebar = true;

  auto* app = new Walnut::Application(spec);
  std::shared_ptr<ExampleLayer> main_layer = std::make_shared<ExampleLayer>();
  app->PushLayer(main_layer);
  app->SetMenubarCallback([app, main_layer]()
  {
    if(ImGui::BeginMenu("File"))
    {
      if(ImGui::MenuItem("Exit"))
      {
        app->Close();
      }
      ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Help"))
    {
      if(ImGui::MenuItem("About"))
      {
        main_layer->ShowAboutModal();
      }
      ImGui::EndMenu();
    }
  });
  return app;
}