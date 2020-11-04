#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include <iostream>
#include <memory>
#include <vector>
#include "Atom.h"

class Context;
typedef std::shared_ptr<Context> ctx_ptr;
typedef std::shared_ptr<Atom> Atom_ptr;

class Context {
private:
    Context() = default;

    static ctx_ptr single_instance;
public:
    Context(const Context& ctx) = delete;

    static ctx_ptr GetInstance();

    void operator=(const Context &) = delete;

    SDL_Window *window = nullptr;
    int SCREEN_WIDTH = 600;
    int SCREEN_HEIGHT = 600;
    Atom* a = nullptr;
    Atom* b = nullptr;
    std::vector<Atom_ptr> atoms;
    void render();
    void update(float dt);

};



ctx_ptr Context::single_instance = nullptr;

ctx_ptr Context::GetInstance() {
    if(Context::single_instance == nullptr) {
        Context::single_instance = ctx_ptr(new Context());

    }
    return Context::single_instance;
}

void Context::render() {
    //Start gl rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->a->draw();
    this->b->draw();
    for(auto a : atoms)
        a->draw();
    SDL_GL_SwapWindow(this->window);
}

void Context::update(float dt) {
    //this->a->update(dt);
    Atom_ptr a, b;
    float time = -1.0;
    for(int i=0; i < atoms.size(); i++) {
        for(int j=i+1; j < atoms.size(); j++) {
            a = atoms[i];
            b = atoms[j];
            time = collision_time(*a, *b);
            if(time >= 0.0 && time <= dt) {
                resolve_collision(*a, *b);
            }
        }
    }
    for(auto a: atoms) {
        a->update(dt);
    }
}

ctx_ptr ctx;

void loop() {
    ctx->render();
    ctx->update(0.166);
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

#if __EMSCRIPTEN__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif
    //Create context
    ctx = Context::GetInstance();

    ctx->window = SDL_CreateWindow("wasm-physics", 0, 0, ctx->SCREEN_WIDTH, ctx->SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(ctx->window);

    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte *version;
    version = glGetString(GL_VERSION);
    std::cout << "version: " << version << std::endl;
    //Setup gl BG color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //Create Atom
    vec2 p(0.1, 0.1);
    vec2 v(0.01, 0.0);
    ctx->a = new Atom(p, v, 1.0, 1.0);

    ctx->b = new Atom(p, v, 0.2, 1.0);
    std::cout << ctx->a->vel.x << std::endl;
    //Initialize atoms
    ctx->atoms.push_back(std::make_shared<Atom>(vec2(-1.0, 0.0), vec2(0.1, 0.0), 0.1, 10.0));
    p = vec2(0.8, 0.0);
    v = vec2(-0.1, 0.0);
    ctx->atoms.push_back(std::make_shared<Atom>(p, v, 0.1, 1.0));


    //Emscripten has it's own way of running a loop
#if __EMSCRIPTEN__
    emscripten_set_main_loop(loop, -1, 1);
#else
    SDL_Event windowEvent;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) break;
        }
        //Render loop
        loop();
    }
#endif

    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}