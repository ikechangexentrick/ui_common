#include "ui_common.h"

static bool update_flag = false;

void Application::register_update()
{
	update_flag = true;
}

bool Application::should_update() const
{ 
	bool ret = update_flag;
	update_flag = false;
	return ret;
}

// ------------------------------------------

void MenuApp::onRotarySW(RotarySwitch::RSW_DIR dir)
{
	if (dir == RotarySwitch::CW) {
		if (current->next) current = current->next;

	} else {
		if (current->prev) current = current->prev;

	}

	display->show_menu(current->get_title());
}

void MenuApp::onButton(int state)
{
	if (state == 1) {
		//serial_log("MenuApp::onButton: current= %s", current->get_title());
		if (current->child) {
			current->exec();
			current = current->child;
			//serial_log("MenuApp::onButton: child= %s", current->get_title());
			display->show_menu(current->get_title());
		} else current->exec();
	}
}

void Menu_Back::exec() {
	auto current = app->get_current();
	//serial_log("Menu_Back::exec: current= %s", current->get_title());
	if (current->parent) {
	//serial_log("Menu_Back::exec: parent= %s", current->parent->get_title());
		current = current->parent;
		app->set_current(current);
		app->get_display()->show_menu(current->get_title());
	}
}


