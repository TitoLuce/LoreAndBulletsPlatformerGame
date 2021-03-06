#ifndef __GUICHECKBOX_H__
#define __GUICHECKBOX_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiCheckBox : public GuiControl
{
public:

	GuiCheckBox(uint32 id, SDL_Rect bounds, const char *text);
	virtual ~GuiCheckBox();

	bool Update(float dt);
	bool Draw();

	bool checked = false;

private:

	SDL_Rect normalCb;
	SDL_Rect focusedCb;
	SDL_Rect pressedCb;
	SDL_Rect check;

	bool hoverPlay = true;
	bool clickPlay = true;
};

#endif // __GUICHECKBOX_H__
