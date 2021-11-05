#ifndef UI_COMMON__H
#define UI_COMMON__H

#include "button.h"

class Application
{
public:
	Application() {}

	virtual void onRotarySW(RotarySwitch::RSW_DIR dir) = 0;
	virtual void onButton(int state) = 0;

	void register_update();
	bool should_update() const;

};

//  -----------------------------------------------

struct Menu
{
	Menu(const char *title)
		: next(nullptr), prev(nullptr), child(nullptr), parent(nullptr), title(title)
	{}

	virtual const char *get_title() { return title; }

	void add_sibling(Menu *p)
	{
		next = p;
		p->prev = this;
		p->parent = parent;
	}

	void add_child(Menu *p)
	{
		child = p;
		p->parent = this;
	}

	virtual void exec() {};

	Menu *next;
	Menu *prev;
	Menu *child;
	Menu *parent;

	const char *title;
};

//  -----------------------------------------------

class Display
{
public:
	virtual void show_menu(const char *title) = 0;
};

//  -----------------------------------------------

class MenuApp : public Application
{
public:
	MenuApp(Menu *top, Display *disp)
		: current(top) 
		, display(disp)
	{}
	void onRotarySW(RotarySwitch::RSW_DIR dir) override;
	void onButton(int state) override;
	Menu * const get_current() const {return current;}
	void set_current(Menu *cur) {current = cur;}

	Display *get_display() { return display; }

private:
	Menu *current;
	Display *display;
};

struct Menu_Back : Menu
{
	Menu_Back(const char *title, const MenuApp *const app)
		: Menu(title), app(app)
	{}
	void exec() override;

	MenuApp *app;
};

#endif // UI_COMMON__H
