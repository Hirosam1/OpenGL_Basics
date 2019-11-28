#pragma once
class Window;
class InputManager;
class Time;

class BasicsBlock{
    public:
        BasicsBlock(Window* window, InputManager* input, Time* time);
        Window* m_window;
        InputManager* m_input;
        Time* m_time;
};