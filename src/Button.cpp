#include <Button.hpp>


sf::Font Button::font;

auto Button::pressSound = std::shared_ptr<aud::Sound>(new aud::Sound("res/click.wav"));
auto Button::hoverSound = std::shared_ptr<aud::Sound>(new aud::Sound("res/hover.wav"));

int Button::hoverScaleAmount = 30;
int Button::hoverScaleSpeed = 1;
