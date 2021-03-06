#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"

#include "PugiXml\src\pugixml.hpp"

struct Properties
{
	struct Property
	{
		SString name;
		int value;
	};

	~Properties()
	{
		ListItem<Property*>* item;
		item = list.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}
		list.Clear();
	}

	int GetProperty(const char* name, int default_value = 0) const;
	void SetProperty(const char* name, int value);
	List<Property*> list;
};

struct Tile
{
	int id;
	Properties properties;
};

struct TileSet
{
	SString	name;
	int	firstgid;
	int margin;
	int	spacing;
	int	tileWidth;
	int	tileHeight;

	SDL_Texture* texture;
	int	texWidth;
	int	texHeight;
	int	numTilesWidth;
	int	numTilesHeight;
	int	offsetX;
	int	offsetY;

	List<Tile*> tilesetPropList;

	SDL_Rect GetTileRect(int id) const;

	// function that gives id and returns its properties
	Tile* GetPropList(int id) const;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

struct MapLayer
{
	SString	name;
	int width;
	int height;
	uint* data;

	Properties properties;

	MapLayer() : data(NULL) {}

	~MapLayer() { RELEASE(data); }

	inline uint Get(int x, int y) const { return data[(y * width) + x]; }
};

struct MapData
{
	int width;
	int	height;
	int	tileWidth;
	int	tileHeight;
	SDL_Color backgroundColor;
	MapTypes type;
	List<TileSet*> tilesets;
	List<MapLayer*> layers;
};

class Map : public Module
{
public:
	Map();

	// Destructor
	virtual ~Map();

	void Init();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	iPoint MapToWorld(int x, int y) const;
	MapTypes StrToMapType(SString s);

	// Changes property to value assigned
	void SetTileProperty(int x, int y, const char* property, int value, bool nonMovementCollision = false, bool isObject = false);

	// Gets the value of a property in a given tile
	int GetTileProperty(int x, int y, const char* property, bool nonMovementCollision = false, bool isObject = false) const;


	bool Map::CreateWalkabilityMap(int* width, int* height, uchar** buffer) const;

private:
	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetProperties(pugi::xml_node& node, TileSet* set);
	bool LoadProperties(pugi::xml_node& node, Properties& properties);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool StoreId(pugi::xml_node& node, MapLayer* layer, int index);
	void LogInfo();

	TileSet* GetTilesetFromTileId(int id) const;

public:
	MapData data;

private:
	pugi::xml_document mapFile;
	SString folder;
	bool mapLoaded;
	bool loadAll;
	
};

#endif // __MAP_H__