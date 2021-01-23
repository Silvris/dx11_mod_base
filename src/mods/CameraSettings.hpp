#pragma once
#include "Mod.hpp"
#include "sdk/ReClass.hpp"
class CameraSettings : public Mod {
public:
  CameraSettings() = default;
  // mod name string for config
  std::string_view get_name() const override { return "CameraSettings"; }
  // called by m_mods->init() you'd want to override this
  std::optional<std::string> on_initialize() override;
  uintptr_t static jmp_retFoV;
  uintptr_t static jmp_retHorizontalSensClockwise;
  uintptr_t static jmp_retHorizontalSensAntiClockwise;

  uintptr_t static jmp_retKeyboardHorizontalEnable;
  uintptr_t static jmp_jeKeyboardHorizontalEnable;

  uintptr_t static jmp_retSiyansCamFix1;
  uintptr_t static jmp_jneSiyansCamFix1;

  uintptr_t static jmp_retCloseAutoCorrect;
  uintptr_t static jmp_jneCloseAutoCorrect;

  uintptr_t static jmp_retDistantAutoCorrect;

  uintptr_t static cheaton;

  // Override this things if you want to store values in the config file
  void on_config_load(const utility::Config& cfg) override;
  void on_config_save(utility::Config& cfg) override;

  // on_frame() is called every frame regardless whether the gui shows up.
  // void on_frame() override;
  // on_draw_ui() is called only when the gui shows up
  // you are in the imgui window here.
  void on_draw_ui() override;
  // on_draw_debug_ui() is called when debug window shows up
  // void on_draw_debug_ui() override;

private:
  // function hook instance for our detour, convinient wrapper
  // around minhook
  std::unique_ptr<FunctionHook> m_function_hookFoV;
  std::unique_ptr<FunctionHook> m_function_hookHorizontalSensClockwise;
  std::unique_ptr<FunctionHook> m_function_hookHorizontalSensAntiClockwise;
  std::unique_ptr<FunctionHook> m_function_hookKeyboardHorizontalEnable;
  std::unique_ptr<FunctionHook> m_function_hookSiyansCamFix1;
  std::unique_ptr<FunctionHook> m_function_hookCloseAutoCorrect;
  std::unique_ptr<FunctionHook> m_function_hookDistantAutoCorrect;
};