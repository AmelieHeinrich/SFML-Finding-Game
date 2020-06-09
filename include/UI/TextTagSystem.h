#ifndef TEXTTAGSYSTEM_H
#define TEXTTAGSYSTEM_H

#include "State.h"

enum TAGTYPE { DEFAULT_TAG, SPECIAL_TAG };

class TextTagSystem
{
private:
    class TextTag
    {
    private:
        sf::Text text;
        float dirX;
        float dirY;
        float lifetime;
        float speed;

    public:
        TextTag(sf::Font& font, std::string text,
                float pos_x, float pos_y,
                float dir_x, float dir_y,
                sf::Color color,
                unsigned char_size,
                float lifetime,
                float speed)
        {
            this->text.setFont(font);
            this->text.setPosition(pos_x, pos_y);
            this->text.setFillColor(color);
            this->text.setCharacterSize(char_size);
            this->text.setString(text);

            this->dirX = dir_x;
            this->dirY = dir_y;
            this->lifetime = lifetime;
            this->speed = speed;
        }

        TextTag(TextTag* tag, float pos_x, float pos_y)
        {
            this->text = tag->text;
            this->text.setPosition(pos_x, pos_y);

            this->dirX = tag->dirX;
            this->dirY = tag->dirY;
            this->lifetime = tag->lifetime;
            this->speed = tag->speed;
        }

        ~TextTag()
        {

        }

        inline const bool canBeRemoved() const
        {
            return this->lifetime <= 0.f;
        }

        void update()
        {
            if (this->lifetime > 0.f)
            {
                this->lifetime -= 10.f;

                this->text.move(this->dirX, this->dirY);
            }
        }

        void render(sf::RenderTarget & target)
        {
            target.draw(this->text);
        }
    };

    sf::Font font;
    std::map<unsigned, TextTag*> tagTemplates;
    std::vector<TextTag*> tags;

    void initVariables();
    void initFonts(std::string font_file);
    void initTagTemplates();

public:
    TextTagSystem(std::string font_file);
    virtual ~TextTagSystem();

    void addTextFrag(const unsigned text_tag, float pos_x, float pos_y);
    void removeTextFrag();

    void update();
    void render(sf::RenderTarget & target);
};

#endif // TEXTTAGSYSTEM_H
