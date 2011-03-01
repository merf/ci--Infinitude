/*
 *  InfinitudeApp.h
 *  Infinitude
 *
 *  Created by Neil Wallace on 01/03/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "cinder/app/AppBasic.h"

class InfiniThing;

class InfinitudeAppApp : public ci::app::AppBasic {
public:
	~InfinitudeAppApp() {quit();}
	void setup();
	void quit();
	void keyDown(ci::app::KeyEvent event);	
	void update();
	void draw();
	
	InfiniThing* mp_InfiniThing;
	
	static InfinitudeAppApp* mp_App;
};