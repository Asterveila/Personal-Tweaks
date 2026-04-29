#include "ModernSettingsPopup.hpp"
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>

using namespace geode::prelude;

void openPersonalTweaksPopupGlobal() {
    ModernSettingsPopup::create()->show();
}

// Add button to MenuLayer
class $modify(ModernMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        
        auto spr = CCSprite::create("myChudDaughter.gif"_spr);
        auto settingsSprite = CircleButtonSprite::create(spr, CircleBaseColor::Green, CircleBaseSize::MediumAlt);
        
        auto settingsBtn = CCMenuItemSpriteExtra::create(
            settingsSprite,
            this,
            menu_selector(ModernMenuLayer::onOpenModernSettings)
        );
        
        auto menu = this->getChildByID("bottom-menu");
        if (menu) {
            settingsBtn->setID("personal-tweaks-btn"_spr);
            menu->addChild(settingsBtn);
            menu->updateLayout();
        }
        
        return true;
    }
    
    void onOpenModernSettings(CCObject*) {
        ModernSettingsPopup::create()->show();
    }
};

class $modify(ModernPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto spr = CCSprite::create("myChudDaughter.gif"_spr);
        auto settingsSprite = CircleButtonSprite::create(spr, CircleBaseColor::Green, CircleBaseSize::Small);
        
        auto settingsBtn = CCMenuItemSpriteExtra::create(
            settingsSprite,
            this,
            menu_selector(ModernPauseLayer::onOpenModernSettings)
        );
        
        settingsBtn->setPosition({-150.0f, -65.0f});
        
        auto menu = this->getChildByID("left-button-menu");
        if (menu) {
            settingsBtn->setID("personal-tweaks-btn"_spr);
            menu->addChild(settingsBtn);
        }
    }
    
    void onOpenModernSettings(CCObject*) {
        ModernSettingsPopup::create()->show();
    }
};

class $modify(ModernGarageLayer, GJGarageLayer) {
    bool init() {
        if (!GJGarageLayer::init()) return false;
        
        bool useModernUI = Mod::get()->getSettingValue<bool>("use-modern-ui");
        
        auto spr = CCSprite::create("myChudDaughter.gif"_spr);
        auto settingsSprite = CircleButtonSprite::create(spr, CircleBaseColor::Green, CircleBaseSize::Small);
        
        auto settingsBtn = CCMenuItemSpriteExtra::create(
            settingsSprite,
            this,
            menu_selector(ModernGarageLayer::onOpenModernSettings)
        );
        
        settingsBtn->setPosition({-200.0f, 100.0f});
        
        auto menu = this->getChildByID("shards-menu");

        if (menu) {
            menu->addChild(settingsBtn);
        } else {
            auto menuFr = CCMenu::create();
            menuFr->setContentSize(settingsSprite->getContentSize());
            menuFr->setID("personal-tweaks-garage-menu"_spr);
            menuFr->setPosition({20.f, 20.f});

            settingsBtn->setPosition({menuFr->getContentSize().width / 2.0f, menuFr->getContentSize().height / 2.0f});

            this->addChild(menuFr);
        }
        
        return true;
        
    }
    
    void onOpenModernSettings(CCObject*) {
        ModernSettingsPopup::create()->show();
    }
};

$on_game(Loaded) {
    listenForKeybindSettingPresses("modmenu-keybind", [](Keybind const& keybind, bool down, bool repeat, double timestamp) {
        if (down && !repeat) {
            openPersonalTweaksPopupGlobal();
        }
    });
}