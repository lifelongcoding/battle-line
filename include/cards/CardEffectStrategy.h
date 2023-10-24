#pragma once

#include <iostream>


class CardEffectStrategy {
public:
    virtual void executeEffect() const = 0;
};

class TroopCardEffectStrategy : public CardEffectStrategy {
public:
    void executeEffect() const override;
};

class LeaderTacticsEffectStrategy : public CardEffectStrategy {
public:
    void executeEffect() const override;
};

class CompanionCavalryEffectStrategy : public CardEffectStrategy {
public:
    void executeEffect() const override;
};

class ShieldBearersTacticsEffectStrategy : public CardEffectStrategy {
public:
    void executeEffect() const override;
};

class FogTacticsEffectStrategy : public CardEffectStrategy {
public:
    void executeEffect() const override;
};

class MudTacticsEffectStrategy : public CardEffectStrategy {
public:
    void executeEffect() const override;
};

class ScoutTacticsEffectStrategy : public CardEffectStrategy {
public:
    void executeEffect() const override;
};

class RedeployTacticsEffectStrategy : public CardEffectStrategy {
public:
    void executeEffect() const override;
};

class DeserterTacticsEffectStrategy : public CardEffectStrategy {
public:
    void executeEffect() const override;
};

class TraitorTacticsEffectStrategy : public CardEffectStrategy {
public:
    void executeEffect() const override;
};
