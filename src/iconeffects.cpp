#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

auto colorMod = Mod::get();
struct CustomColorSettings {
    bool enableP1 = false;
    bool enableP2 = false;
    
    // Player 1
    cocos2d::ccColor3B p1Primary = {255, 255, 255};
    cocos2d::ccColor3B p1Secondary = {255, 255, 255};
    cocos2d::ccColor3B p1Glow = {255, 255, 255};
    cocos2d::ccColor3B p1Wave = {255, 255, 255};
    cocos2d::ccColor3B p1Trail = {255, 255, 255};
    cocos2d::ccColor3B p1GhostTrail = {255, 255, 255};
    cocos2d::ccColor3B p1DashFire = {255, 255, 255};
    cocos2d::ccColor3B p1UfoDome = {255, 255, 255};
    
    // Player 2
    cocos2d::ccColor3B p2Primary = {255, 255, 255};
    cocos2d::ccColor3B p2Secondary = {255, 255, 255};
    cocos2d::ccColor3B p2Glow = {255, 255, 255};
    cocos2d::ccColor3B p2Wave = {255, 255, 255};
    cocos2d::ccColor3B p2Trail = {255, 255, 255};
    cocos2d::ccColor3B p2GhostTrail = {255, 255, 255};
    cocos2d::ccColor3B p2DashFire = {255, 255, 255};
    cocos2d::ccColor3B p2UfoDome = {255, 255, 255};
    
    // Tinting toggles
    bool tintWaveP1 = false;
    bool tintWaveP2 = false;
    bool tintTrailP1 = false;
    bool tintTrailP2 = false;
    bool tintGhostTrailP1 = false;
    bool tintGhostTrailP2 = false;
    bool tintDashFireP1 = false;
    bool tintDashFireP2 = false;
    bool tintUfoDomeP1 = false;
    bool tintUfoDomeP2 = false;
    
    // Particle settings
    bool tintMainParticlesP1 = false;
    bool tintMainParticlesP2 = false;
    bool tintUfoClickParticlesP1 = false;
    bool tintUfoClickParticlesP2 = false;
    bool overrideAllVariances = false;
    
    cocos2d::ccColor4B p1MainParticlesStart = {255, 255, 255, 255};
    cocos2d::ccColor4B p1MainParticlesEnd = {255, 255, 255, 255};
    cocos2d::ccColor4B p1UfoClickParticlesStart = {255, 255, 255, 255};
    cocos2d::ccColor4B p1UfoClickParticlesEnd = {255, 255, 255, 255};
    
    cocos2d::ccColor4B p2MainParticlesStart = {255, 255, 255, 255};
    cocos2d::ccColor4B p2MainParticlesEnd = {255, 255, 255, 255};
    cocos2d::ccColor4B p2UfoClickParticlesStart = {255, 255, 255, 255};
    cocos2d::ccColor4B p2UfoClickParticlesEnd = {255, 255, 255, 255};
    
    cocos2d::ccColor4B variancesOverride = {10, 10, 10, 10};
};

static CustomColorSettings g_customColorSettings;

void loadAllColorSettings() {
    auto& cc = g_customColorSettings;
    cc.enableP1 = colorMod->getSettingValue<bool>("enable-customcolors-p1");
    cc.enableP2 = colorMod->getSettingValue<bool>("enable-customcolors-p2");
    
    cc.p1Primary = colorMod->getSettingValue<cocos2d::ccColor3B>("p1-primary");
    cc.p1Secondary = colorMod->getSettingValue<cocos2d::ccColor3B>("p1-secondary");
    cc.p1Glow = colorMod->getSettingValue<cocos2d::ccColor3B>("p1-glow");
    cc.p1Wave = colorMod->getSettingValue<cocos2d::ccColor3B>("p1-wave");
    cc.p1Trail = colorMod->getSettingValue<cocos2d::ccColor3B>("p1-trail");
    cc.p1GhostTrail = colorMod->getSettingValue<cocos2d::ccColor3B>("p1-ghost-trail");
    cc.p1DashFire = colorMod->getSettingValue<cocos2d::ccColor3B>("p1-dashfire");
    cc.p1UfoDome = colorMod->getSettingValue<cocos2d::ccColor3B>("p1-ufodome");
    
    cc.p2Primary = colorMod->getSettingValue<cocos2d::ccColor3B>("p2-primary");
    cc.p2Secondary = colorMod->getSettingValue<cocos2d::ccColor3B>("p2-secondary");
    cc.p2Glow = colorMod->getSettingValue<cocos2d::ccColor3B>("p2-glow");
    cc.p2Wave = colorMod->getSettingValue<cocos2d::ccColor3B>("p2-wave");
    cc.p2Trail = colorMod->getSettingValue<cocos2d::ccColor3B>("p2-trail");
    cc.p2GhostTrail = colorMod->getSettingValue<cocos2d::ccColor3B>("p2-ghost-trail");
    cc.p2DashFire = colorMod->getSettingValue<cocos2d::ccColor3B>("p2-dashfire");
    cc.p2UfoDome = colorMod->getSettingValue<cocos2d::ccColor3B>("p2-ufodome");
    
    cc.tintWaveP1 = colorMod->getSettingValue<bool>("tint-wave-p1");
    cc.tintWaveP2 = colorMod->getSettingValue<bool>("tint-wave-p2");
    cc.tintTrailP1 = colorMod->getSettingValue<bool>("tint-trail-p1");
    cc.tintTrailP2 = colorMod->getSettingValue<bool>("tint-trail-p2");
    cc.tintGhostTrailP1 = colorMod->getSettingValue<bool>("tint-ghost-trail-p1");
    cc.tintGhostTrailP2 = colorMod->getSettingValue<bool>("tint-ghost-trail-p2");
    cc.tintDashFireP1 = colorMod->getSettingValue<bool>("tint-dashfire-p1");
    cc.tintDashFireP2 = colorMod->getSettingValue<bool>("tint-dashfire-p2");
    cc.tintUfoDomeP1 = colorMod->getSettingValue<bool>("tint-ufodome-p1");
    cc.tintUfoDomeP2 = colorMod->getSettingValue<bool>("tint-ufodome-p2");
    
    cc.tintMainParticlesP1 = colorMod->getSettingValue<bool>("tint-mainparticles-p1");
    cc.tintMainParticlesP2 = colorMod->getSettingValue<bool>("tint-mainparticles-p2");
    cc.tintUfoClickParticlesP1 = colorMod->getSettingValue<bool>("tint-ufo-click-particles-p1");
    cc.tintUfoClickParticlesP2 = colorMod->getSettingValue<bool>("tint-ufo-click-particles-p2");
    cc.overrideAllVariances = colorMod->getSettingValue<bool>("override-all-variances");
    
    cc.p1MainParticlesStart = colorMod->getSettingValue<cocos2d::ccColor4B>("p1-main-particles-start");
    cc.p1MainParticlesEnd = colorMod->getSettingValue<cocos2d::ccColor4B>("p1-main-particles-end");
    cc.p1UfoClickParticlesStart = colorMod->getSettingValue<cocos2d::ccColor4B>("p1-ufo-click-particles-start");
    cc.p1UfoClickParticlesEnd = colorMod->getSettingValue<cocos2d::ccColor4B>("p1-ufo-click-particles-end");
    
    cc.p2MainParticlesStart = colorMod->getSettingValue<cocos2d::ccColor4B>("p2-main-particles-start");
    cc.p2MainParticlesEnd = colorMod->getSettingValue<cocos2d::ccColor4B>("p2-main-particles-end");
    cc.p2UfoClickParticlesStart = colorMod->getSettingValue<cocos2d::ccColor4B>("p2-ufo-click-particles-start");
    cc.p2UfoClickParticlesEnd = colorMod->getSettingValue<cocos2d::ccColor4B>("p2-ufo-click-particles-end");
    
    cc.variancesOverride = colorMod->getSettingValue<cocos2d::ccColor4B>("variances-override");
}

$on_mod(Loaded) {
    loadAllColorSettings();
    
    listenForSettingChanges("enable-customcolors-p1", [](bool value) { g_customColorSettings.enableP1 = value; });
    listenForSettingChanges("enable-customcolors-p2", [](bool value) { g_customColorSettings.enableP2 = value; });
    
    listenForSettingChanges("tint-wave-p1", [](bool value) { g_customColorSettings.tintWaveP1 = value; });
    listenForSettingChanges("tint-wave-p2", [](bool value) { g_customColorSettings.tintWaveP2 = value; });
    listenForSettingChanges("tint-trail-p1", [](bool value) { g_customColorSettings.tintTrailP1 = value; });
    listenForSettingChanges("tint-trail-p2", [](bool value) { g_customColorSettings.tintTrailP2 = value; });
    listenForSettingChanges("tint-ghost-trail-p1", [](bool value) { g_customColorSettings.tintGhostTrailP1 = value; });
    listenForSettingChanges("tint-ghost-trail-p2", [](bool value) { g_customColorSettings.tintGhostTrailP2 = value; });
    listenForSettingChanges("tint-dashfire-p1", [](bool value) { g_customColorSettings.tintDashFireP1 = value; });
    listenForSettingChanges("tint-dashfire-p2", [](bool value) { g_customColorSettings.tintDashFireP2 = value; });
    listenForSettingChanges("tint-ufodome-p1", [](bool value) { g_customColorSettings.tintUfoDomeP1 = value; });
    listenForSettingChanges("tint-ufodome-p2", [](bool value) { g_customColorSettings.tintUfoDomeP2 = value; });
    
    listenForSettingChanges("tint-mainparticles-p1", [](bool value) { g_customColorSettings.tintMainParticlesP1 = value; });
    listenForSettingChanges("tint-mainparticles-p2", [](bool value) { g_customColorSettings.tintMainParticlesP2 = value; });
    listenForSettingChanges("tint-ufo-click-particles-p1", [](bool value) { g_customColorSettings.tintUfoClickParticlesP1 = value; });
    listenForSettingChanges("tint-ufo-click-particles-p2", [](bool value) { g_customColorSettings.tintUfoClickParticlesP2 = value; });
    listenForSettingChanges("override-all-variances", [](bool value) { g_customColorSettings.overrideAllVariances = value; });
    
    // Player 1 colors
    listenForSettingChanges("p1-primary", [](cocos2d::ccColor3B value) { g_customColorSettings.p1Primary = value; });
    listenForSettingChanges("p1-secondary", [](cocos2d::ccColor3B value) { g_customColorSettings.p1Secondary = value; });
    listenForSettingChanges("p1-glow", [](cocos2d::ccColor3B value) { g_customColorSettings.p1Glow = value; });
    listenForSettingChanges("p1-wave", [](cocos2d::ccColor3B value) { g_customColorSettings.p1Wave = value; });
    listenForSettingChanges("p1-trail", [](cocos2d::ccColor3B value) { g_customColorSettings.p1Trail = value; });
    listenForSettingChanges("p1-ghost-trail", [](cocos2d::ccColor3B value) { g_customColorSettings.p1GhostTrail = value; });
    listenForSettingChanges("p1-dashfire", [](cocos2d::ccColor3B value) { g_customColorSettings.p1DashFire = value; });
    listenForSettingChanges("p1-ufodome", [](cocos2d::ccColor3B value) { g_customColorSettings.p1UfoDome = value; });
    listenForSettingChanges("p1-main-particles-start", [](cocos2d::ccColor4B value) { g_customColorSettings.p1MainParticlesStart = value; });
    listenForSettingChanges("p1-main-particles-end", [](cocos2d::ccColor4B value) { g_customColorSettings.p1MainParticlesEnd = value; });
    listenForSettingChanges("p1-ufo-click-particles-start", [](cocos2d::ccColor4B value) { g_customColorSettings.p1UfoClickParticlesStart = value; });
    listenForSettingChanges("p1-ufo-click-particles-end", [](cocos2d::ccColor4B value) { g_customColorSettings.p1UfoClickParticlesEnd = value; });
    
    // Player 2 colors
    listenForSettingChanges("p2-primary", [](cocos2d::ccColor3B value) { g_customColorSettings.p2Primary = value; });
    listenForSettingChanges("p2-secondary", [](cocos2d::ccColor3B value) { g_customColorSettings.p2Secondary = value; });
    listenForSettingChanges("p2-glow", [](cocos2d::ccColor3B value) { g_customColorSettings.p2Glow = value; });
    listenForSettingChanges("p2-wave", [](cocos2d::ccColor3B value) { g_customColorSettings.p2Wave = value; });
    listenForSettingChanges("p2-trail", [](cocos2d::ccColor3B value) { g_customColorSettings.p2Trail = value; });
    listenForSettingChanges("p2-ghost-trail", [](cocos2d::ccColor3B value) { g_customColorSettings.p2GhostTrail = value; });
    listenForSettingChanges("p2-dashfire", [](cocos2d::ccColor3B value) { g_customColorSettings.p2DashFire = value; });
    listenForSettingChanges("p2-ufodome", [](cocos2d::ccColor3B value) { g_customColorSettings.p2UfoDome = value; });
    listenForSettingChanges("p2-main-particles-start", [](cocos2d::ccColor4B value) { g_customColorSettings.p2MainParticlesStart = value; });
    listenForSettingChanges("p2-main-particles-end", [](cocos2d::ccColor4B value) { g_customColorSettings.p2MainParticlesEnd = value; });
    listenForSettingChanges("p2-ufo-click-particles-start", [](cocos2d::ccColor4B value) { g_customColorSettings.p2UfoClickParticlesStart = value; });
    listenForSettingChanges("p2-ufo-click-particles-end", [](cocos2d::ccColor4B value) { g_customColorSettings.p2UfoClickParticlesEnd = value; });
    
    listenForSettingChanges("variances-override", [](cocos2d::ccColor4B value) { g_customColorSettings.variancesOverride = value; });
}

// ============================================================================
// GAMEMANAGER - BASIC COLORS
// ============================================================================
class $modify(CustomColorsGM, GameManager) {
    ccColor3B colorForIdx(int index) {
        ccColor3B ret = GameManager::colorForIdx(index);
        
        auto gm = GameManager::sharedState();
        int col1Id = gm->getPlayerColor();
        int col2Id = gm->getPlayerColor2();
        int glowId = gm->getPlayerGlowColor();
        
        // Check for Separate Dual Icons mod
        bool hasSeparateDual = Loader::get()->isModLoaded("weebify.separate_dual_icons");
        int p2col1Id = col1Id;
        int p2col2Id = col2Id;
        int p2glowId = glowId;
        
        if (hasSeparateDual) {
            auto sdlMod = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
            p2col1Id = sdlMod->getSavedValue<int>("color1", col1Id);
            p2col2Id = sdlMod->getSavedValue<int>("color2", col2Id);
            p2glowId = sdlMod->getSavedValue<int>("colorglow", glowId);
        }
        
        // Player 1 Custom Colors
        if (g_customColorSettings.enableP1) {
            if (index == col1Id) {
                ret = g_customColorSettings.p1Primary;
            } else if (index == col2Id) {
                ret = g_customColorSettings.p1Secondary;
            } else if (index == glowId) {
                ret = g_customColorSettings.p1Glow;
            }
        }
        
        // Player 2 Custom Colors
        if (g_customColorSettings.enableP2 && hasSeparateDual) {
            if (index == p2col1Id) {
                ret = g_customColorSettings.p2Primary;
            } else if (index == p2col2Id) {
                ret = g_customColorSettings.p2Secondary;
            } else if (index == p2glowId) {
                ret = g_customColorSettings.p2Glow;
            }
        }
        
        return ret;
    }
};

// ============================================================================
// PLAYEROBJECT - MANUALLY APPLY SEPARATE STUFF IF ENABLED
// ============================================================================
class $modify(CustomColorsPlayer, PlayerObject) {
    cocos2d::ccColor4F toColor4F(const cocos2d::ccColor3B& color) {
        return {color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, 1.0f};
    }
    
    cocos2d::ccColor4F toColor4F(const cocos2d::ccColor4B& color) {
        return {color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f};
    }
    
    void applySpecialTinting() {
        bool isP2 = m_isSecondPlayer;
        auto& cc = g_customColorSettings;
        
        bool useCustomP1 = cc.enableP1 && !isP2;
        bool useCustomP2 = cc.enableP2 && isP2;
        
        if (!useCustomP1 && !useCustomP2) return;
        
        // Wave Trail
        if (m_waveTrail) {
            bool shouldTint = isP2 ? cc.tintWaveP2 : cc.tintWaveP1;
            if (shouldTint) {
                auto waveColor = isP2 ? cc.p2Wave : cc.p1Wave;
                m_waveTrail->setColor(waveColor);
            }
        }
        
        // Regular Trail
        if (m_regularTrail) {
            bool shouldTint = isP2 ? cc.tintTrailP2 : cc.tintTrailP1;
            if (shouldTint) {
                auto trailColor = isP2 ? cc.p2Trail : cc.p1Trail;
                m_regularTrail->setColor(trailColor);
            }
        }
        
        // Ghost Trail
        if (m_ghostTrail) {
            bool shouldTint = isP2 ? cc.tintGhostTrailP2 : cc.tintGhostTrailP1;
            if (shouldTint) {
                auto ghostColor = isP2 ? cc.p2GhostTrail : cc.p1GhostTrail;
                m_ghostTrail->m_color = ghostColor;
            }
        }
        
        // Dash Fire
        if (m_dashFireSprite) {
            bool shouldTint = isP2 ? cc.tintDashFireP2 : cc.tintDashFireP1;
            if (shouldTint) {
                auto dashColor = isP2 ? cc.p2DashFire : cc.p1DashFire;
                m_dashFireSprite->setColor(dashColor);
                if (m_dashParticles) {
                    auto dashStart = toColor4F(dashColor);
                    auto dashEnd = dashStart;
                    dashEnd.a = 0.0f;
                    m_dashParticles->m_tStartColor = dashStart;
                    m_dashParticles->m_tEndColor = dashEnd;
                }
            }
        }
        
        // UFO Dome
        if (m_isBird && m_birdVehicle) {
            bool shouldTint = isP2 ? cc.tintUfoDomeP2 : cc.tintUfoDomeP1;
            if (shouldTint) {
                auto domeColor = isP2 ? cc.p2UfoDome : cc.p1UfoDome;
                m_birdVehicle->setColor(domeColor);
            }
        }
        
        // Particles
        auto applyParticleColors = [&](cocos2d::CCParticleSystem* particle, const cocos2d::ccColor4F& start, const cocos2d::ccColor4F& end) {
            if (particle) {
                particle->m_tStartColor = start;
                particle->m_tEndColor = end;
                if (cc.overrideAllVariances) {
                    auto variance = toColor4F(cc.variancesOverride);
                    particle->m_tStartColorVar = variance;
                    particle->m_tEndColorVar = variance;
                }
            }
        };
        
        // Main Particles
        bool shouldTintMain = isP2 ? cc.tintMainParticlesP2 : cc.tintMainParticlesP1;
        if (shouldTintMain) {
            auto startColor = toColor4F(isP2 ? cc.p2MainParticlesStart : cc.p1MainParticlesStart);
            auto endColor = toColor4F(isP2 ? cc.p2MainParticlesEnd : cc.p1MainParticlesEnd);
            
            applyParticleColors(m_playerGroundParticles, startColor, endColor);
            applyParticleColors(m_landParticles0, startColor, endColor);
            applyParticleColors(m_landParticles1, startColor, endColor);
            applyParticleColors(m_vehicleGroundParticles, startColor, endColor);
        }
        
        // UFO Click Particles
        bool shouldTintUfo = isP2 ? cc.tintUfoClickParticlesP2 : cc.tintUfoClickParticlesP1;
        if (shouldTintUfo) {
            auto startColor = toColor4F(isP2 ? cc.p2UfoClickParticlesStart : cc.p1UfoClickParticlesStart);
            auto endColor = toColor4F(isP2 ? cc.p2UfoClickParticlesEnd : cc.p1UfoClickParticlesEnd);
            applyParticleColors(m_ufoClickParticles, startColor, endColor);
        }
    }
    
    void update(float dt) {
        PlayerObject::update(dt);
        applySpecialTinting();
    }
};

class $modify(CustomColorsPlayLayer, PlayLayer) {
    void resume() {
        PlayLayer::resume();
        loadAllColorSettings();
    }
    
    void resumeAndRestart(bool p0) {
        PlayLayer::resumeAndRestart(p0);
        loadAllColorSettings();
    }
};