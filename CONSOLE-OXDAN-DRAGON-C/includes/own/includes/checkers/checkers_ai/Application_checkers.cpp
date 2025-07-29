//
//  Application.cpp
//  SDL_Checkers
//
//  Created by Jacky Chiu on 2016-02-18.
//  Copyright © 2016 Jacky Chiu.
//

#include "Application_checkers.h"
#include "ApplicationState_checkers.h"
#include "ApplicationStateManager_checkers.h"
#include "Texture_checkers.h"

int currentSprite = 0;
SDL_Window *gWindow;
SDL_Renderer *gRenderer;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
int BUTTON_WIDTH = 0;
int BUTTON_HEIGHT = 0;
int GAMEMODE = 0;

vector<SDL_Rect> spriteClips;
Texture spriteSheetTexture;

Application_checkers::Application_checkers(){
    gWindow=NULL;
    gRenderer=NULL;
    // Checks if init was able to excute //
    if(!init()){
        //cout<<"Could not load application!"<<endl;
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        //printf("(!Enter pas_gen option!)\n");
        cout << "(!Could not load application!)";
        printf("\033[0;37m");
    }
    applicationStateManager = new ApplicationStateManager;
}

Application_checkers::~Application_checkers(){
    delete applicationStateManager;
    applicationStateManager = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow=NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer=NULL;
}

bool Application_checkers::init(){
    bool initSuccessful = true;

    if(SDL_Init(SDL_INIT_VIDEO)>0)
    {
        //cout<<"Failed init. SDL_ERROR: %s\n"<<SDL_GetError();
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        //printf("(!Enter pas_gen option!)\n");
        cout << "(!Failed init. SDL_ERROR: " << SDL_GetError() << "!)";
        printf("\033[0;37m");
        initSuccessful = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            cout<<"Warning: Linear texture filtering not enabled!"<<endl;
            printf("\033[0;31m");
            printf("\n");
            printf("(!ERROR!)");
            printf("\033[0;37m");
            printf(" = ");
            printf("\033[0;32m");
            //printf("(!Enter pas_gen option!)\n");
            cout << "(!Warning: Linear texture filtering not enabled!)";
            printf("\033[0;37m");
        }

        gWindow=SDL_CreateWindow("Checkers Ai",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

        if(gWindow==NULL)
        {
            //cout<<"Couldnt make window. SDL_Error: %s\n"<<SDL_GetError()<<endl;
            printf("\033[0;31m");
            printf("\n");
            printf("(!ERROR!)");
            printf("\033[0;37m");
            printf(" = ");
            printf("\033[0;32m");
            //printf("(!Enter pas_gen option!)\n");
            cout << "(!Couldnt make window. SDL_Error: " << SDL_GetError() << "!)";
            printf("\033[0;37m");
            initSuccessful = false;
        }
        else
        {
            gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer==NULL)
            {
                //cout<<"Renderer failed. SDL_Error: %s\n"<<SDL_GetError()<<endl;
                printf("\033[0;31m");
                printf("\n");
                printf("(!ERROR!)");
                printf("\033[0;37m");
                printf(" = ");
                printf("\033[0;32m");
                //printf("(!Enter pas_gen option!)\n");
                cout << "(!Renderer failed. SDL_Error: " << SDL_GetError() << "!)";
                printf("\033[0;37m");
                initSuccessful = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);

                // Init for img loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    //cout<<"Image failed. SDl_image Error: %s\n"<<IMG_GetError()<<endl;
                    printf("\033[0;31m");
                    printf("\n");
                    printf("(!ERROR!)");
                    printf("\033[0;37m");
                    printf(" = ");
                    printf("\033[0;32m");
                    //printf("(!Enter pas_gen option!)\n");
                    cout << "(!Image failed. SDl_image Error: " << IMG_GetError() << "!)";
                    printf("\033[0;37m");
                    initSuccessful = false;
                }
            }
        }
    }
    return initSuccessful;
}

int Application_checkers::startApplication(){

    while (!applicationStateManager->stateExit()) {
        applicationStateManager->stateEvent();
        applicationStateManager->stateRender();
        if (applicationStateManager->stateUpdate() != applicationStateManager->getCurrentStateEnum()) {
            applicationStateManager->setCurrentStateEnum(applicationStateManager->stateUpdate());
            applicationStateManager->changeStates();
        }
        SDL_RenderPresent(gRenderer);
        if (applicationStateManager->getCurrentStateEnum() == MENU_STATE) {
            SDL_Delay(30);
        }
        else {
            SDL_Delay(100);
        }
    }

    closeApplication();

    return (EXIT_SUCCESS);

}

void Application_checkers::closeApplication(){
    IMG_Quit();
    SDL_Quit();
}
