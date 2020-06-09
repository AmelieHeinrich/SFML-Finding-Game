#include "TextTagSystem.h"

void TextTagSystem::initVariables()
{

}

void TextTagSystem::initFonts(std::string font_file)
{
    if (!this->font.loadFromFile(font_file))
    {
        std::cout << "failed to load font: " << font_file << std::endl;
    }
}

void TextTagSystem::initTagTemplates()
{
    this->tagTemplates[DEFAULT_TAG] = new TextTag(this->font, "+1", 1000.f, 1000.f, 0.f, -1.f, sf::Color::Cyan, 30, 1000.f, 200.f);
}

TextTagSystem::TextTagSystem(std::string font_file)
{
    this->initVariables();
    this->initFonts(font_file);
    this->initTagTemplates();
}

TextTagSystem::~TextTagSystem()
{
    for (auto *tag : this->tags)
    {
        delete tag;
    }

    for (auto &tag : this->tagTemplates)
    {
        delete tag.second;
    }
}

void TextTagSystem::addTextFrag(const unsigned text_tag, float pos_x, float pos_y)
{
    this->tags.push_back(new TextTag(this->tagTemplates[text_tag], pos_x, pos_y));
}

void TextTagSystem::removeTextFrag()
{

}

void TextTagSystem::update()
{
    for (size_t i = 0; i < this->tags.size(); ++i)
	{
		this->tags[i]->update();

		if (this->tags[i]->canBeRemoved())
		{
			delete this->tags[i];
			this->tags.erase(this->tags.begin() + i);
		}
	}
}

void TextTagSystem::render(sf::RenderTarget & target)
{
    for (auto& tag : this->tags)
    {
        tag->render(target);
    }
}
