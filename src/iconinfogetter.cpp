#include <Geode/modify/GJGarageLayer.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>
#include "Geode/utils/cocos.hpp"
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/binding/FLAlertLayer.hpp>

using namespace geode::prelude;

bool iconListingEnabled = Mod::get()->getSettingValue<bool>("iconlist-ft");

$on_mod(Loaded) {
    listenForSettingChanges<bool>("iconlist-ft", [](bool value) {
        iconListingEnabled = value;
    });
}

class $modify(ImSoLazyGarageLayer, GJGarageLayer) {
    struct Fields {
        std::vector<std::string> m_iconList;
    };

    void addIconToList(CCObject* sender) {
        auto addedSpr = CCSprite::create("addToList.png"_spr);
        auto fields = m_fields.self();

        IconInfo* selectedIcon = more_icons::activeIcon(m_selectedIconType);
        std::string iconName = selectedIcon->getShortName();

        fields->m_iconList.push_back(iconName);

        Notification::create("Icon " + iconName + " added!", addedSpr, 0.30f)->show();
    }

    void printListOfIcons(CCObject* sender) {
        auto fields = m_fields.self();
        auto errSpr = CCSprite::createWithSpriteFrameName("exMark_001.png");
        auto worked = CCSprite::createWithSpriteFrameName("GJ_completesIcon_001.png");

        auto configDir = Mod::get()->getConfigDir(true);
        auto filePath = configDir / "chosen_icons.txt";
        bool fileSaved = false;

        std::ofstream out(filePath);
        if (out.is_open()) {
            for (const auto& icon : fields->m_iconList) {
                out << icon << "\n";
            }
            out.close();
            fileSaved = true;
            geode::log::debug("Icon list saved to {}", filePath);
            Notification::create("Icon list saved to chosen_icons.txt!", worked, 0.5f)->show();
        }

        // Fallback: print to debug log if file failed
        if (!fileSaved) {
            std::string allIcons;
            for (const auto& icon : fields->m_iconList) {
                allIcons += icon + "\n";
            }
            geode::log::debug("Icon list:\n{}", allIcons);
            Notification::create("Failed to save file! List printed to debug.", errSpr, 0.5f)->show();
        }
    }

    void checkListPopup(CCObject* sender) {
        auto fields = m_fields.self();

        std::string allIcons;
        for (const auto& icon : fields->m_iconList) {
            allIcons += "- " + icon + "\n";
        }

        std::string popupContent = fmt::format("# Your Current Icon List: \n\n{}", allIcons);

        MDPopup::create(
            "Chosen icons list",
            popupContent,
            "ok",
            "thanks",
            static_cast<std::function<void(bool)>>(nullptr)
        )->show();
    }

    void removeLastIconFromList(CCObject* sender) {
        auto fields = m_fields.self();
        auto err = CCSprite::createWithSpriteFrameName("exMark_001.png");
        auto removedSpr = CCSprite::createWithSpriteFrameName("GJ_completesIcon_001.png");

        if (!fields->m_iconList.empty()) {
            std::string removed = fields->m_iconList.back();
            fields->m_iconList.pop_back();
            geode::log::debug("Removed icon: {}", removed);
            Notification::create("Removed last icon!", removedSpr, 0.3f)->show();
        } else {
            geode::log::debug("Icon list is already empty.");
            Notification::create(" Icon list is empty!", err, 0.3f)->show();
        }
    }

    void countMixIcons(CCObject* sender) {
        size_t cubeCount    = more_icons::getIconCount(IconType::Cube);
        size_t shipCount    = more_icons::getIconCount(IconType::Ship);
        size_t ballCount    = more_icons::getIconCount(IconType::Ball);
        size_t ufoCount     = more_icons::getIconCount(IconType::Ufo);
        size_t waveCount    = more_icons::getIconCount(IconType::Wave);
        size_t robotCount   = more_icons::getIconCount(IconType::Robot);
        size_t spiderCount  = more_icons::getIconCount(IconType::Spider);
        size_t swingCount   = more_icons::getIconCount(IconType::Swing);
        size_t jetpackCount = more_icons::getIconCount(IconType::Jetpack);

        size_t total = cubeCount + shipCount + ballCount + ufoCount + waveCount + robotCount + spiderCount + swingCount + jetpackCount;

        std::string infoData = fmt::format(
            "<cg>Cube</c>: {}\n<cp>Ship</c>: {}\n<cr>Ball</c>: {}\n<co>Ufo</c>: {}\n<cf>Wave</c>: {}\nRobot: {}\n<ca>Spider</c>: {}\n<cy>Swing</c>: {}\n<cp>Jetpack</c>: {}\n\n<cd>Total</c>: {}",
            cubeCount, shipCount, ballCount, ufoCount, waveCount,
            robotCount, spiderCount, swingCount, jetpackCount, total
        );

        IconInfo* thing = more_icons::activeIcon(m_selectedIconType);
        std::string packInfoString = fmt::format("{} Info", thing->getPackName());

        FLAlertLayer::create(packInfoString.c_str(), infoData.c_str(), "ok")->show();
    }

    bool init() {
        if (!GJGarageLayer::init()) return false;

        if (!iconListingEnabled) return true;

        float extraOffset = 0.f;
        bool isSeparateLoaded = Loader::get()->isModLoaded("weebify.separate_dual_icons");

        if (isSeparateLoaded) {
            extraOffset = 90.f;
        }
        
        auto buttonsMenu = CCMenu::create();
        buttonsMenu->setLayout(
            RowLayout::create()
                ->setGap(2.f)
                ->setAxisAlignment(AxisAlignment::End)
                ->setAxisReverse(false)
                ->setGrowCrossAxis(true)
                ->setCrossAxisOverflow(true)
                ->setAutoScale(false)
        );
        buttonsMenu->setContentSize({84.f, 84.f});
        buttonsMenu->setPosition({m_playerObject->getPositionX() + 90.f + extraOffset, m_playerObject->getPositionY()});
        buttonsMenu->setScale(0.6f);
        buttonsMenu->setID("pt-buttons-menu"_spr);
        this->addChild(buttonsMenu);

        auto addSpr = CircleButtonSprite::createWithSprite("addToList.png"_spr, 1.0f, CircleBaseColor::Pink, CircleBaseSize::Small);
        auto printSpr = CircleButtonSprite::createWithSprite("printList.png"_spr, 1.0f, CircleBaseColor::Cyan, CircleBaseSize::Small);
        auto removeLastSpr = CircleButtonSprite::createWithSprite("removeLast.png"_spr, 1.0f, CircleBaseColor::DarkAqua, CircleBaseSize::Small);
        auto checkListSpr = CircleButtonSprite::createWithSprite("elPutisimoOjoDelBetterEditHermanoJajaj.png"_spr, 1.0f, CircleBaseColor::Green, CircleBaseSize::Small);

        auto addButton = CCMenuItemSpriteExtra::create(
            addSpr,
            this,
            menu_selector(ImSoLazyGarageLayer::addIconToList)
        );
        auto printButton = CCMenuItemSpriteExtra::create(
            printSpr, 
            this, 
            menu_selector(ImSoLazyGarageLayer::printListOfIcons)
        );
        auto removeLastButton = CCMenuItemSpriteExtra::create(
            removeLastSpr,
            this,
            menu_selector(ImSoLazyGarageLayer::removeLastIconFromList)
        );
        auto checkListButton = CCMenuItemSpriteExtra::create(
            checkListSpr,
            this,
            menu_selector(ImSoLazyGarageLayer::checkListPopup)
        );

        buttonsMenu->addChild(addButton);
        buttonsMenu->addChild(printButton);
        buttonsMenu->addChild(removeLastButton);
        buttonsMenu->addChild(checkListButton);

        buttonsMenu->updateLayout();

        // icon counter
        auto infoMenu = CCMenu::create();
        infoMenu->setContentSize({20.f, 20.f});
        infoMenu->setID("mix-info"_spr);
        
        auto infoSpr = CCSprite::create("mix-info.png"_spr);
        auto infoButton = CCMenuItemSpriteExtra::create(infoSpr, this, menu_selector(ImSoLazyGarageLayer::countMixIcons));

        infoMenu->addChild(infoButton);
        infoButton->setPosition({10.f, 10.f});

        auto selBg = this->getChildByID("select-background");

        auto addX = selBg->getContentSize().width / 2;
        auto addY = selBg->getContentSize().height / 2;

        infoMenu->setPosition({selBg->getPositionX() + addX, selBg->getPositionY() + addY});
        infoMenu->setScale(0.7f);

        this->addChild(infoMenu, 2);

        return true;
    }
};