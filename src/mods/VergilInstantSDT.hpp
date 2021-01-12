#pragma once
#include "Mod.hpp"
#include "sdk/ReClass.hpp"
class VergilInstantSDT : public Mod {
public:
  VergilInstantSDT() = default;
  // mod name string for config
  std::string_view get_name() const override { return "VergilInstantSDT"; }
  // called by m_mods->init() you'd want to override this
  std::optional<std::string> on_initialize() override;
  uintptr_t static jmp_ret1;
  uintptr_t static jmp_ja1;
  uintptr_t static jmp_ret2;

  // Override this things if you want to store values in the config file
  // void on_config_load(const utility::Config& cfg) override;
  // void on_config_save(utility::Config& cfg) override;

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
  std::unique_ptr<FunctionHook> m_function_hook1;
  std::unique_ptr<FunctionHook> m_function_hook2;
};