#include "CardEffectStrategy.h"
#include "Game.h"

void TroopCardEffectStrategy::executeEffect() const {
    Game* game = Game::getInstance();
    int choice = InputHandler::getChoice(1, 9, "Chose a region (1-9) to place the troop card: ");
    Region& selectedRegion = game->getRegionsManager().getRegion(choice - 1);
    selectedRegion.addCard(game->getCurrentPlayer(), game->getCurrentCard());
}

void LeaderTacticsEffectStrategy::executeEffect() const {
    Game* game = Game::getInstance();
    int colorChoice = InputHandler::getChoice(1, 6, "Chose a color (1-6) you want to set: ");
    int numberChoice = InputHandler::getChoice(1, 10, "Chose a number you want to set: ");
    auto& selectedCard = dynamic_cast<SpecialTacticsCard&>(const_cast<Card&>(game->getCurrentCard()));
    selectedCard.setColor(static_cast<Color>(colorChoice - 1));
    selectedCard.setNumber(static_cast<Number>(numberChoice - 1));
    selectedCard.setTypeToTroop();
    int choice = InputHandler::getChoice(1, 9, "Chose a region (1-9) to place the troop card: ");
    Region& selectedRegion = game->getRegionsManager().getRegion(choice - 1);
    selectedRegion.addCard(game->getCurrentPlayer(), game->getCurrentCard());
}

void CompanionCavalryEffectStrategy::executeEffect() const {
    Game* game = Game::getInstance();
    int colorChoice = InputHandler::getChoice(1, 6, "Chose a color (1-6) you want to set: ");
    auto& selectedCard = dynamic_cast<SpecialTacticsCard&>(const_cast<Card&>(game->getCurrentCard()));
    selectedCard.setColor(static_cast<Color>(colorChoice - 1));
    selectedCard.setNumber(Number::EIGHT);
    selectedCard.setTypeToTroop();
    int choice = InputHandler::getChoice(1, 9, "Chose a region (1-9) to place the troop card: ");
    Region& selectedRegion = game->getRegionsManager().getRegion(choice - 1);
    selectedRegion.addCard(game->getCurrentPlayer(), game->getCurrentCard());
}


void ShieldBearersTacticsEffectStrategy::executeEffect() const {
    Game* game = Game::getInstance();
    int colorChoice = InputHandler::getChoice(1, 6, "Chose a color (1-6) you want to set: ");
    int numberChoice = InputHandler::getChoice(1, 3, "Chose a number (1-3) you want to set: ");
    auto& selectedCard = dynamic_cast<SpecialTacticsCard&>(const_cast<Card&>(game->getCurrentCard()));
    selectedCard.setColor(static_cast<Color>(colorChoice - 1));
    selectedCard.setNumber(static_cast<Number>(numberChoice - 1));
    selectedCard.setTypeToTroop();
    int choice = InputHandler::getChoice(1, 9, "Chose a region (1-9) to place the troop card: ");
    Region& selectedRegion = game->getRegionsManager().getRegion(choice - 1);
    selectedRegion.addCard(game->getCurrentPlayer(), game->getCurrentCard());
}

void FogTacticsEffectStrategy::executeEffect() const {

}

void MudTacticsEffectStrategy::executeEffect() const {
    Game* game = Game::getInstance();
    int regionChoice = InputHandler::getChoice(1, 9, "Chose a region (1-9) to use the mud effect: ");
    Region& selectedRegion = game->getRegionsManager().getRegion(regionChoice - 1);
    selectedRegion.setMaxTroopCard(4);
}

void ScoutTacticsEffectStrategy::executeEffect() const {
    Game* game = Game::getInstance();

    for (int i = 0; i < 3; i++) {
        int pileChoice = InputHandler::getChoice(1, 2, "From which pile would you like to draw a card? (1 for Troop, 2 for Tactics): ");
        if (pileChoice == 1) {
            game->getCurrentPlayer().drawCard(game->getTroopCardPile());
        } else {
            game->getCurrentPlayer().drawCard(game->getTacticsCardPile());
        }
    }

    for (int i = 0; i < 2; i++) {
        int cardChoice = InputHandler::getChoice(1, game->getCurrentPlayer().getHandsSize(), "Choose a card to place back into its pile: ");
        const Card& selectedCard = game->getCurrentPlayer().getCard(cardChoice);
        if (selectedCard.getType() == CardType::TROOP_CARD) {
            game->getTroopCardPile().addCard(selectedCard);
        } else {
            game->getTacticsCardPile().addCard(selectedCard);
        }
    }

    game->getDiscardPile().addCard(game->getCurrentCard());
}

void RedeployTacticsEffectStrategy::executeEffect() const {
    Game* game = Game::getInstance();
    int fromRegionChoice = InputHandler::getChoice(1, 9, "Chose a region (1-9) which have the card you want to redeploy: ");
    Region& fromRegion = game->getRegionsManager().getRegion(fromRegionChoice - 1);
    // 若是没牌，增加检测
    int cardChoice = InputHandler::getChoice(1, 3, "Chose a card (1-3) to traitor: ");
    const Card& selectedCard = fromRegion.getCard(game->getCurrentPlayer().getId(), cardChoice);
    int toRegionChoice = InputHandler::getChoice(1, 9, "Chose a region (1-9) where you want to deploy the card: ");
    Region& toRegion = game->getRegionsManager().getRegion(toRegionChoice - 1);

    fromRegion.removeCard(selectedCard);
    toRegion.addCard(game->getCurrentPlayer(), selectedCard);
    game->getDiscardPile().addCard(game->getCurrentCard());
}

void DeserterTacticsEffectStrategy::executeEffect() const {
    Game* game = Game::getInstance();
    int regionChoice = InputHandler::getChoice(1, 9, "Chose a region (1-9) which have the card you want to traitor: ");
    Region& selectedRegion = game->getRegionsManager().getRegion(regionChoice - 1);
    // 若是没牌，增加检测
    int cardChoice = InputHandler::getChoice(1, selectedRegion.getSize(game->getAnotherPlayer().getId()), "Chose a card to desert: ");
    const Card& selectedCard = selectedRegion.getCard(game->getAnotherPlayer().getId(), cardChoice);
    selectedRegion.removeCard(selectedCard);
    game->getDiscardPile().addCard(selectedCard);
}

void TraitorTacticsEffectStrategy::executeEffect() const {
    Game* game = Game::getInstance();
    int regionChoice = InputHandler::getChoice(1, 9, "Chose a region (1-9) to place the troop card: ");
    Region& selectedRegion = game->getRegionsManager().getRegion(regionChoice - 1);
    // 若是没牌，增加检测
    int cardChoice = InputHandler::getChoice(1, selectedRegion.getSize(game->getAnotherPlayer().getId()), "Chose a troop card to traitor: "); // 只考虑了部队卡的情况，没有考虑还有战术卡的情况
    const Card& selectedCard = selectedRegion.getCard(game->getAnotherPlayer().getId(), cardChoice);
    selectedRegion.removeCard(selectedCard);
    selectedRegion.addCard(game->getCurrentPlayer(), selectedCard);
    game->getDiscardPile().addCard(game->getCurrentCard());
}
