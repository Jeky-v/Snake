#pragma once
#include <vector>
#include "UIElement.h"
#include "ModuleMgr.h"
class UIElement;
class ButtonsManager
{
public:
	ButtonsManager(ModuleMgr* mgr);
	~ButtonsManager();
	ModuleMgr* m_mgr;
	std::vector<UIElement*>::iterator findButton(int x, int y); //x and y are coordinats of mouse.
	bool doRun();
	void addButton(UIElement* button);
	void goUp();  //for keyboard.
	void goDown();
	void setActive(UIElement* button);
private:
	std::vector<UIElement*> elements;
	std::vector<UIElement*>::iterator currentButton,switchButton;
};

