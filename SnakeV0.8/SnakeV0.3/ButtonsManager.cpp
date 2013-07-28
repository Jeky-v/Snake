#include "ButtonsManager.h"
#include "GlobalVariables.h"
#include <algorithm>
ButtonsManager::ButtonsManager(ModuleMgr* mgr)
{
	m_mgr=mgr;
}


void ButtonsManager::addButton(UIElement* button)
{
	elements.push_back(button);
	currentButton=elements.begin();  //something very weird with these iterators. 
	switchButton=currentButton;     //If you put it in the constuctor, there will be runtime erorr. 
	(*currentButton)->isActive=true;
}

std::vector<UIElement*>::iterator ButtonsManager::findButton(int x, int y)
{
	for (std::vector<UIElement*>::iterator it=elements.begin();it!=elements.end();it++)
		if ((*it)->checkCollision(x,y)) switchButton=it;
	return switchButton;
}
void ButtonsManager::setActive(UIElement* button)
{
	
	switchButton=currentButton=std::find(elements.begin(),elements.end(),button);
	(*currentButton)->isActive=true;
}

bool ButtonsManager::doRun()
{
	if (switchButton!=currentButton)
	{
		(*currentButton)->isActive=false;
		currentButton=switchButton;
		(*currentButton)->isActive=true;
	}

	for (std::vector<UIElement*>::iterator it=elements.begin();it!=elements.end();it++)
		(*it)->drawButton();
	SDL_Flip(screen);

	return (*currentButton)->processEvents();
}
void ButtonsManager::goUp()
{
	if (switchButton==elements.begin())
	{
		switchButton=elements.end();
		switchButton--;
	}
	else switchButton--;
}
void ButtonsManager::goDown()
{
	switchButton++;
	if (switchButton==elements.end()) switchButton=elements.begin();
}

ButtonsManager::~ButtonsManager()
{
	std::for_each(elements.begin(),elements.end(),[](UIElement* button){
	 delete button;
	});
	elements.clear();
}