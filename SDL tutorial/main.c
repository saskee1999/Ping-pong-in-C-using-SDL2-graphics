#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>



typedef struct
{
    int x;
    int y;
    char* name;
} Man;

typedef struct
{
    int x;
    int y;
    float dx;
    float dy;
}Ball;

typedef struct
{
    //players
    Man man1;
    Man man2;
    Ball ball;
    SDL_Texture* star;

} GameState;

/*int rc(int range){
    return srand(time(NULL))%range;
}*/


int ProcessEvents(SDL_Window *window, GameState* game)
{
    int done=0;

    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {

        case SDL_WINDOWEVENT_CLOSE:
        {
            if(window)
            {
                SDL_DestroyWindow(window);
                window = NULL;
            }
        }
        break;
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                done = 1;
                break;
            }
        }
        break;
        case SDL_QUIT:
            done = 1;
            break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_LEFT] && game->man1.x > 0){
        game->man1.x -= 10;
    }
    if(state[SDL_SCANCODE_RIGHT] && game->man1.x < 490)
    {
        game->man1.x += 10;
    }
    if(state[SDL_SCANCODE_A] && game->man2.x > 0){
        game->man2.x -= 10;
    }
    if(state[SDL_SCANCODE_D] && game->man2.x < 490)
    {
        game->man2.x += 10;
    }

    if(game->ball.x <= 0 || game->ball.x >= 630){
        game->ball.dx = -game->ball.dx;
    }
    if(((game->ball.y >= game->man1.y) && (game->ball.x >= game->man1.x) && (game->ball.x <= game->man1.x + 150)) || (game->ball.y <= game->man2.y+30 && game->ball.x >= game->man2.x && game->ball.x <= game->man2.x + 150)){
        game->ball.dy = -game->ball.dy;
        //if(game->ball.dy > 0){
        //    game->ball.dy += 0.5;
        //}else{
        //game->ball.dy -= 0.5;
        //}
    }
    if(game->ball.y < 0 || game->ball.y > 480){
        game->ball.y = 50;
        game->ball.x = 50;
        game->ball.dy = 5;
        game->ball.dx = 5;
    }



    game->ball.x += game->ball.dx;
    game->ball.y += game->ball.dy;



    return done;

}


void doRender(SDL_Renderer *renderer, GameState* game)
{


    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //Selects Blue as colour

    //clears screen to blue
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //Selects white as colour

    SDL_Rect rect1 = {game->man1.x, game->man1.y, 150, 30}; //creates rectangle with array arguments x y wifth and height
    SDL_Rect rect2 = {game->man2.x, game->man2.y, 150, 30};
    SDL_Rect bouncy = {game->ball.x, game->ball.y, 10, 10};
    SDL_Rect divider = {0, 240, 640, 10};
    SDL_RenderFillRect(renderer, &rect1); //fills reactangle with selected colour
    SDL_RenderFillRect(renderer, &rect2); //fills reactangle with selected colour
    SDL_RenderFillRect(renderer, &divider);
    SDL_RenderFillRect(renderer, &bouncy);

    SDL_RenderPresent(renderer); //presents to screen

}


void LoadGame()
{
;
}


int main(int argc, char* argv[])
{

//for(int i = 0; i < 20 ; i++){
//    printf("%d\n", rc(480));
//}


    SDL_Window *window = NULL;     //Declare a window
    SDL_Renderer *renderer = NULL; //Declare a renderer
    SDL_Surface *starSurface = NULL;

    SDL_Init(SDL_INIT_VIDEO); //initialize SDL 2

    //Creates an application window with the following settings

    window = SDL_CreateWindow("Game Window",               //Window title
                              SDL_WINDOWPOS_UNDEFINED,     //initial x position
                              SDL_WINDOWPOS_UNDEFINED,     //initial y position
                              640,                         // width in pixels
                              480,                         // height in pixels
                              0                            //flags
                             );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Accelerated means do as fast as hardware allows

    //IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG); //initilises image

    //starSurface = IMG_Load("star.jpg");
    /*if(starSurface = NULL)
    {
        printf("Cannot find star.jpg!\n\n");
        SDL_Quit();
        return 1;
    }*/

    GameState gameState;

    gameState.star = SDL_CreateTextureFromSurface(renderer, starSurface);
    SDL_FreeSurface(starSurface);



    Ball ball;
    Man man1;
    Man man2;
    gameState.man1.x = 320-50;
    gameState.man1.y = 480-40;
    gameState.man2.x = 320-50;
    gameState.man2.y = 480-460;
    gameState.ball.x = 50;
    gameState.ball.y = 50;
    gameState.ball.dx = 5;
    gameState.ball.dy = 5;

    int done = 0;
    while(!done)
    {

        done = ProcessEvents(&window, &gameState);
        doRender(renderer, &gameState);
        /*SDL_Delay(10);*/
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
