#pragma once
class Renderer
{
public:

	void BeginScene();
	void DrawScene();
	void EndScene();

	static Renderer* GetInstance();

public:
	Renderer::Renderer(){}
	Renderer::~Renderer(){}


	void  DrawString(float x, float y, ImVec4 clr, const char* format, ...){
		if (!format)
			return;
	
		float fontSize = 0.f;
		bool centeredX = true, 
			 centeredY = true,
			 outline = true;

		static const auto MAX_BUFFER_SIZE = 1024;
		static char buffer[MAX_BUFFER_SIZE] = "";

		ImGuiIO& io = ImGui::GetIO();

		auto font = io.Fonts->Fonts[0];
		ImGui::GetWindowDrawList()->PushTextureID(io.Fonts->TexID);

		va_list va;
		va_start(va, format);
		vsnprintf_s(buffer, MAX_BUFFER_SIZE, format, va);
		va_end(va);

		float fSize = fontSize == 0 ? font->FontSize : fontSize;

		if (centeredX || centeredY)
		{
			auto text_size = font->CalcTextSizeA(fSize, FLT_MAX, 0.0f, buffer);
			if (centeredX)
				x -= text_size.x / 2;
			if (centeredY)
				y -= text_size.y / 2;
		}

		if (outline)
		{
			int w = 1;
			ImGui::GetWindowDrawList()->AddText(font, fSize, ImVec2{ x - w, y - w }, 0xFF000000, buffer);
			ImGui::GetWindowDrawList()->AddText(font, fSize, ImVec2{ x + w, y }, 0xFF000000, buffer);
			ImGui::GetWindowDrawList()->AddText(font, fSize, ImVec2{ x    , y + w }, 0xFF000000, buffer);
			ImGui::GetWindowDrawList()->AddText(font, fSize, ImVec2{ x - w, y }, 0xFF000000, buffer);
		}

		ImGui::GetWindowDrawList()->AddText(font, fSize, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(clr), buffer);
		ImGui::GetWindowDrawList()->PopTextureID();
	}

	void DrawLine(const ImVec2& from, const ImVec2& to, ImVec4 color, float thickness = 1.f){
		ImGui::GetWindowDrawList()->AddLine(from, to, ImGui::ColorConvertFloat4ToU32(color), thickness);
	}

	void DrawCircle(const ImVec2& position, float radius, ImVec4 color){
		ImGui::GetWindowDrawList()->AddCircle(position, radius, ImGui::ColorConvertFloat4ToU32(color), 12);
	}

	void DrawRect(const ImVec2& position, const ImVec2& size, ImVec4 color){
		ImGui::GetWindowDrawList()->AddRect(position, size, ImGui::ColorConvertFloat4ToU32(color));
	}

	void DrawCircleFilled(const ImVec2& position, float radius, ImVec4 color){
		ImGui::GetWindowDrawList()->AddCircleFilled(position, radius, ImGui::ColorConvertFloat4ToU32(color), 12);
	}

	void DrawRectFilled(const ImVec2& position, const ImVec2& size, ImVec4 color){
	ImGui::GetWindowDrawList()->AddRectFilled(position, size, ImGui::ColorConvertFloat4ToU32(color));
	}



#define BONE_USED_BY_HITBOX			0x00000100
	void DrawSkeleton(IClientEntity* pEntity, ImVec4 color)
	{
		auto pStudioModel = pModelInfo->GetStudioModel(pEntity->GetModel());
		
		if (!pStudioModel)
			return;

		static matrix3x4_t pBoneToWorldOut[128];
		if (pEntity->SetupBones(pBoneToWorldOut, 128, 256, 0)) {

			for (int i = 0; i < pStudioModel->numbones; i++) {

				auto pBone = pStudioModel->pBone(i);
				if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
					continue;

				Vector vBonePos1 = {0, 0, 0};
				if (!WorldToScreen(Vector(pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3]), vBonePos1))
					continue;

				Vector vBonePos2 = { 0, 0, 0 };
				if (!WorldToScreen(Vector(pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3]), vBonePos2))
					continue;

				DrawLine(ImVec2(vBonePos1.X, vBonePos1.Y), ImVec2(vBonePos2.X, vBonePos2.Y), color);
			}
		}
	}


	void BulletTrace(IClientEntity* entity, ImVec4 color, float BulletTraceLength)
	{
		Vector src3D, dst3D, forward, src, dst;
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;

		AngleVectors(entity->GetEyeAngles(), &forward);
		filter.pSkip = entity;
		src3D = entity->GetBonePosition(8) - Vector(0, 0, 0);
		dst3D = src3D + (forward * BulletTraceLength);

		ray.Init(src3D, dst3D);

		pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

		if (!WorldToScreen(src3D, src) || !WorldToScreen(tr.endpos, dst))
			return;

		Renderer::GetInstance()->DrawLine(ImVec2(src.X, src.Y), ImVec2(dst.X, dst.Y), color, 1);
	}

	Vector GetHitboxPosition(IClientEntity* pEntity, int Hitbox)
	{
		matrix3x4_t matrix[128];
		if (!pEntity->SetupBones(matrix, 128, BONE_USED_BY_HITBOX, pEngine->GetLastTimeStamp()))
			return Vector(0, 0, 0);

		auto pModel = pEntity->GetModel();

		if (!pModel)
			return Vector(0, 0, 0);

		auto pStudioHdr = pModelInfo->GetStudioModel(pModel);

		if (!pStudioHdr)
			return Vector(0, 0, 0);

		auto pHitboxSet = pStudioHdr->pHitboxSet(pEntity->GetHitboxSet());

		auto hitbox = pHitboxSet->pHitbox(Hitbox);

		if (!hitbox)
			return Vector(0, 0, 0);

		Vector vMin = { 0,0,0 }, vMax = { 0,0,0 }, vCenter = { 0,0,0 }, sCenter = { 0,0,0 };
		VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
		VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
		vCenter = (vMin + vMax) *0.5f;
		return vCenter;
	}

	inline float FASTSQRT(float x)
	{
		unsigned int i = *(unsigned int*)&x;

		i += 127 << 23;
		i >>= 1;
		return *(float*)&i;
	}

	float Distance(Vector VecA, Vector VecB)
	{
		//return sqrt(((VecA.X - VecB.X) * (VecA.X - VecB.X)) +
		//	((VecA.Y - VecB.Y) * (VecA.Y - VecB.Y)) +
		//	((VecA.Z - VecB.Z) * (VecA.Z - VecB.Z)));


		return FASTSQRT(pow(VecA.X - VecB.X, 2) + pow(VecA.Y - VecB.Y, 2) + pow(VecA.Z - VecB.Z, 2));
	}

	static Renderer* m_pInstance;


private:

	static wchar_t *To_Unicode(const char*utf8_string)
	{
		int err;
		wchar_t * res;
		int res_len = MultiByteToWideChar(CP_UTF8, 0, utf8_string, -1, NULL, 0);
		if (res_len == 0)
			return NULL;

		res = (wchar_t *)calloc(sizeof(wchar_t), res_len);
		if (res == NULL)
			return NULL;

		err = MultiByteToWideChar(CP_UTF8, 0, utf8_string, -1, res, res_len);
		if (err == 0)
		{
			free(res);
			return NULL;
		}
		return res;
	}

};

Renderer* Renderer::m_pInstance;

void Renderer::BeginScene()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::Begin(XorStr("bb"), reinterpret_cast<bool*>(true), ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiSetCond_Always);
	ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiSetCond_Always);
}



ImVec4 BoxColorVisible = ImVec4(21.f / 255.f, 194.f / 255.f, 60.f / 255.f, 255.f / 255.f);
ImVec4 BoxColorInVisible = ImVec4(189.f / 255.f, 7.f / 255.f, 26.f / 255.f, 255.f / 255.f);

ImVec4 LineColorVisible = ImVec4(21.f / 255.f, 194.f / 255.f, 60.f / 255.f, 255.f / 255.f);
ImVec4 LineColorInVisible = ImVec4(189.f / 255.f, 7.f / 255.f, 26.f / 255.f, 255.f / 255.f);

ImVec4 D3BoxColorVisible = ImVec4(21.f / 255.f, 194.f / 255.f, 60.f / 255.f, 255.f / 255.f);
ImVec4 D3BoxColorInVisible = ImVec4(189.f / 255.f, 7.f / 255.f, 26.f / 255.f, 255.f / 255.f);

ImVec4 SkeletColorVisible = ImVec4(21.f / 255.f, 194.f / 255.f, 60.f / 255.f, 255.f / 255.f);
ImVec4 SkeletColorInVisible = ImVec4(189.f / 255.f, 7.f / 255.f, 26.f / 255.f, 255.f / 255.f);

ImVec4 HitBoxColorVisible = ImVec4(21.f / 255.f, 194.f / 255.f, 60.f / 255.f, 255.f / 255.f);
ImVec4 HitBoxColorInVisible = ImVec4(189.f / 255.f, 7.f / 255.f, 26.f / 255.f, 255.f / 255.f);

ImVec4 CircleColorVisible = ImVec4(21.f / 255.f, 194.f / 255.f, 60.f / 255.f, 255.f / 255.f);
ImVec4 CircleColorInVisible = ImVec4(189.f / 255.f, 7.f / 255.f, 26.f / 255.f, 255.f / 255.f);


ImVec4 InWeaponColorVisible = ImVec4(21.f / 255.f, 194.f / 255.f, 60.f / 255.f, 255.f / 255.f);

ImVec4 WeaponColorVisible = ImVec4(21.f / 255.f, 194.f / 255.f, 60.f / 255.f, 255.f / 255.f);
ImVec4 WeaponColorText = ImVec4(189.f / 255.f, 7.f / 255.f, 26.f / 255.f, 255.f / 255.f);


extern Variables  Vars;
bool IsOwner = false;


void PlayerHurtEvent::paint(void)
{
	static int width = 0, height = 0;
	pEngine->GetScreenSize(width, height);

	float alpha = 0.f;

	if (Vars.VisualMenu.InfoDamge )
	{
		for (size_t i = 0; i < hitMarkers.size(); i++)
		{

			float diff = hitMarkers[i].expTime - pGlobals->curtime;

			if (diff < 0.f)
			{
				hitMarkers.erase(hitMarkers.begin() + i);
				continue;
			}

			int dist = 30;

			float ratio = 2.f - (diff / 0.8f);
			alpha = (diff / 0.8f) * 2.f;

			Renderer::GetInstance()->DrawString(width / 2 + 6 + ratio * dist / 2, height / 2 + 6 - ratio * dist, ImVec4(255.f / 255.f, 0.f / 255.f, 0.f / 255.f, 255.f / 255.f), u8"%s" , std::to_string(hitMarkers[i].dmg).c_str());

		}

	}

	if (hitMarkers.size() > 0 && Vars.VisualMenu.HitMarks )
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

		Renderer::GetInstance()->DrawLine(ImVec2(width / 2 + lineSize / 2, height / 2 - lineSize / 2), ImVec2(width / 2 - lineSize / 2, height / 2 + lineSize / 2), ImVec4(255.f / 255.f, 255 / 255.f, 255 / 255.f, ((float)(alpha * 255)) / 255.f), 1);
		Renderer::GetInstance()->DrawLine(ImVec2(width / 2 - lineSize / 2, height / 2 - lineSize / 2), ImVec2(width / 2 + lineSize / 2, height / 2 + lineSize / 2), ImVec4(255.f / 255.f, 255 / 255.f, 255 / 255.f, ((float)(alpha * 255)) / 255.f), 1);

	}

}


void DrawWeapon(IClientEntity* pEntity, ClientClass* clientclass)
{
	const matrix3x4_t& trans = *(matrix3x4_t*)((DWORD)pEntity + (DWORD)DynNetVars::m_rgflCoordinateFrame);

	Vector min = *(Vector*)((DWORD)pEntity + (DWORD)Engine::Dynamic::Entity::m_Collision + (DWORD)Engine::Dynamic::Entity::m_vecMins);
	Vector max = *(Vector*)((DWORD)pEntity + (DWORD)Engine::Dynamic::Entity::m_Collision + (DWORD)Engine::Dynamic::Entity::m_vecMaxs);


	Vector pointList[] =
	{
		Vector(min.X, min.Y, min.Z),
		Vector(min.X, max.Y, min.Z),
		Vector(max.X, max.Y, min.Z),
		Vector(max.X, min.Y, min.Z),
		Vector(max.X, max.Y, max.Z),
		Vector(min.X, max.Y, max.Z),
		Vector(min.X, min.Y, max.Z),
		Vector(max.X, min.Y, max.Z)
	};

	Vector transformed[8];

	for (auto i = 0; i < 8; ++i)
		VectorTransform(pointList[i], trans, transformed[i]);

	Vector flb, brt, blb, frt, frb, brb, blt, flt;

	if (!WorldToScreen(transformed[3], flb) || !WorldToScreen(transformed[5], brt)
		|| !WorldToScreen(transformed[0], blb) || !WorldToScreen(transformed[4], frt)
		|| !WorldToScreen(transformed[2], frb) || !WorldToScreen(transformed[1], brb)
		|| !WorldToScreen(transformed[6], blt) || !WorldToScreen(transformed[7], flt))
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	auto left = flb.X;
	auto top = flb.Y;
	auto right = flb.X;
	auto bottom = flb.Y;

	for (int i = 0; i < 8; ++i)
	{
		if (left > arr[i].X)
			left = arr[i].X;
		if (top < arr[i].Y)
			top = arr[i].Y;
		if (right < arr[i].X)
			right = arr[i].X;
		if (bottom > arr[i].Y)
			bottom = arr[i].Y;
	}


	auto x = left;
	auto y = bottom;

	auto w = right - left;
	auto h = top - bottom;

	int edges[12][2] =
	{
		{ 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },
		{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 },
		{ 0, 6 },{ 1, 5 },{ 2, 4 },{ 3, 7 },
	};


	if (strstr(clientclass->m_pName, XorStr("BaseWeaponWorldModel")))
		return;


	if (strstr(clientclass->m_pName, XorStr("Planted")) && Vars.VisualMenu.BombTimer )
		Renderer::GetInstance()->DrawString(left, bottom, ImVec4(255.f / 255.f, 10.f / 255.f, 10.f / 255.f, 255.f / 255.f), "BOMB TIMER : %.1f", pEntity->GetBombTimer());
	

	auto owner = pEntity->GetOwnerHandle();

	if (owner == -1)
	{
		if (strstr(clientclass->m_pName, XorStr("Weapon"))
			|| strstr(clientclass->m_pName, XorStr("AK47"))
			|| strstr(clientclass->m_pName, XorStr("DEagle"))
			|| strstr(clientclass->m_pName, XorStr("Grenade"))
			|| strstr(clientclass->m_pName, XorStr("Planted"))
			|| strstr(clientclass->m_pName, XorStr("C4")))
		{

			if (Vars.VisualMenu.DropWeapon )
			{
				if (Vars.VisualMenu.Weapon2DBox )
				{
					Renderer::GetInstance()->DrawRect(ImVec2(left - 1.f, top - 1.f), ImVec2(right + 1.f, bottom + 1.f), ImVec4(00, 00, 00, 1));
					Renderer::GetInstance()->DrawRect(ImVec2(left, top), ImVec2(right, bottom), WeaponColorVisible);
					Renderer::GetInstance()->DrawRect(ImVec2(left + 1.f, top + 1.f), ImVec2(right - 1.f, bottom - 1.f), ImVec4(00, 00, 00, 1));

				}
				if (Vars.VisualMenu.Weapon3DBox )
				{
					for (auto it : edges)
					{
						Vector p1 = { 0 , 0 , 0 }, 
							p2 = { 0 , 0 , 0 };
						if (WorldToScreen(transformed[it[0]], p1) && WorldToScreen(transformed[it[1]], p2))
							Renderer::GetInstance()->DrawLine(ImVec2(p1.X, p1.Y), ImVec2(p2.X, p2.Y), WeaponColorVisible);
					}

				}
			}

		}
	}






	
}


void DrawPlayer(IClientEntity* pLocalEntity,IClientEntity* pEntity , ClientClass* clientclass, player_info_t pi, int WScreen, int HScreen)
{
	const matrix3x4_t& trans = *(matrix3x4_t*)((DWORD)pEntity + (DWORD)DynNetVars::m_rgflCoordinateFrame);

	Vector min = *(Vector*)((DWORD)pEntity + (DWORD)Engine::Dynamic::Entity::m_Collision + (DWORD)Engine::Dynamic::Entity::m_vecMins);
	Vector max = *(Vector*)((DWORD)pEntity + (DWORD)Engine::Dynamic::Entity::m_Collision + (DWORD)Engine::Dynamic::Entity::m_vecMaxs);


	auto vHead = Renderer::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Head),
		vLeg = pEntity->GetOrigin();

	Vector vScreenLeg = { 0, 0, 0 },	
		   vScreenHead = { 0, 0, 0 };


	Vector pointList[] =
	{
		Vector(min.X, min.Y, min.Z),
		Vector(min.X, max.Y, min.Z),
		Vector(max.X, max.Y, min.Z),
		Vector(max.X, min.Y, min.Z),
		Vector(max.X, max.Y, max.Z),
		Vector(min.X, max.Y, max.Z),
		Vector(min.X, min.Y, max.Z),
		Vector(max.X, min.Y, max.Z)
	};

	Vector transformed[8];

	for (int i = 0; i < 8; ++i)
		VectorTransform(pointList[i], trans, transformed[i]);

	Vector flb = { 0, 0, 0 } , 
		   brt = { 0, 0, 0 },
		   blb = { 0, 0, 0 }, 
		   frt = { 0, 0, 0 },
		   frb = { 0, 0, 0 },
		   brb = { 0, 0, 0 }, 
		   blt = { 0, 0, 0 }, 
		   flt = { 0, 0, 0 };

	if (!WorldToScreen(transformed[3], flb) || !WorldToScreen(transformed[5], brt)
		|| !WorldToScreen(transformed[0], blb) || !WorldToScreen(transformed[4], frt)
		|| !WorldToScreen(transformed[2], frb) || !WorldToScreen(transformed[1], brb)
		|| !WorldToScreen(transformed[6], blt) || !WorldToScreen(transformed[7], flt)
		|| !WorldToScreen(vLeg, vScreenLeg) || !WorldToScreen(vHead, vScreenHead))
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	auto left = flb.X;
	auto top = flb.Y;
	auto right = flb.X;
	auto bottom = flb.Y;

	for (int i = 0; i < 8; ++i)
	{
		if (left > arr[i].X)
			left = arr[i].X;
		if (top < arr[i].Y)
			top = arr[i].Y;
		if (right < arr[i].X)
			right = arr[i].X;
		if (bottom > arr[i].Y)
			bottom = arr[i].Y;
	}

	auto x = left;
	auto y = bottom;

	auto w = right - left;
	auto h = top - bottom;


	int edges[12][2] =
		{
			{ 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },
			{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 },
			{ 0, 6 },{ 1, 5 },{ 2, 4 },{ 3, 7 },
		};

		if (strstr(clientclass->m_pName, XorStr("CCSPlayer")) && (pEntity->IsValid() ))
		{
			if (pEntity->GetTeamNum() != pLocalEntity->GetTeamNum())
			{

				UINT  fHealth = pEntity->GetHealth();
				UINT  fArmor = pEntity->GetArmor();

				FLOAT  Dist = Renderer::GetInstance()->Distance(pLocalEntity->GetOrigin(), pEntity->GetOrigin());

				auto* Weapon = pEntity->GetWeapon();

				if (Weapon == nullptr)
					return;

				const char* pszName = Weapon->GetName();

				if (!pszName)
					return;

				std::string name(pszName);

				name = name.substr(name.find("_") + 1, name.length());
				name = name.substr(name.find("_") + 1, name.length());


				if (Vars.VisualMenu.Player2DBox)
				{
					Renderer::GetInstance()->DrawRect(ImVec2(left - 1.f, top - 1.f), ImVec2(right + 1.f, bottom + 1.f), ImVec4(00, 00, 00, 1));

					Renderer::GetInstance()->DrawRect(ImVec2(left, top), ImVec2(right, bottom), WeaponColorVisible);

					Renderer::GetInstance()->DrawRect(ImVec2(left + 1.f, top + 1.f), ImVec2(right - 1.f, bottom - 1.f), ImVec4(00, 00, 00, 1));

				}


				if (Vars.VisualMenu.Player3DBox)
				{
					for (auto it : edges)
					{
						Vector p1 = { 0 , 0 , 0 },
							p2 = { 0 , 0 , 0 };
						if (WorldToScreen(transformed[it[0]], p1) && WorldToScreen(transformed[it[1]], p2))
							Renderer::GetInstance()->DrawLine(ImVec2(p1.X, p1.Y), ImVec2(p2.X, p2.Y), WeaponColorVisible);
					}
				}
			

				if (Vars.VisualMenu.ESPSkelet)
					Renderer::GetInstance()->DrawSkeleton(pEntity, SkeletColorInVisible);

				if (Vars.VisualMenu.ESPLine )
					Renderer::GetInstance()->DrawLine(ImVec2(WScreen / 2, HScreen), ImVec2(vScreenHead.X, vScreenHead.Y), LineColorInVisible, 1);

				if (Vars.VisualMenu.Head )
					Renderer::GetInstance()->DrawCircle(ImVec2(vScreenHead.X, vScreenHead.Y), 5.0f, CircleColorInVisible);

				if (Vars.VisualMenu.ESPNickName )
					Renderer::GetInstance()->DrawString(left - 30, bottom + 10, ImVec4(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 255.f / 255.f), u8"%s", pi.szName);

				if (Vars.VisualMenu.HealthDraw )
					Renderer::GetInstance()->DrawString(left - 30, bottom + (11 * 2), ImVec4(255.f / 255.f, 0.f / 255.f, 0.f / 255.f, 255.f / 255.f), "Health : %d", fHealth);

				if (Vars.VisualMenu.ArmorDraw)
					Renderer::GetInstance()->DrawString(left - 30, bottom + (11 * 3), ImVec4(0.f / 255.f, 122.f / 255.f, 204.f / 255.f, 255.f / 255.f), "Armor : %d", fArmor);

				if (Vars.VisualMenu.ESPDistance)
					Renderer::GetInstance()->DrawString(left - 30, bottom + (11 * 4), ImVec4(255.f / 255.f, 122.f / 255.f, 0 / 255.f, 255.f / 255.f), u8"Distance : %.f M", Dist / 100);

				if (Vars.VisualMenu.ESPWeapon)
					Renderer::GetInstance()->DrawString(left - 30, bottom + (11 * 5), ImVec4(255.f / 255.f, 122.f / 255.f, 204.f / 255.f, 255.f / 255.f), "%s", name.c_str());
			
				if (Vars.VisualMenu.ESPLastPlace)
					Renderer::GetInstance()->DrawString(left - 30, bottom + (11 * 6), ImVec4(255.f / 255.f, 122.f / 255.f, 0 / 255.f, 255.f / 255.f), "%s", pEntity->GetLastPlace());			
						
				if (Vars.VisualMenu.ShowPitch)
					Renderer::GetInstance()->DrawString(left - 30, bottom + (11 * 7), ImVec4(240.f / 255.f, 240.f / 255.f, 255.f / 255.f, 255.f / 255.f), u8"Pitch: %.1f", pEntity->GetEyeAngles().X);

				if (Vars.VisualMenu.ShowYaw)
					Renderer::GetInstance()->DrawString(left - 30, bottom + (11 * 8), ImVec4(240.f / 255.f, 240.f / 255.f, 255.f / 255.f, 255.f / 255.f), u8"Yaw: %.1f", pEntity->GetEyeAngles().Y);

				if (Vars.VisualMenu.IsFlashed && pEntity->IsFlashed())
					Renderer::GetInstance()->DrawString(left - 30, bottom + (11 * 9), ImVec4(240.f / 255.f, 240.f / 255.f, 0 / 255.f, 255.f / 255.f), XorStr(u8"Ослеплен"));
				
				if (Vars.VisualMenu.BulletTrace)
					Renderer::GetInstance()->BulletTrace(pEntity, ImVec4(240.f / 255.f, 0 / 255.f, 0 / 255.f, 255.f / 255.f), Vars.VisualMenu.BulletTraceLength);
			}

		}


}




void Renderer::DrawScene()
{

	Renderer::GetInstance()->DrawString(40, 15, ImVec4(255.f / 255.f, 0 / 255.f, 0 / 255.f, 255 / 255.f), XorStr("XVII Project"));

	if (pEngine->IsTakingScreenshot() || pEngine->IsInGame() == false)
		return;

	int WScreen = 0, HScreen = 0;
	pEngine->GetScreenSize(WScreen, HScreen);

	auto pLocalEntity = pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());

	if (pLocalEntity->IsValid() == false)
		return;

	for (int i = 0; i <= pClientEntList->GetHighestEntityIndex(); i++)
	{
		auto pEntity = pClientEntList->GetClientEntity(i);

		if (!pEntity)
			continue;

		auto cClass = pEntity->GetClientClass();

		if (!cClass)
			continue;

		DrawWeapon(pEntity, cClass);

	//	playerHurtEvent->paint();

		if (pEntity == pLocalEntity)
			continue;			

		player_info_t pi;

		if (pEngine->GetPlayerInfo(i, &pi) == false)
			continue;

		DrawPlayer(pLocalEntity,pEntity, cClass, pi, WScreen, HScreen);


	}


}



void Renderer::EndScene()
{
	ImGui::GetCurrentWindow()->DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
}

Renderer* Renderer::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new Renderer();

	return m_pInstance;
}




#define MAKE_IMU32(r, g, b, a) ((a << 24) + (b << 16) + (g << 8) + r) 


void showRadarHack()
{
	ImGui::Begin(XorStr("Radar"), &Vars.m_radarIsActive, ImVec2(200, 200), 0.6f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);


	ImVec2 bgPos = ImGui::GetCursorScreenPos();
	ImVec2 bgSize = ImGui::GetContentRegionAvail();

	ImGui::GetWindowDrawList()->AddRectFilled(bgPos, ImVec2(bgPos.x + bgSize.x, bgPos.y + bgSize.y), 0xFF333333);


	auto localPlayer = static_cast<IClientEntity*>(pClientEntList->GetClientEntity(pEngine->GetLocalPlayer()));

	if (!localPlayer)
	{
		ImGui::End();
		return;
	}


	Vector pos = { 0, 0, 0 };
	float x = 0, y = 0;
	ImVec2 midRadar = ImVec2(bgPos.x + (bgSize.x / 2), bgPos.y + (bgSize.y / 2));
	float mapSizeX = -5000;
	float mapSizeY = 5000;
	ImGui::GetWindowDrawList()->AddLine(ImVec2(midRadar.x - bgSize.x / 2.f, midRadar.y), ImVec2(midRadar.x + bgSize.x / 2.f, midRadar.y), MAKE_IMU32(0, 0, 0, 64));
	ImGui::GetWindowDrawList()->AddLine(ImVec2(midRadar.x, midRadar.y - bgSize.y / 2.f), ImVec2(midRadar.x, midRadar.y + bgSize.y / 2.f), MAKE_IMU32(0, 0, 0, 64));


	pos = localPlayer->GetOrigin();
	x = midRadar.x;
	y = midRadar.y;
	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x - 2, y - 2), ImVec2(x + 2, y + 2), 0xFFFFFFFF);

	// Show local camera
	bool radarViewFixed = true;
	ImVec2 camPos = ImVec2(0, 0);
	Vector forward = { 0, 0, 0 };

	angleToForwardVector(Global::MyViewAng, forward);

	forward = forward * 1000;

	if (radarViewFixed)
		camPos = ImVec2(midRadar.x, 0);
	else
		camPos = ImVec2(x - forward.X, y + forward.Y);

	float fov = DEG2RAD(90.f); // @todo: get fov
	rotateVector(camPos.x, camPos.y, fov / 2.f, x, y);
	ImGui::GetWindowDrawList()->AddLine(ImVec2(x, y), camPos, MAKE_IMU32(199, 202, 74, 255));
	rotateVector(camPos.x, camPos.y, -fov, x, y);
	ImGui::GetWindowDrawList()->AddLine(ImVec2(x, y), camPos, MAKE_IMU32(199, 202, 74, 255));

	ImU32 color = MAKE_IMU32(0, 0, 255, 255);

	for (int i = 0; i < pGlobals->maxClients; i++)
	{

		IClientEntity* pEntity = pClientEntList->GetClientEntity(i);

		if (pEntity == nullptr
			|| !pEntity->IsPlayer()
			|| pEntity->GetHealth() <= 0)
			continue;

		if (pEntity->GetTeamNum() != localPlayer->GetTeamNum())
		{
			color = MAKE_IMU32(255, 0, 0, 255);
			pos = pEntity->GetOrigin();
			pos = pos - localPlayer->GetOrigin();

			x = midRadar.x + (pos.X / mapSizeX) * bgSize.x;
			y = midRadar.y + (pos.Y / mapSizeY) * bgSize.y;

			if (radarViewFixed)
				rotateVector(x, y, DEG2RAD((Global::MyViewAng.Y + 90)), midRadar.x, midRadar.y);


			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x - 2, y - 2), ImVec2(x + 2, y + 2), color);
		}
	}

	ImGui::End();
}



