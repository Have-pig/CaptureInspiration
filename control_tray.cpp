#include "control_tray.h"
#include <SDL3/SDL.h>
#include "struct_define.h"


// 自定义标记，用来区分菜单项
struct Tray_MenuItemTag {
    enum TrayMenuItemTags 
    {
        TRAY_ITEM_SHOW,
        TRAY_ITEM_QUIT
    } state;
    SDL_Window* window;
};


// static 只本文件可见
static void SDLCALL TrayCallback(void* userdata, SDL_TrayEntry* entry)
{
    (void)entry;
    Tray_MenuItemTag* ctx = static_cast<Tray_MenuItemTag*>(userdata);

    // 注意：tag指针是堆分配，用完立刻释放
    switch(ctx->state)
    {   
        case Tray_MenuItemTag::TRAY_ITEM_SHOW:
        {
            SDL_ShowWindow(ctx->window);
            SDL_RestoreWindow(ctx->window);
            SDL_RaiseWindow(ctx->window);
            break;
        }
        case Tray_MenuItemTag::TRAY_ITEM_QUIT:
        {
            SDL_Event event{};
            event.type = SDL_EVENT_QUIT;
            SDL_PushEvent(&event);
            break;
        }
    }

    // 释放堆内存
    delete ctx;
}

void CreateSystemTray(AppState& state, SDL_Window* win, SDL_Surface* icon_surface)
{
    if(state.main_tray) 
        return;

    // 创建托盘
    state.main_tray = SDL_CreateTray(icon_surface, "CIP");
    // 创建托盘菜单
    SDL_TrayMenu* menu = SDL_CreateTrayMenu(state.main_tray);

    // 托盘菜单配置
    Tray_MenuItemTag* tag_show = new Tray_MenuItemTag{
        Tray_MenuItemTag::TRAY_ITEM_SHOW,
        win
    };
    Tray_MenuItemTag* tag_quit = new Tray_MenuItemTag{
        Tray_MenuItemTag::TRAY_ITEM_QUIT,
        win
    };
    SDL_TrayEntry* entry_show = SDL_InsertTrayEntryAt(menu, -1, "显示窗口", SDL_TRAYENTRY_BUTTON);
    SDL_InsertTrayEntryAt(menu, -1, nullptr, SDL_TRAYENTRY_BUTTON);// 菜单分割线
    SDL_TrayEntry* entry_quit = SDL_InsertTrayEntryAt(menu, -1, "退出", SDL_TRAYENTRY_BUTTON);
    
    SDL_SetTrayEntryCallback(entry_show, TrayCallback, tag_show);
    SDL_SetTrayEntryCallback(entry_quit, TrayCallback, tag_quit);
}

void DestroySystemTray(AppState& state)
{
    if(state.main_tray)
    {
        SDL_DestroyTray(state.main_tray);
        state.main_tray = nullptr;
    }
}