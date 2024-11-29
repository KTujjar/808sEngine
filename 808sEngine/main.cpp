// Dear ImGui: standalone example application for SDL2 + SDL_Renderer
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

// Important to understand: SDL_Renderer is an _optional_ component of SDL2.
// For a multi-platform app consider using e.g. SDL+DirectX on Windows and SDL+OpenGL on Linux/OSX.
#define _CRT_SECURE_NO_WARNINGS 
#include "texture_loader.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL.h>

// Main code
int main(int, char**)
{
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with SDL_Renderer graphics context
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    if (window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return -1;
    }
    //SDL_RendererInfo info;
    //SDL_GetRendererInfo(renderer, &info);
    //SDL_Log("Current SDL_Renderer: %s", info.name);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigWindowsMoveFromTitleBarOnly = false;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiWindowFlags_NoResize;            // Disable Window Resize
    io.ConfigFlags |= ImGuiWindowFlags_NoCollapse;

    

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;;
    

    //Style
    ImGuiStyle& style = ImGui::GetStyle();

    //Logo
    SDL_Texture* my_texture;
    int my_image_width, my_image_height;
    bool ret = LoadTextureFromFile("assets\\logo.jpeg", renderer, &my_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);

    //Load Fonts

    //Default
    io.Fonts->AddFontDefault();
    ImFont* mainfont = io.Fonts->AddFontFromFileTTF("assets\\fonts\\roboto-regular.ttf", 30.0f);
    IM_ASSERT(mainfont != NULL);

    //Header Font
    ImFont* headerFont = io.Fonts->AddFontFromFileTTF("assets\\fonts\\roboto-regular.ttf", 40.0f);
    IM_ASSERT(headerFont != NULL);

    //ListBox Font
    ImFont* listFont = io.Fonts->AddFontFromFileTTF("assets\\fonts\\roboto-regular.ttf", 80.0f);
    IM_ASSERT(listFont != NULL);
    

    //Bool for create/new project windows
    bool newProject = false;    
    bool openProject = true;
    //General Color
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(43, 58, 68, 255));

    //HoveredColor
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(55, 58, 75, 255));

    //ActiveColor
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(55, 58, 75, 255));

    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
      


        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        static float f = 0.0f;
        static int counter = 0;

        //Setting the window size and position
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);


        //Window Cant be Collapsed or Moved through drag
        
        //Color of the buttons on the window

        //General Color
        ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(43,58,68,255));

        //HoveredColor
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(55, 58, 75, 255));

        //ActiveColor
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, openProject ? IM_COL32(55, 58, 75, 255) : IM_COL32(43,58,68,255));

        //Font
        ImGui::PushFont(mainfont);

        //Handle WindowSize
        int width;
        int height;
        SDL_GetWindowSize(window, &width, &height);
        ImVec2 windowSize = (ImVec2((float)width, (float)height));
        ImGui::SetNextWindowSize(windowSize);
        
        ImGui::Begin("New/Open", NULL, (ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize));

        //Logo + Top Window Box
        ImGui::BeginGroup();
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        drawList->ChannelsSplit(2);
        drawList->ChannelsSetCurrent(1);
        ImGui::Image((ImTextureID)(intptr_t)my_texture, ImVec2((float)70, (float)70));
        drawList->ChannelsSetCurrent(0);
        drawList->AddRectFilled(ImVec2(0,0), ImVec2(ImGui::GetWindowSize().x, 90), IM_COL32(75, 0, 130, 255));
        drawList->ChannelsMerge();
        ImGui::EndGroup();


        ImGui::SameLine();
        ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x * 0.30f, 20));

        if (ImGui::Button("Open Project", ImVec2(200, 50)))
        {
            newProject = false;
            openProject = true;
        }

        ImGui::SameLine();
        ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x * 0.55f, 20));

        if (ImGui::Button("New Project", ImVec2(200, 50)))
        {
            newProject = true;
            openProject = false;
        }

        if (newProject)
        {
            ImGui::Dummy(ImVec2(0, 40));
            ImGui::Text("Templates");
        }
        else

        if (openProject)
        {
            ImGui::Dummy(ImVec2(0, 40));

            //Group for the list of projects
            const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
            static int item_current = 1;
            /*ImFontConfig fontCfg = {};
            fontCfg.RasterizerDensity = 10;*/
            ImGui::PushFont(headerFont);
            ImGui::SetCursorPosX(ImGui::GetWindowSize().x * 0.4f);
            ImGui::Text("Projects");
            ImGui::PopFont();
            ImGui::PushFont(listFont);
            ImGui::PushItemWidth(ImGui::GetWindowSize().x * 0.85f);
            ImGui::ListBox("##label", &item_current, items, IM_ARRAYSIZE(items), 5);
            ImGui::PopItemWidth();
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetWindowSize().x * 0.89f);
            ImGui::Button("Open", ImVec2(100,50));
           
        }

        
        ImGui::End();

        ImGui::PopStyleColor(3);
        ImGui::PopFont();

        // Rendering
        ImGui::Render();
        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}