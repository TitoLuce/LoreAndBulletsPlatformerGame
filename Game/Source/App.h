#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"

#include "PugiXml/src/pugixml.hpp"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;
class Map;
class TitleScreen;
class Transition;
class LogoScreen;
class Player;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	//Request to save & load
	void LoadRequest();
	void SaveRequest();

private:

	// Load config file
	pugi::xml_node App::LoadConfig(pugi::xml_document& configFile) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	//Load & save on an xml file
	bool LoadGame();
	bool SaveGame();

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Scene* scene;
	Map* map;
	TitleScreen* titleScreen;
	Transition* transition;
	LogoScreen* logoScreen;
	Player* player;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;
	uint frames;
	float dt;

	bool saveRequest, loadRequest;
	pugi::xml_document saveFile;
	pugi::xml_node save;
};

extern App* app;

#endif	// __APP_H__