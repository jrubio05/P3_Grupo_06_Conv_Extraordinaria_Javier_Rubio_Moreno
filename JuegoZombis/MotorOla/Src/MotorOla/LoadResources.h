#pragma once

#ifdef MOTOR_EXPORTS
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include <map>
#include <string>
#include "utils/Singleton.h"
#include <filesystem>

using namespace std::filesystem;
using namespace std;

MOTOR_API class LoadResources : public Singleton<LoadResources> {
	friend Singleton<LoadResources>;
private:
	LoadResources(std::string assetDirPath = "./Assets");
public:
	virtual ~LoadResources();
	MOTOR_API string mes(string m);
	MOTOR_API string aud(string name);
	MOTOR_API string tex(string tex);
	MOTOR_API string scene(string scene);
	MOTOR_API string prefab(string prefab);
private:
	std::string assetDir; // RUTA PARA BUSCAR LOS ASSETS
	//
	map<string, string>mesh;	//.mesh
	map<string, string>audio;	//.mp3,.ogg,.wav
	map<string, string>textures;//.png,.jpg,.bmp
	map<string, string>scenes;	//.lua
	map<string, string>prefabs;
	//Si hay otro tipo a?adir el map
	void search(path p);
	void load(path p, size_t end, size_t pathLenght);
};
