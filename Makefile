project=kratstom
CC=g++
STD=c++11
VARIABLES=-Wall -pedantic -I/usr/include/libxml2/
DEBUG=-Werror -g -ggdb -fno-omit-frame-pointer
FINAL_FILE=$(project)
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lxml2 -lstdc++
OBJS=build/gameobject.o build/main.o build/game.o build/Logger.o build/Config.o build/button.o build/sprite.o build/ResourcesManager.o build/AudioManager.o build/window.o build/scene.o build/mainmenu.o build/GameOverScene.o build/LevelSelect.o build/Credits.o build/gamescene.o build/vector2d.o build/scenemanager.o build/text.o build/VerticalLayoutGroup.o build/Unit.o build/Goblin.o build/Troll.o build/Map.o build/Tile.o build/Player.o build/Human.o build/Computer.o build/MonsterButton.o build/Tooltip.o build/ProgressBar.o build/Structure.o build/LivingStructure.o build/Base.o build/UnitDropOff.o build/TowerSlot.o build/Tower.o build/BombTower.o build/ArcherTower.o build/Missile.o build/Bomb.o build/Arrow.o

all: clean compile doc

clean:
	rm -f $(FINAL_FILE)
	rm -rf build/
	rm -rf doc/

compile: $(OBJS)
	$(CC) $(VARIABLES) $(DEBUG) $^ -o $(FINAL_FILE) $(LIBS)
	make copyAssets

copyAssets:
	yes | cp -r examples/* assets/
	mkdir -p assets/saves

run:
	./$(FINAL_FILE) DEBUG

build/Logger.o:  src/Engine/Logger/Logger.cpp src/Engine/Logger/Logger.h src/Engine/Logger/Color.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/main.o: src/main.cpp
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@


build/game.o: src/Game/Game.cpp src/Game/Game.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Config.o: src/Engine/Config.cpp src/Engine/Config.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/window.o: src/Engine/Window.cpp src/Engine/Window.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/sprite.o: src/Engine/Sprite.cpp src/Engine/Sprite.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/gameobject.o: src/Engine/GameObject.cpp src/Engine/GameObject.h
	mkdir -p build
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/ResourcesManager.o: src/Engine/Managers/ResourceManager.cpp src/Engine/Managers/ResourceManager.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/AudioManager.o: src/Engine/Managers/AudioManager.cpp src/Engine/Managers/AudioManager.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/button.o: src/Engine/UI/Button.cpp src/Engine/UI/Button.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/scene.o: src/Engine/Scene.cpp src/Engine/Scene.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/mainmenu.o: src/Game/Scenes/MainMenu/MainMenu.cpp src/Game/Scenes/MainMenu/MainMenu.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/GameOverScene.o: src/Game/Scenes/GameOver/GameOverScene.cpp src/Game/Scenes/GameOver/GameOverScene.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@


build/LevelSelect.o: src/Game/Scenes/LevelSelect/LevelSelect.cpp src/Game/Scenes/LevelSelect/LevelSelect.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Credits.o: src/Game/Scenes/Credits/Credits.cpp src/Game/Scenes/Credits/Credits.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/gamescene.o: src/Game/Scenes/GameScene/GameScene.cpp src/Game/Scenes/GameScene/GameScene.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/vector2d.o: src/Engine/Vector2D.cpp src/Engine/Vector2D.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/scenemanager.o: src/Engine/Managers/SceneManager.cpp src/Engine/Managers/SceneManager.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/text.o: src/Engine/UI/Text.cpp src/Engine/UI/Text.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/VerticalLayoutGroup.o: src/Engine/UI/VerticalLayoutGroup.cpp src/Engine/UI/VerticalLayoutGroup.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Unit.o: src/Game/Scenes/GameScene/GameObjects/Units/Unit.cpp src/Game/Scenes/GameScene/GameObjects/Units/Unit.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Goblin.o: src/Game/Scenes/GameScene/GameObjects/Units/Goblin.cpp src/Game/Scenes/GameScene/GameObjects/Units/Goblin.cpp
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Troll.o: src/Game/Scenes/GameScene/GameObjects/Units/Troll.cpp src/Game/Scenes/GameScene/GameObjects/Units/Troll.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Map.o: src/Game/Scenes/GameScene/GameObjects/Map/Map.cpp src/Game/Scenes/GameScene/GameObjects/Map/Map.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Tile.o: src/Game/Scenes/GameScene/GameObjects/Map/Tile.cpp src/Game/Scenes/GameScene/GameObjects/Map/Tile.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/InputTile.o: src/Game/Scenes/GameScene/GameObjects/Structures/UnitDropOff.cpp src/Game/Scenes/GameScene/GameObjects/Structures/UnitDropOff.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Player.o: src/Game/Scenes/GameScene/Players/Player.cpp src/Game/Scenes/GameScene/Players/Player.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Human.o: src/Game/Scenes/GameScene/Players/Human.cpp src/Game/Scenes/GameScene/Players/Human.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Computer.o: src/Game/Scenes/GameScene/Players/Computer.cpp src/Game/Scenes/GameScene/Players/Computer.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/MonsterButton.o: src/Game/Scenes/GameScene/GameObjects/Buttons/MonsterButton.cpp src/Game/Scenes/GameScene/GameObjects/Buttons/MonsterButton.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Tooltip.o: src/Game/Scenes/GameScene/GameObjects/Buttons/Tooltip.cpp src/Game/Scenes/GameScene/GameObjects/Buttons/Tooltip.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/ProgressBar.o: src/Engine/UI/ProgressBar.cpp src/Engine/UI/ProgressBar.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Structure.o: src/Game/Scenes/GameScene/GameObjects/Structures/Structure.cpp src/Game/Scenes/GameScene/GameObjects/Structures/Structure.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/LivingStructure.o: src/Game/Scenes/GameScene/GameObjects/Structures/LivingStructure.cpp src/Game/Scenes/GameScene/GameObjects/Structures/LivingStructure.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Base.o: src/Game/Scenes/GameScene/GameObjects/Structures/Base.cpp src/Game/Scenes/GameScene/GameObjects/Structures/Base.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/UnitDropOff.o: src/Game/Scenes/GameScene/GameObjects/Structures/UnitDropOff.cpp src/Game/Scenes/GameScene/GameObjects/Structures/UnitDropOff.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/TowerSlot.o: src/Game/Scenes/GameScene/GameObjects/Structures/TowerSlot.cpp src/Game/Scenes/GameScene/GameObjects/Structures/TowerSlot.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Tower.o: src/Game/Scenes/GameScene/GameObjects/Structures/Towers/Tower.cpp src/Game/Scenes/GameScene/GameObjects/Structures/Towers/Tower.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/BombTower.o: src/Game/Scenes/GameScene/GameObjects/Structures/Towers/BombTower.cpp src/Game/Scenes/GameScene/GameObjects/Structures/Towers/BombTower.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/ArcherTower.o: src/Game/Scenes/GameScene/GameObjects/Structures/Towers/ArcherTower.cpp src/Game/Scenes/GameScene/GameObjects/Structures/Towers/ArcherTower.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Missile.o: src/Game/Scenes/GameScene/GameObjects/Structures/Towers/Missiles/Missile.cpp src/Game/Scenes/GameScene/GameObjects/Structures/Towers/Missiles/Missile.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Bomb.o: src/Game/Scenes/GameScene/GameObjects/Structures/Towers/Missiles/Bomb.cpp src/Game/Scenes/GameScene/GameObjects/Structures/Towers/Missiles/Bomb.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

build/Arrow.o: src/Game/Scenes/GameScene/GameObjects/Structures/Towers/Missiles/Arrow.cpp src/Game/Scenes/GameScene/GameObjects/Structures/Towers/Missiles/Arrow.h
	$(CC) -std=$(STD) $(VARIABLES) $(DEBUG) -c $< -o $@

doc:
	doxygen


.PHONY: clean
.PHONY: run
.PHONY: doc