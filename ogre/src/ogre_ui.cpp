#include "ogre_int.hpp"

Ogre::OverlayContainer* ogre_ui;

namespace
{
	struct Operation
	{
		unsigned texture;
		unsigned x, y;
		unsigned width, height;
		Ogre::String text;
	};
	typedef std::deque<Operation> Operations;

	Operations operations;

	void erase(Ogre::OverlayElement* element, bool erase_element)
	{
		Ogre::OverlayContainer* container = dynamic_cast<Ogre::OverlayContainer*>(element);
		if (container)
		{
			std::deque<Ogre::OverlayElement*> elems;
			Ogre::OverlayContainer::ChildIterator children = container->getChildIterator();
			while (children.hasMoreElements())
				elems.push_back(children.getNext());
			for (unsigned i = 0; i < elems.size(); i++)
				erase(elems[i], true);
		}
		if (element && erase_element)
		{
			Ogre::OverlayContainer* parent = element->getParent();
			if (parent)
				parent->removeChild(element->getName());
			Ogre::OverlayManager::getSingleton().destroyOverlayElement(element);
		}
	}
}

namespace
{
	struct Font
	{
		float height;
		unsigned characters[USE_UI_CHARACTERS];
	};

	typedef std::map<unsigned, Font> Fonts;
	Fonts fonts;
};

namespace
{
	class TaskUI : public Task
	{
	public:
		TaskUI(Operations& operations)
		{
			this->operations.swap(operations);
		}

		virtual TaskResult task(void)
		{
			//ogre_log(__FUNCTION__, "");

			Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
			unsigned index = 0;
			for (Operations::iterator itor(operations.begin()); itor != operations.end(); ++itor)
			{
				Ogre::OverlayElement* el;
				if (itor->texture)
				{
					el = om.createOverlayElement("Panel", UIElement(index++));
					el->setMetricsMode(Ogre::GMM_PIXELS);
					el->setPosition((float)itor->x, (float)itor->y);
					el->setDimensions((float)itor->width, (float)itor->height);
					el->setMaterialName(MaterialTextureName(itor->texture));
				}
				else
				{
					Fonts::const_iterator it(fonts.find(itor->width));
					if (it == fonts.end())
						continue;
					el = om.createOverlayElement("TextArea", UIElement(index++));
					el->setMetricsMode(Ogre::GMM_PIXELS);
					el->setPosition((float)itor->x, (float)itor->y);
					el->setCaption(itor->text);
					el->setDimensions(0.1f, 0.1f);
					el->setParameter("font_name", FontName(itor->width));
					char buf[32];
					sprintf(buf, "%f", it->second.height);
					el->setParameter("char_height", buf);
					el->setColour(Ogre::ColourValue(((itor->height >> 16) & 0xFF) / 255.0f, ((itor->height >> 8) & 0xFF) / 255.0f, ((itor->height >> 0) & 0xFF) / 255.0f));
				}
				el->initialise();
				el->show();
				ogre_ui->addChild(el);
			}

			return TR_TASK;
		}

	private:
		Operations operations;
	};

	class TaskUIFont : public Task
	{
	public:
		TaskUIFont(unsigned font, const char* name, float height, Semaphore& sem)
			: font(font), name(name), height(height), sem(sem)
		{
		}
		virtual TaskResult task(void)
		{
			ogre_log(__FUNCTION__, "");

			Font& f = fonts[font];

			f.height = height;

			Ogre::FontPtr fnt = Ogre::FontManager::getSingleton().create(FontName(font), ogre_resource_group);
			fnt->setType(Ogre::FT_TRUETYPE);
			fnt->setSource(name + ".ttf");
			fnt->setTrueTypeSize(height);
			fnt->setTrueTypeResolution(96);
			fnt->addCodePointRange(Ogre::Font::CodePointRange(32, USE_UI_CHARACTERS - 1));
			fnt->load();

			for (unsigned ch = 0; ch < USE_UI_CHARACTERS; ch++)
				f.characters[ch] = (unsigned) (fnt->getGlyphAspectRatio(ch) * height);

			sem.release();
			return TR_TASK;
		}

	private:
		unsigned font;
		Ogre::String name;
		float height;
		Semaphore& sem;
	};

	struct TaskUIFontsClear : public Task
	{
		virtual TaskResult task(void)
		{
			ogre_log(__FUNCTION__, "");

			for (Fonts::iterator itor(fonts.begin()); itor != fonts.end(); itor++)
			{
				FontName font_name(itor->first);
				Ogre::FontManager::getSingleton().unload(font_name);
				Ogre::FontManager::getSingleton().remove(font_name);
			}

			fonts.clear();

			return TR_TASK;
		}
	};

	struct TaskUIClear : public Task
	{
		virtual TaskResult task(void)
		{
			ogre_log(__FUNCTION__, "");

			erase(ogre_ui, true);
			ogre_ui = 0;

			return TR_TASK;
		}
	};
}

void OGREEE_CALL ogre_ui_draw(unsigned texture, unsigned x1, unsigned y1, unsigned x2, unsigned y2)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "%u %u %u %u %u", texture, x1, y1, x2, y2);

	Operation op = { texture, x1, y1, x2 - x1, y2 - y1 };
	operations.push_back(op);
}


OGREEE_API void OGREEE_CALL ogre_ui_font(unsigned font, const char* name, float height)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "");

	Semaphore sem(0, 1);
	ogre_tasks->enqueue(new TaskUIFont(font, name, height, sem));
	sem.acquire();
}

OGREEE_API unsigned OGREEE_CALL ogre_ui_width(unsigned font, const char* str)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "%s %u", str, font);

	Fonts::const_iterator itor = fonts.find(font);
	if (itor == fonts.end())
		return 0;

	Ogre::DisplayString s(str);
	unsigned total = 0;
	for (Ogre::DisplayString::iterator i(s.begin()); i != s.end(); ++i)
	{
		Ogre::Font::CodePoint ch = OGRE_DEREF_DISPLAYSTRING_ITERATOR(i);
		if (ch >= USE_UI_CHARACTERS)
			return 0;
		unsigned width = itor->second.characters[ch];
		if (!width)
			return 0;
		total += width;
		// FIXME: kerning
	}

	return total;
}

OGREEE_API void OGREEE_CALL ogre_ui_text(unsigned font, unsigned x, unsigned y, const char* str, unsigned colour)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "%s %u %u %u %08X", str, x, y, font, colour);

	Operation op = { 0, x, y, font, colour, str };
	operations.push_back(op);
}

void ogre_ui_commit(void)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "");

	if (!operations.empty())
		ogre_tasks->enqueue(new TaskUI(operations));
}

OGREEE_API void OGREEE_CALL ogre_ui_fonts_clear(void)
{
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_log_(__FUNCTION__, "");

	ogre_tasks->enqueue(new TaskUIFontsClear);
}

OGREEE_API void OGREEE_CALL ogre_ui_clear(void)
{
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_log_(__FUNCTION__, "");

	ogre_tasks->enqueue(new TaskUIClear);
}

void ogre_ui_frame(void)
{
	assert(GetCurrentThreadId() == ogre_thread_id);
	//ogre_log(__FUNCTION__, "");

	erase(ogre_ui, false);
}
