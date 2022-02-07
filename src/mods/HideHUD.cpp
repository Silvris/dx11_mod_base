
#include "HideHUD.hpp"
#include "PlayerTracker.hpp"

uintptr_t HideHUD::jmp_ret{NULL};
bool HideHUD::cheaton{NULL};
bool hideeverything;
bool hidehp;
bool hideorbs;
bool hidestyle;

// clang-format off
// only in clang/icl mode on x64, sorry

static naked void detour() {
	__asm {
        // cmp [PlayerTracker::playerid], 1 //change this to the char number obviously
        // jne code
        cmp byte ptr [HideHUD::cheaton], 1
        je cheatcode
        jmp code

    cheatcode:
        cmp byte ptr [hideeverything], 1
        je retcode
        cmp byte ptr [rbx+08h], 17    // Nero HP
        je hpcheck
        cmp byte ptr [rbx+08h], 10    // Dante HP
        je hpcheck
        cmp byte ptr [rbx+08h], 11    // V HP
        je hpcheck
        cmp byte ptr [rbx+08h], 6     // Vergil HP
        je hpcheck
        cmp byte ptr [rbx+08h], 5     // Orbs
        je orbcheck
        cmp byte ptr [rbx+08h], 18    // Style Meter
        je stylecheck
        jmp code

    hpcheck:
        cmp byte ptr [hidehp], 1
        je retcode
        jmp code

    orbcheck:
        cmp byte ptr [hideorbs], 1
        je retcode
        jmp code

    stylecheck:
        cmp byte ptr [hidestyle], 1
        je retcode
        jmp code

    code:
        mov [rbx+000000C4h], eax
    retcode:
        jmp qword ptr [HideHUD::jmp_ret]
	}
}

// clang-format on

void HideHUD::init_check_box_info() {
  m_check_box_name = m_prefix_check_box_name + std::string(get_name());
  m_hot_key_name   = m_prefix_hot_key_name + std::string(get_name());
}

std::optional<std::string> HideHUD::on_initialize() {
  init_check_box_info();

  ischecked               = &HideHUD::cheaton  ;
  onpage                  = camera;

  full_name_string        = "Hide HUD (+)";
  author_string           = "SSSiyan";
  description_string      = "Disables elements of the Heads Up Display.";

  auto base = g_framework->get_module().as<HMODULE>(); // note HMODULE
  auto addr = patterns.find_addr(base, "89 83 C4 00 00 00 F3");
  if (!addr) {
    return "Unable to find HideHUD pattern.";
  }

  if (!install_hook_absolute(addr.value(), m_function_hook, &detour, &jmp_ret, 6)) {
    //  return a error string in case something goes wrong
    spdlog::error("[{}] failed to initialize", get_name());
    return "Failed to initialize HideHUD";
  }
  return Mod::on_initialize();
}

void HideHUD::on_config_load(const utility::Config& cfg) {
  hidehp         = cfg.get<bool>("hide_hp_hud").value_or(false);
  hideorbs       = cfg.get<bool>("hide_orbs_hud").value_or(false);
  hidestyle      = cfg.get<bool>("hide_style_hud").value_or(false);
  hideeverything = cfg.get<bool>("hide_all_hud").value_or(true);
}
void HideHUD::on_config_save(utility::Config& cfg) {
  cfg.set<bool>("hide_hp_hud", hidehp);
  cfg.set<bool>("hide_orbs_hud", hideorbs);
  cfg.set<bool>("hide_style_hud", hidestyle);
  cfg.set<bool>("hide_all_hud", hideeverything);
}

void HideHUD::on_draw_ui() {
  ImGui::Checkbox("Hide HP", &hidehp);
  ImGui::Checkbox("Hide Orbs", &hideorbs);
  ImGui::Checkbox("Hide Style", &hidestyle);
  ImGui::Checkbox("Hide all optional HUD", &hideeverything);
}
