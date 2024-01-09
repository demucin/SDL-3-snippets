#include <SDL3/SDL.h>

typedef struct anythin {
    int* some_int;
}anything;

static const char* anything_name = "anything";

static void SDLCALL clean_anything_callback(void* userdata, void* value)
{
    (void)(userdata);
    anything* any = (anything*)value;
    SDL_Log("Destroying: %d\n", *any->some_int);

    SDL_free(any->some_int);
    SDL_free(any);
}

int main()
{
    SDL_Init(0);
    SDL_PropertiesID props = SDL_CreateProperties();

    anything* width1 = SDL_calloc(1, sizeof(anything));
    width1->some_int = SDL_malloc(sizeof(int));
    *width1->some_int = 91001;
    SDL_Log("Created: %d\n", *width1->some_int);

    anything* width2 = SDL_calloc(1, sizeof(anything));
    width2->some_int = SDL_malloc(sizeof(int));
    *width2->some_int = 91002;
    SDL_Log("Created: %d\n", *width2->some_int);

    SDL_Log("Set %s: %d\n", anything_name, *width1->some_int);
    SDL_SetPropertyWithCleanup(props, anything_name, width1, clean_anything_callback, NULL);
    
    SDL_Log("Reset %s: %d\n", anything_name, *width2->some_int);
    SDL_SetPropertyWithCleanup(props, anything_name, width2, clean_anything_callback, NULL);

    // SDL_DestroyProperties(props);

    SDL_Log("Quit");
    SDL_Quit();
}
