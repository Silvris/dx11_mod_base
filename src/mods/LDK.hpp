#pragma once
#include "Mod.hpp"
#include "sdk/ReClass.hpp"
class LDK : public Mod {
public:
  LDK() = default;
  // mod name string for config
  std::string_view get_name() const override { return "LDK"; }
  // called by m_mods->init() you'd want to override this
  std::optional<std::string> on_initialize() override;
  uintptr_t static enemynumber_jmp_ret;
  uintptr_t static capbypass_jmp_ret1;
  uintptr_t static capbypass_jmp_ret2;
  uintptr_t static capbypass_jmp_jnl;
  uintptr_t static capbypass_jmp_jle;
  uintptr_t static cheaton;

  uint32_t static number;
  uint32_t static hardlimit;
  uint32_t static softlimit;
  uint32_t static limittype;

  // Override this things if you want to store values in the config file
  void on_config_load(const utility::Config& cfg) override;
  void on_config_save(utility::Config& cfg) override;

  // on_frame() is called every frame regardless whether the gui shows up.
  //void on_frame() override;
  // on_draw_ui() is called only when the gui shows up
  // you are in the imgui window here.
  void on_draw_ui() override;
  // on_draw_debug_ui() is called when debug window shows up
  void on_draw_debug_ui() override;

  // function hook instance for our detour, convinient wrapper 
  // around minhook
  std::unique_ptr<FunctionHook> m_enemynumber_hook;
  std::unique_ptr<FunctionHook> m_capbypass_hook1;
  std::unique_ptr<FunctionHook> m_capbypass_hook2;
};