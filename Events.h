#pragma once
struct HitMarker
{
	float expTime;
	int dmg;
};

class PlayerHurtEvent : public GameEventListener2
{
public:

	void FireGameEvent(GameEvent *gEvent);
	int GetEventDebugID(void);

	void registerSelf(void);
	void unregisterSelf(void);

	void paint(void);

private:

	std::vector<HitMarker> hitMarkers;
};

PlayerHurtEvent *playerHurtEvent = nullptr;

void PlayerHurtEvent::FireGameEvent(GameEvent *gEvent)
{
	if (!gEvent)
		return;

	if (pEngine->GetPlayerForUserID(gEvent->getInt(XorStr("attacker"))) == pEngine->GetLocalPlayer())
		hitMarkers.push_back({pGlobals->curtime + 0.8f, gEvent->getInt(XorStr("dmg_health"))});

}

int PlayerHurtEvent::GetEventDebugID(void)
{
	return EVENT_DEBUG_ID_INIT;
}

void PlayerHurtEvent::registerSelf(void)
{

	pGameEventManager2->AddListener(this, XorStr("player_hurt"), false);

}

void PlayerHurtEvent::unregisterSelf(void)
{
	pGameEventManager2->RemoveListener(this);
}

