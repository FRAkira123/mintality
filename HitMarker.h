#pragma once

std::vector<HitMarker> hitMarkers;

class hitmarker
{	
	class player_hurt_listener : public GameEventListener2
	{
	public:
		void start()
		{
			if (!pGameEventManager2->AddListener(this, "player_hurt", false))
				throw std::exception("Failed to register the event");
			
		}
		void stop()
		{
			pGameEventManager2->RemoveListener(this);
		}
		void FireGameEvent(IGameEvent *event) override
		{
			hitmarker::singleton()->on_fire_event(event);
		}
		int GetEventDebugID(void) override
		{
			return 0x2A;
		}

		void paint(void)
		{
			static int width = 0, 
				       height = 0;
			float alpha = 0.f;

			pEngine->GetScreenSize(width, height);

			if (Vars.VisualMenu.InfoDamge == true)
			{
				for (size_t i = 0; i < hitMarkers.size(); i++)
				{
					float diff = hitMarkers[i].expTime - pGlobals->curtime;

					if (diff < 0.f)
					{
						hitMarkers.erase(hitMarkers.begin() + i);
						continue;
					}

					int dist = 25;

					float ratio = 2.f - (diff / 0.8f);
					alpha = (diff / 0.8f) * 2.f;

					CDrawing::GetInstance()->Draw_String(width / 2 + 6 + ratio * dist / 2, height / 2 + 6 - ratio * dist, Color(255.f, 0.f, 0.f, 255.f), DT_CENTER, u8"%s", std::to_string(hitMarkers[i].dmg).c_str());

				}

			}

			if (hitMarkers.size() > 0 && Vars.VisualMenu.HitMarks == true)
			{
				for (size_t i = 0; i < hitMarkers.size(); i++)
				{

					float diff = hitMarkers[i].expTime - pGlobals->curtime;

					if (diff < 0.f)
					{
						hitMarkers.erase(hitMarkers.begin() + i);
						continue;
					}

					alpha = (diff / 0.8f) * 2.f;

				}

				int lineSize = 12;

				CDrawing::GetInstance()->Draw_Line(width / 2 + lineSize / 2, height / 2 - lineSize / 2, width / 2 - lineSize / 2, height / 2 + lineSize / 2, Color(255.f, 255.f, 255.f, ((float)(alpha * 255))));
				CDrawing::GetInstance()->Draw_Line(width / 2 - lineSize / 2, height / 2 - lineSize / 2, width / 2 + lineSize / 2, height / 2 + lineSize / 2, Color(255.f, 255.f, 255.f, ((float)(alpha * 255))));

			}

		}

	private :
	

	};

public:
	static hitmarker* singleton()
	{
		static hitmarker* instance = new hitmarker;
		return instance;
	}

	void initialize(void)
	{
		_listener.start();
		
	}
	void Paint(void)
	{
		_listener.paint();
	}

	void on_fire_event(IGameEvent* event)
	{
		if (!strcmp(event->GetName(), "player_hurt"))
		{
			int attacker = event->GetInt("attacker");
			if (pEngine->GetPlayerForUserID(attacker) == pEngine->GetLocalPlayer())
			{

				hitMarkers.push_back({ pGlobals->curtime + 0.8f, event->GetInt(XorStr("dmg_health")) });
				_flHurtTime = pGlobals->curtime;
			}
		}
	}

private:
	player_hurt_listener    _listener;
	float                   _flHurtTime;
	
};


