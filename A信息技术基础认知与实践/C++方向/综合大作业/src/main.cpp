#include "Prelude.hpp"
#include "prefabs/Bullet.hpp"
#include "prefabs/DialogBox.hpp"
#include "prefabs/Banner.hpp"
#include "prefabs/Mob.hpp"
#include "prefabs/Player.hpp"
#include "prefabs/Root.hpp"
#include "systems/MusicControl.hpp"
#include "utils/DialogGenerator.hpp"
#include "prefabs/SimpleMapLayer.hpp"
#include "components/SceneTree.hpp"
#include "prefabs/SplashScreen.hpp"

void onPlayerDeath(game::prefab::EOnPlayerDeathEvent e) {
    game::prefab::DialogBox dialogBox = game::prefab::DialogBox::create();
    auto dialogs = game::DialogGenerator()
            .fromJson("assets/dialog/end.json")
            .generate();
    dialogBox.loadDialog("dialogEnd", dialogs);
    dialogBox.setVisibility(true);
}

void cleanMobBullets() {
    for (auto entity : game::getRegistry().view<game::prefab::GBulletComponent>()) {
        game::UnmountUtils::queueUnmount(entity);
    }
}

void makeMobs() {
    auto& root = game::getRegistry().ctx().get<game::prefab::Root>();
    for (int i = 0; i < static_cast<int>(game::random(12, 16)); i++) {
        game::prefab::Mob mob = game::prefab::Mob::create(game::random({-512.f, -512.f}, { 512.f, 512.f }));
        root.mountChild(mob.getEntity());
    }
}

void onDialogCompleted(game::prefab::EOnDialogBoxCompletedEvent e) {
    static bool shouldClose = false;

    if (shouldClose) {
        game::getGame().getWindow().getRawWindow()->close();
    } else {
        shouldClose = true;
    }

    game::prefab::Player player = game::prefab::Player::create();
    auto& root = game::getRegistry().ctx().get<game::prefab::Root>();

    root.mountChild(player.getEntity());
    game::SceneTreeUtils::unmount(e.entity);

    makeMobs();
}

void onBannerComplete(game::prefab::EOnBannerCompleteEvent e) {
    auto& registry = game::getRegistry();
    game::UnmountUtils::queueUnmount(e.banner);
    makeMobs();
}

void onMobDeath(game::prefab::EOnMobDeathEvent e) {
    auto& registry = game::getRegistry();
    size_t size = 0;
    registry.view<game::prefab::GMobComponent>().each([&size](entt::entity e, game::prefab::GMobComponent&) {
        if (!game::UnmountUtils::isUnmountingQueued(e)) {
            size++;
        }
    });

    game::getLogger().logDebug("Mob hit, remaining: " + std::to_string(size));
    if (size == 0) {
        game::prefab::Banner banner = game::prefab::Banner::create();
        banner.setText("STAGE CLEARED");
        banner.launch();
        cleanMobBullets();
    }
}

void onSplashScreenCompleted(game::prefab::EOnSplashScreenCompletedEvent e) {
    game::UnmountUtils::queueUnmount(e.entity);

    try {
        auto music = game::ResourceManager::getBinaryFileCache()
                .load(entt::hashed_string{"bgm"},"assets/music/bgm.ogg").first->second;
        game::SMusicSystem::playMusic(music, game::MusicConfig{75.f, true});
    } catch (std::exception& e) {
        game::getLogger().logError("Failed to load music: " + std::string(e.what()));
    }

    game::prefab::SimpleMapLayer::create(0);
    game::prefab::SimpleMapLayer::create(96);

    game::prefab::DialogBox dialogBox = game::prefab::DialogBox::create();
    game::getRegistry().ctx().emplace<game::prefab::DialogBox>(dialogBox);

    auto texture0 = game::ResourceManager::getTextureCache()
            .load(entt::hashed_string { "portrait0" }, "assets/image/character0.png", sf::IntRect {{0, 0}, {1024, 1536}}).first->second;

    auto texture1 = game::ResourceManager::getTextureCache()
            .load(entt::hashed_string { "portrait1" }, "assets/image/character1.png", sf::IntRect {{0, 0}, {1024, 1536}}).first->second;
    auto dialogs = game::DialogGenerator()
            .fromJson("assets/dialog/start.json")
            .generate();
    dialogBox.loadDialog("dialogStart", dialogs);
    dialogBox.setVisibility(true);
}

int main() {
    game::Game& game = game::Game::createGame();
    game.setConfig({.windowTitle = "Game - C++ 25sp", .fps = 60, .vsync = false});

    game::prefab::Root root = game::prefab::Root::create();
    game::getRegistry().ctx().emplace<game::prefab::Root>(root);

    game.getWindow().setZoomFactor(0.5f);

    game::prefab::SplashScreen splashScreen = game::prefab::SplashScreen::create();

    auto& eventDispatcher = game::getEventDispatcher();

    eventDispatcher.sink<game::prefab::EOnSplashScreenCompletedEvent>().connect<&onSplashScreenCompleted>();
    eventDispatcher.sink<game::prefab::EOnDialogBoxCompletedEvent>().connect<&onDialogCompleted>();
    eventDispatcher.sink<game::prefab::EOnPlayerDeathEvent>().connect<&onPlayerDeath>();
    eventDispatcher.sink<game::prefab::EOnMobDeathEvent>().connect<&onMobDeath>();
    eventDispatcher.sink<game::prefab::EOnBannerCompleteEvent>().connect<&onBannerComplete>();

    game.run();
}
