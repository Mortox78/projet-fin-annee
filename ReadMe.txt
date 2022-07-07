Build : You can build this project by typing "make" in the console inside the folder that contains the project.
Run   : You can type "./bin/gl"  in the console or "make run" once the project is build

Information:
    
    You can move with z, q, s and d. 
    You can press space bar for jump.
    You can shoot you're enemies with the left click of your mouse.
    You can stop the program by pressing the ESCAPE key.
    You can rebind all the keys in the options of the main menu.
    
    We used IMGUI for the UI.

    The file used for shader are placed in "include/Resources/"

--- Developed features ---
In the directory "Tools" (include/Tools for .hpp and src/Tools for .cpp):
	- We have a InputManager, that takes care of all the inputs of the game (move, jump, shoot ...).
	- We have a SaveManager, used to save and load the game.
	- We have a TimeManager, used to get the time that elapses during the game while it's running and gives a deltatime, the deltatime being the time bewteen each frames.

In the directory "Entity" (include/Entity for .hpp and src/Entity for .cpp)
	- We have a class Entity, contains basic value for player and enemy (hp, speed, attack, ect...).
	- We have a class Bullet, which takes care of the interactions of every bullets within the world(enemies, wall, ect...).

In the directory "Player" (include/Entity/Player for .hpp and src/Entity/Player for .cpp)
	- We have a class Player (children of Entity).
	- We have a class PlayerShoot, in this class there is the max and current number of ammo for the weapon and a function shoot in order to attack the enemies.

In the directory "Enemy" (include/Entity/Enemy for .hpp and src/Entity/Enemy for .cpp)
	- We have a class Enemy (children of Entity), who chases the player and can deal damage to him.

In the directory "DataStructure" (include/Core/DataStructure for .hpp and src/Core/DataStructure for .cpp)
	- We have a class GameObject, used for every object in the game, and that contains a list of AdditionalBehavior. 
	- We have a class AdditionalBehavior, The purpose of this class is to add script and physics to any GameObject in the game.
	- We have a class Graph.
	
In the directory "LowRenderer" (include/LowRenderer for .hpp and src/LowRenderer for .cpp)
	- We have a class Camera.
	- We have a class Light.
	- We have a class Mesh.
	- We have a class PlayerCamera, it's used to get a fps view of the game.

In the directory "Resources" (include/Resources for .hpp and src/Resources for .cpp)
	- We have a class Sprite, used to get sprite animations for enemies.
	- We have a class Texture, used to free and load texture.
	- We have a class Scene.
	- We have a class ResourcesManager.
	- We have a class Model, used to create basic forms like cubes, spheres, ect...



 --- Problem and Bug ---
