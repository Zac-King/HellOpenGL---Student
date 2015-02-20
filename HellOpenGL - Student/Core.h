#pragma once

class Engine;

class Core
{
	friend class Engine;
protected:
	virtual bool init() { return true; } // create
	virtual bool step() { return true; } // update
	virtual bool term() { return true; } // destroy
};