//
// Created by ebalo on 24/03/20.
//

#ifndef TD_TOWERDEFENSE_TURRETGENERATOR_H
#define TD_TOWERDEFENSE_TURRETGENERATOR_H

#include <vector>
#include <unordered_map>
#include <map>
#include <forward_list>
#include <memory>
#include "Turret.h"
#include "../States/TurretState.h"
#include "ButtonIcon.h"
#include "../EventHandler.h"
#include "../Maps/Map.h"
#include "ButtonRect.h"
#include "../Observers/MouseHoverObserver.h"
#include "../Events/IconButtonHover.h"
#include "../Observers/MouseOutObserver.h"
#include "../Observers/MouseClickObserver.h"
#include "../Maps/RenderableMap.h"
#include "DrawableFactory.h"
#include "../Adapters/TurretAdapter.h"
#include "../Parser/Config.h"

// Add a short alias for std::shared_ptr to the current environment
template <class T> using sptr = std::shared_ptr<T>;

class TurretGenerator : public sf::Drawable, public sf::Transformable, public Notifier, public RenderableMap, public TurretAdapter {
private:
    std::vector<sptr<Turret>> initialized_instances;
    std::map<int, int> initialized_instances_map;

    bool menu_first_page = true,
            turret_placing_loop = false,
            render_left_arrow = false,
            render_right_arrow = true,
            translate_left_arrow = false,
            right_arrow_linked = true;
    int selected_turret,
            current_page = 1;

    sptr<Button> craft_virtual_button;
    sptr<Map> map;
    sptr<EventHandler> eventHandler;
    sptr<DrawableFactory> factory;

    sptr<sf::RenderWindow> window;
    sptr<sf::Font> font;

    int achievement_title_vertical_align = Config::getHeight() / 2 - 185,
            achievement_body_vertical_align = Config::getHeight() / 2 - 155;
    bool showing_achievement = false;
    sf::Clock achievement_clock;

    void generateInstancesMap();

    void computeSpriteSwitching(bool forward = true);

    void renderTurretMenu(sf::RenderTarget &target, sf::RenderStates states) const;

    void renderTurretAvailableLocations(sf::RenderTarget &target) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    TurretGenerator(const sptr<sf::RenderWindow> &window, sptr<sf::Font> font, const sptr<EventHandler> &eventHandler,
                    sptr<Map> map, bool is_easy, const sptr<Tower> &tower);

    sptr<Turret> generate(int turret_index);

    void selectTurret(TURRET_TYPE turret);

    void switchMenuPage(bool forward = true);

    void setTurretPlacement(bool state);

    sptr<sf::Sprite> cloneTurretSprite(int index);

    void destroyCraftedTurretSprite();

    void setCraftVirtualButton(sptr<Button> btn);

    sptr<sf::Font> getFont();

    Map *getMap();

    int getSelectedTurret();

    sptr<EventHandler> getEventHandler();

    void registerTurret(const sptr<Turret>& turret);
    sptr<std::vector<sptr<Turret>>> getRegisteredTurrets();
    const std::vector<sptr<Turret>>& getRegisteredTurretsAsReference();

    std::vector<sptr<Bullet>> getBullets();

    void showReachedAchievement() const;
    void setUpReachedAchievement(std::string title, std::string body);
};


#endif //TD_TOWERDEFENSE_TURRETGENERATOR_H
