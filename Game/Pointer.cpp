#include "Pointer.h"

Pointer::Pointer()
{
	window = NULL;
	view = NULL;
	focus = NULL;
}

Pointer::Pointer(RenderWindow* _window, View* _view, Entity* _focus)
{
	view = _view;
	window = _window;
	focus = _focus;
	cursor.setSize(SIZE);
	cursor.setPosition(view->getCenter());
	cursor.setFillColor(color);
	cursor.setOrigin(cursor.getSize() / 2.f);
	pos = Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
	ppos = pos;
	pview = view->getCenter();
	lvlSize = Vector2f(-1, -1);
}

void Pointer::init(RenderWindow* _window, View* _view, Entity* _focus)
{
	view = _view;
	window = _window;
	focus = _focus;
	cursor.setSize(SIZE);
	cursor.setPosition(view->getCenter());
	cursor.setFillColor(color);
	cursor.setOrigin(cursor.getSize() / 2.f);
	pos = Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
	ppos = pos;
	pview = view->getCenter();
	lvlSize = Vector2f(-1, -1);
}

void Pointer::update()
{
	view->setCenter(focus->getPos()); //setView & update window
	if (lvlSize.x != -1 && //check X level limit
		(view->getCenter().x + view->getSize().x / 2.f > lvlSize.x ||
			view->getCenter().x - view->getSize().x / 2.f < 0))
	{
		view->setCenter(pview.x, view->getCenter().y);
	}
	if (lvlSize.y != -1 && //check Y level limit
		(view->getCenter().y + view->getSize().y / 2.f > lvlSize.y ||
			view->getCenter().y - view->getSize().y / 2.f < 0))
	{
		view->setCenter(view->getCenter().x, pview.y);
	}
	window->setView(*view);
	cursor.setPosition(cursor.getPosition() + ((pos - ppos) + (view->getCenter() - pview))); //update cursos position
	checkEdges(); //check cursor limit
	ppos = pos;
	pos = Vector2f(Mouse::getPosition(*window)); //change/update/store values
	pview = view->getCenter();
	cursor.setFillColor(color);
}

void Pointer::checkEdges()
{
	if (Mouse::getPosition().x >= window->getSize().x - 1 ||
		Mouse::getPosition().x <= 1 ||
		Mouse::getPosition().y >= window->getSize().y - 1 ||
		Mouse::getPosition().y <= 1)
	{
		Mouse::setPosition((Vector2i)window->getSize() / 2);
		pos = Vector2f(Mouse::getPosition(*window));
	}

	//rect dx
	if (cursor.getPosition().x > view->getCenter().x + view->getSize().x / 2.f - cursor.getSize().x / 2.f)
	{
		cursor.setPosition(view->getCenter().x + view->getSize().x / 2.f - cursor.getSize().x / 2.f, cursor.getPosition().y);
	}
	//rect up
	if (cursor.getPosition().y < view->getCenter().y - view->getSize().y / 2.f + cursor.getSize().y / 2.f)
	{
		cursor.setPosition(cursor.getPosition().x, view->getCenter().y - view->getSize().y / 2.f + cursor.getSize().y / 2.f);
	}
	//rect sx
	if (cursor.getPosition().x < view->getCenter().x - view->getSize().x / 2.f + cursor.getSize().x / 2.f)
	{
		cursor.setPosition(view->getCenter().x - view->getSize().x / 2.f + cursor.getSize().x / 2.f, cursor.getPosition().y);
	}
	//rect down
	if (cursor.getPosition().y > view->getCenter().y + view->getSize().y / 2.f - cursor.getSize().y / 2.f)
	{
		cursor.setPosition(cursor.getPosition().x, view->getCenter().y + view->getSize().y / 2.f - cursor.getSize().y / 2.f);
	}
}