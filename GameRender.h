#pragma once
class CDrawing
{
public:

	CDrawing::CDrawing() {}
	CDrawing::~CDrawing() {}

	static CDrawing* m_pInstance;
	static CDrawing* GetInstance();

	void Draw_String(FLOAT x, FLOAT y, Color color, DWORD dwAlign, const char *fmt, ...)
	{
		if (!fmt)
			return;

		char    buff[256] = { '\0' };
		va_list vlist = nullptr;
		va_start(vlist, fmt);
		vsprintf_s(buff, fmt, vlist);
		va_end(vlist);
		wchar_t * szString = To_Unicode(buff);

		int wide = 0, tall = 0;
		if (dwAlign & DT_RIGHT)
		{
			pSurface->GetTextSize(espfont, szString, wide, tall);
			x -= wide;
		}
		if (dwAlign & DT_CENTER)
		{
			pSurface->GetTextSize(espfont, szString, wide, tall);
			x -= wide / 2.0;
		}

		pSurface->DrawSetTextPos(x, y);
		pSurface->DrawSetTextFont(espfont);
		pSurface->DrawSetTextColor(color.r(), color.g(), color.b(), color.a());
		pSurface->DrawPrintText(szString, wcslen(szString));
	}

	void Outlined_Rect(int x, int y, int w, int h, Color& color)
	{
		pSurface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
		pSurface->DrawOutlinedRect(x, y, x + w, y + h);
	}

	void Bordered_Box(int x, int y, int w, int h, Color color, Color out)
	{
		Outlined_Rect(x, y, w, h, color);
		Outlined_Rect(x - 1, y - 1, w + 2, h + 2, out);
		Outlined_Rect(x + 1, y + 1, w - 2, h - 2, out);
	}

	void Filled_Rect(int x, int y, int w, int h, Color colour)
	{
		pSurface->DrawSetColor(colour.r(), colour.g(), colour.b(), colour.a());
		pSurface->DrawFilledRect(x, y, x + w, y + h);
	}

	void Draw_Bar(int x, int y, float health, int w, int h, Color Draw)
	{
		x -= w / 2;
		y -= h / 2;
		Outlined_Rect(x, y, w, h + 1, Color(0, 0, 0, 255));
		UINT hw = (UINT)(((w - 2) * health) / 100);
		Filled_Rect(x + 1, y + 1, hw, h - 1, Draw);
	}

	void Draw_Outlined_Circle(int x, int y, int r, Color col)
	{
		pSurface->DrawSetColor(col.r(), col.g(), col.b(), col.a());
		pSurface->DrawOutlinedCircle(x, y, r, 15);
	}

	void Draw_Line(int x0, int y0, int x1, int y1, Color col)
	{
		pSurface->DrawSetColor(col.r(), col.g(), col.b(), col.a());
		pSurface->DrawLine(x0, y0, x1, y1);
	}

	Vector Get_Bone_Position(IClientEntity * pPlayer, int Bone)
	{
		matrix3x4_t MatrixArray[128];
		Vector Out = { 0, 0, 0 };
		if (!pPlayer->SetupBones(MatrixArray, 128, 0x00000100, pEngine->GetLastTimeStamp()))
			return Vector(0, 0, 0);

		matrix3x4_t HitboxMatrix = MatrixArray[Bone];
		Out = Vector(HitboxMatrix[0][3], HitboxMatrix[1][3], HitboxMatrix[2][3]);
		return Out;
	}


	void DrawPixel(int x, int y, Color col)
	{
		pSurface->DrawSetColor(col);
		pSurface->DrawFilledRect(x, y, x + 1, y + 1);
	}

	void DrawWave(Vector loc, float radius, Color color)
	{
		static float Step = M_PI * 3.0f / 50;
		Vector prev = { 0, 0, 0 };
		for (float lat = 0; lat <= M_PI * 4.0f; lat += Step)
		{
			float
				sin1 = sin(lat),
				cos1 = cos(lat),
				sin3 = sin(0.0),
				cos3 = cos(0.0);

			Vector point1 = { 0, 0, 0 };
			point1 = Vector(sin1 * cos3, cos1, sin1 * sin3) * radius;
			Vector point3 = loc;
			Vector Out = { 0, 0, 0 };
			point3 += point1;

			if (WorldToScreen(point3, Out))
			{
				if (lat > 0.000)
					Draw_Line(prev.X, prev.Y, Out.X, Out.Y, color);
			}
			prev = Out;
		}
	}

	void BulletTrace(IClientEntity* entity, Color color, float BulletTraceLength2)
	{

		Vector src3D, dst3D, forward, src, dst;
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;

		AngleVectors(entity->GetEyeAngles(), &forward);
		filter.pSkip = entity;
		src3D = entity->GetBonePosition(6) - Vector(0, 0, 0);
		dst3D = src3D + (forward * BulletTraceLength2);

		ray.Init(src3D, dst3D);

		pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

		if (!WorldToScreen(src3D, src) || !WorldToScreen(tr.endpos, dst))
			return;

		Draw_Line(src.X, src.Y, dst.X, dst.Y, color);
		Filled_Rect(dst.X - 3, dst.Y - 3, 5, 5, color);
	}

	void BoundingBoxPlayer(IClientEntity* pEntity, bool& Visible)
	{
		Vector vOrigin = pEntity->GetOrigin();

		Vector min = *(Vector*)((DWORD)pEntity + (DWORD)Engine::Dynamic::Entity::m_Collision + (DWORD)Engine::Dynamic::Entity::m_vecMins) + vOrigin;
		Vector max = *(Vector*)((DWORD)pEntity + (DWORD)Engine::Dynamic::Entity::m_Collision + (DWORD)Engine::Dynamic::Entity::m_vecMaxs) + vOrigin;

		Vector points[] =
		{
			Vector(min.X, min.Y, min.Z),
			Vector(min.X, max.Y, min.Z),
			Vector(max.X, max.Y, min.Z),
			Vector(max.X, min.Y, min.Z),
			Vector(min.X, min.Y, max.Z),
			Vector(min.X, max.Y, max.Z),
			Vector(max.X, max.Y, max.Z),
			Vector(max.X, min.Y, max.Z)
		};

		int edges[12][2] =
		{
			{ 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },
		{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 },
		{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 },
		};

		for (auto it : edges)
		{
			Vector p1, p2;
			if (WorldToScreen(points[it[0]], p1) && WorldToScreen(points[it[1]], p2))
			{
				Draw_Line(p1.X, p1.Y, p2.X, p2.Y, Visible == true ? Color(0, 255, 0, 255) : Color(255, 0, 0, 255));
			}
		}
	}



#define BONE_USED_BY_HITBOX			0x00000100

	void DrawSkeleton(IClientEntity* pEntity, Color color)
	{
		studiohdr_t* pStudioModel = pModelInfo->GetStudioModel(pEntity->GetModel());
		if (!pStudioModel)
			return;

		static matrix3x4_t pBoneToWorldOut[128];
		if (pEntity->SetupBones(pBoneToWorldOut, 128, 256, 0))
		{
			for (int i = 0; i < pStudioModel->numbones; i++)
			{
				mstudiobone_t* pBone = pStudioModel->pBone(i);

				if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
					continue;

				Vector vBonePos1 = { 0,0,0 };
				if (!WorldToScreen(Vector(pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3]), vBonePos1))
					continue;

				Vector vBonePos2 = { 0,0,0 };
				if (!WorldToScreen(Vector(pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3]), vBonePos2))
					continue;

				Draw_Line(vBonePos1.X, vBonePos1.Y, vBonePos2.X, vBonePos2.Y, color);
			}
		}
	}



	void Draw3DBox(Vector* boxVectors, Color color)
	{
		Vector boxVectors0 = { 0,0,0 }, boxVectors1 = { 0,0,0 }, boxVectors2 = { 0,0,0 }, boxVectors3 = { 0,0,0 },
			boxVectors4 = { 0,0,0 }, boxVectors5 = { 0,0,0 }, boxVectors6 = { 0,0,0 }, boxVectors7 = { 0,0,0 };


		if (WorldToScreen(boxVectors[0], boxVectors0) &&
			WorldToScreen(boxVectors[1], boxVectors1) &&
			WorldToScreen(boxVectors[2], boxVectors2) &&
			WorldToScreen(boxVectors[3], boxVectors3) &&
			WorldToScreen(boxVectors[4], boxVectors4) &&
			WorldToScreen(boxVectors[5], boxVectors5) &&
			WorldToScreen(boxVectors[6], boxVectors6) &&
			WorldToScreen(boxVectors[7], boxVectors7))
		{

			/*
			.+--5---+
			.8 4    6'|
			+--7---+'  11
			9   |  10  |
			|  ,+--|3--+
			|.0    | 2'
			+--1---+'
			*/

			Vector2D lines[12][2];
			//bottom of box
			lines[0][0] = { boxVectors0.X, boxVectors0.Y };
			lines[0][1] = { boxVectors1.X, boxVectors1.Y };
			lines[1][0] = { boxVectors1.X, boxVectors1.Y };
			lines[1][1] = { boxVectors2.X, boxVectors2.Y };
			lines[2][0] = { boxVectors2.X, boxVectors2.Y };
			lines[2][1] = { boxVectors3.X, boxVectors3.Y };
			lines[3][0] = { boxVectors3.X, boxVectors3.Y };
			lines[3][1] = { boxVectors0.X, boxVectors0.Y };

			lines[4][0] = { boxVectors0.X, boxVectors0.Y };
			lines[4][1] = { boxVectors6.X, boxVectors6.Y };

			// top of box
			lines[5][0] = { boxVectors6.X, boxVectors6.Y };
			lines[5][1] = { boxVectors5.X, boxVectors5.Y };
			lines[6][0] = { boxVectors5.X, boxVectors5.Y };
			lines[6][1] = { boxVectors4.X, boxVectors4.Y };
			lines[7][0] = { boxVectors4.X, boxVectors4.Y };
			lines[7][1] = { boxVectors7.X, boxVectors7.Y };
			lines[8][0] = { boxVectors7.X, boxVectors7.Y };
			lines[8][1] = { boxVectors6.X, boxVectors6.Y };


			lines[9][0] = { boxVectors5.X, boxVectors5.Y };
			lines[9][1] = { boxVectors1.X, boxVectors1.Y };

			lines[10][0] = { boxVectors4.X, boxVectors4.Y };
			lines[10][1] = { boxVectors2.X, boxVectors2.Y };

			lines[11][0] = { boxVectors7.X, boxVectors7.Y };
			lines[11][1] = { boxVectors3.X, boxVectors3.Y };

			for (int i = 0; i < 12; i++)
			{
				Draw_Line(lines[i][0].x, lines[i][0].y, lines[i][1].x, lines[i][1].y, color);
			}
		}
	}


	void Box3d(Vector* pointList, Color color)
	{
		Vector vStart, vEnd;

		for (int i = 0; i < 3; ++i)
		{
			if (WorldToScreen(pointList[i], vStart))
			{
				if (WorldToScreen(pointList[i + 1], vEnd))
					Draw_Line(vStart.X, vStart.Y, vEnd.X, vEnd.Y, color);
			}
		}

		if (WorldToScreen(pointList[0], vStart))
		{
			if (WorldToScreen(pointList[3], vEnd))
				Draw_Line(vStart.X, vStart.Y, vEnd.X, vEnd.Y, color);
		}

		for (int i = 4; i < 7; ++i)
		{
			if (WorldToScreen(pointList[i], vStart))
			{
				if (WorldToScreen(pointList[i + 1], vEnd))
					Draw_Line(vStart.X, vStart.Y, vEnd.X, vEnd.Y, color);
			}
		}

		if (WorldToScreen(pointList[4], vStart))
		{
			if (WorldToScreen(pointList[7], vEnd))
				Draw_Line(vStart.X, vStart.Y, vEnd.X, vEnd.Y, color);
		}

		if (WorldToScreen(pointList[0], vStart))
		{
			if (WorldToScreen(pointList[6], vEnd))
				Draw_Line(vStart.X, vStart.Y, vEnd.X, vEnd.Y, color);
		}

		if (WorldToScreen(pointList[1], vStart))
		{
			if (WorldToScreen(pointList[5], vEnd))
				Draw_Line(vStart.X, vStart.Y, vEnd.X, vEnd.Y, color);
		}

		if (WorldToScreen(pointList[2], vStart))
		{
			if (WorldToScreen(pointList[4], vEnd))
				Draw_Line(vStart.X, vStart.Y, vEnd.X, vEnd.Y, color);
		}

		if (WorldToScreen(pointList[3], vStart))
		{
			if (WorldToScreen(pointList[7], vEnd))
				Draw_Line(vStart.X, vStart.Y, vEnd.X, vEnd.Y, color);
		}
	}

	void Hitbox(IClientEntity* pEntity, int nHitbox, Color color)
	{
		model_t* pModel = pEntity->GetModel();

		if (!pModel)
			return;

		studiohdr_t* pStudioHdr = pModelInfo->GetStudioModel(pModel);

		if (!pStudioHdr)
			return;

		mstudiohitboxset_t* pHitboxSet = pStudioHdr->pHitboxSet(pEntity->GetHitboxSet());

		if (!pHitboxSet)
			return;

		mstudiobbox_t* pBox = pHitboxSet->pHitbox(nHitbox);

		if (!pBox)
			return;

		matrix3x4_t matrix[128];

		if (!pEntity->SetupBones(matrix, 128, BONE_USED_BY_HITBOX, pEngine->GetLastTimeStamp()))
			return;

		Vector min = pBox->bbmin;
		Vector max = pBox->bbmax;

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
			VectorTransform(pointList[i], matrix[pBox->bone], transformed[i]);

		Box3d(transformed, color);
	}

	void DrawHitBox(IClientEntity* pEntity, Color color)
	{
		model_t* pModel = pEntity->GetModel();

		if (!pModel)
			return;

		studiohdr_t* pStudioHdr = pModelInfo->GetStudioModel(pModel);

		if (!pStudioHdr)
			return;

		mstudiohitboxset_t* pHitboxSet = pStudioHdr->pHitboxSet(pEntity->GetHitboxSet());

		if (!pHitboxSet)
			return;

		for (int i = 0; i < pHitboxSet->numhitboxes; ++i)
			Hitbox(pEntity, i, color);
	}

	Vector GetHitboxPosition(IClientEntity* pEntity, int Hitbox)
	{
		matrix3x4_t matrix[128];
		if (!pEntity->SetupBones(matrix, 128, BONE_USED_BY_HITBOX, pEngine->GetLastTimeStamp()))
			return Vector(0, 0, 0);

		model_t* pModel = pEntity->GetModel();

		if (!pModel)
			return Vector(0, 0, 0);

		studiohdr_t* pStudioHdr = pModelInfo->GetStudioModel(pModel);

		if (!pStudioHdr)
			return Vector(0, 0, 0);

		mstudiohitboxset_t* pHitboxSet = pStudioHdr->pHitboxSet(pEntity->GetHitboxSet());

		if (!pHitboxSet)
			return Vector(0, 0, 0);

		mstudiobbox_t* hitbox = pHitboxSet->pHitbox(Hitbox);

		if (!hitbox)
			return Vector(0, 0, 0);

		Vector vMin = { 0,0,0 }, vMax = { 0,0,0 }, vCenter = { 0,0,0 }, sCenter = { 0,0,0 };
		VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
		VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
		vCenter = (vMin + vMax) *0.5f;
		return vCenter;
	}


	void Draw_Circle(Vector position, float points, float radius, Color color)
	{
		float step = (float)M_PI * 2.0f / points;

		std::vector<Vector> points3d;
		for (float a = 0; a < (M_PI * 2.0f); a += step)
		{
			Vector start(radius * cosf(a) + position.X, radius * sinf(a) + position.Y, position.Z);
			Vector end(radius * cosf(a + step) + position.X, radius * sinf(a + step) + position.Y, position.Z);

			Vector start2d, end2d;
			if (!WorldToScreen(start, start2d) || !WorldToScreen(end, end2d))
				return;

			Draw_Line(start2d.X, start2d.Y, end2d.X, end2d.Y, color);
		}
	}

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


CDrawing* CDrawing::m_pInstance;

CDrawing* CDrawing::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new CDrawing();

	return m_pInstance;
}


#include "HitMarker.h"
#include "SoundHook.h"



std::deque< Sound::clog > Sound::log;

void Sound::Add(clog player_log)
{
	log.push_back(player_log);
}

void Sound::Draw()
{
	Vector screen = { 0,0,0 };

	Color Color(255, 255, 255, 255);

	for (int log_id = 0; log_id < log.size(); log_id++)
	{
		if ((log[log_id].origin.IsZero()) || log_id > 10 || log[log_id].time < pGlobals->curtime)
			log.erase(log.begin() + log_id);

		CDrawing::GetInstance()->DrawWave(log[log_id].origin, 20.f, Color);
	}
}

void Draw_Weapon(IClientEntity* pEntity, ClientClass* clientclass)
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


	if (strstr(clientclass->m_pName, XorStr("Planted")) && Vars.VisualMenu.BombTimer)
	{
		CDrawing::GetInstance()->Filled_Rect(x - 60, y - 3, 160, 20, Color(0, 0, 0, 200));
		CDrawing::GetInstance()->Draw_String(x, y, Color(255.f, 10.f, 10.f, 255.f), DT_CENTER, XorStr(u8"Времени до взрыва : %.1f"), pEntity->GetBombTimer());
	}


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

			if (Vars.VisualMenu.DropWeapon)
			{
				if (Vars.VisualMenu.Weapon2DBox)
				{
					CDrawing::GetInstance()->Outlined_Rect(x - 1, y - 1, w + 2, h + 2, Color(00, 00, 00, 255));
					CDrawing::GetInstance()->Outlined_Rect(x, y, w, h, Color(255, 0, 0, 255));
					CDrawing::GetInstance()->Outlined_Rect(x + 1, y + 1, w - 2, h - 2, Color(0, 0, 0, 255));

				}
				if (Vars.VisualMenu.Weapon3DBox)
				{
					for (auto it : edges)
					{
						Vector p1 = { 0 , 0 , 0 },
							p2 = { 0 , 0 , 0 };
						if (WorldToScreen(transformed[it[0]], p1) && WorldToScreen(transformed[it[1]], p2))
							CDrawing::GetInstance()->Draw_Line(p1.X, p1.Y, p2.X, p2.Y, Color(255, 255, 54, 255));
					}

				}
			}

		}
	}


}

void SniperCrosshair(Color color)
{
	int screenW = 0,
		screenH = 0;
	pEngine->GetScreenSize(screenW, screenH);

	int crX = screenW / 2,
		crY = screenH / 2,
		dy = screenH / Vars.Misc.FOV,
		dx = screenW / Vars.Misc.FOV,
		drX = 0,
		drY = 0;

	drX = crX;
	drY = crY;

	CDrawing::GetInstance()->Draw_Line(drX - 5, drY, drX + 5, drY, Color::White());
	CDrawing::GetInstance()->Draw_Line(drX, drY - 5, drX, drY + 5, Color::White());
}


void Draw_Player(IClientEntity* pLocalEntity, IClientEntity* pEntity, ClientClass* clientclass, player_info_t pi, int WScreen, int HScreen)
{

	const matrix3x4_t& trans = *(matrix3x4_t*)((DWORD)pEntity + (DWORD)DynNetVars::m_rgflCoordinateFrame);

	Vector min = *(Vector*)((DWORD)pEntity + (DWORD)Engine::Dynamic::Entity::m_Collision + (DWORD)Engine::Dynamic::Entity::m_vecMins);
	Vector max = *(Vector*)((DWORD)pEntity + (DWORD)Engine::Dynamic::Entity::m_Collision + (DWORD)Engine::Dynamic::Entity::m_vecMaxs);


	auto vHead = CDrawing::GetInstance()->GetHitboxPosition(pEntity, (int)CSGOHitboxID::Head),
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

	Vector flb = { 0, 0, 0 },
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

	if (strstr(clientclass->m_pName, XorStr("CCSPlayer")) && (pEntity->IsValid()))
	{
		if (pEntity->GetTeamNum() != pLocalEntity->GetTeamNum())
		{
			JUNK_CODE_ONE

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
				CDrawing::GetInstance()->Outlined_Rect(x - 1, y - 1, w + 2, h + 2, Color(00, 00, 00, 255));
				CDrawing::GetInstance()->Outlined_Rect(x, y, w, h, Color(255, 0, 0, 255));
				CDrawing::GetInstance()->Outlined_Rect(x + 1, y + 1, w - 2, h - 2, Color(0, 0, 0, 255));
			}



			if (Vars.VisualMenu.Player2DBox2)
			{
				CDrawing::GetInstance()->Outlined_Rect(x - 1, y - 1, w + 2.5, h + 2.5, Color(255, 00, 00, 255));
				CDrawing::GetInstance()->Outlined_Rect(x, y, w, h, Color(255, 0, 0, 255));
				CDrawing::GetInstance()->Outlined_Rect(x + 1, y + 1, w - 2.5, h - 2.5, Color(255, 0, 0, 255));
			}



			if (Vars.VisualMenu.Player3DBox)
			{
				for (auto it : edges)
				{
					Vector p1 = { 0 , 0 , 0 },
						p2 = { 0 , 0 , 0 };
					if (WorldToScreen(transformed[it[0]], p1) && WorldToScreen(transformed[it[1]], p2))
						CDrawing::GetInstance()->Draw_Line(p1.X, p1.Y, p2.X, p2.Y, Color(255, 0, 0, 255));
				}
			}


			if (Vars.VisualMenu.ESPSkelet)
				CDrawing::GetInstance()->DrawSkeleton(pEntity, IsVisible(pEntity) ? Color(0, 255, 0, 255) : Color(255, 0, 0, 255));

			if (Vars.VisualMenu.ESPLine)
				CDrawing::GetInstance()->Draw_Line(WScreen / 2, HScreen, vScreenHead.X, vScreenHead.Y, Color(222, 65, 48, 255));

			if (Vars.VisualMenu.Head)
				CDrawing::GetInstance()->Draw_Outlined_Circle(vScreenHead.X, vScreenHead.Y, 5.0f, IsVisible(pEntity) ? Color(0, 255, 0, 255) : Color(255, 0, 0, 255));

			if (Vars.VisualMenu.ESPNickName)
				CDrawing::GetInstance()->Draw_String(x - 30, y + 10, Color(255, 255, 255, 255), DT_CENTER, XorStr("%s"), pi.szName);

			if (Vars.VisualMenu.HealthDraw)
				CDrawing::GetInstance()->Draw_String(x - 30, y + (11 * 2), Color(255, 0, 0, 255), DT_CENTER, XorStr("Health : %d"), fHealth);

			if (Vars.VisualMenu.ArmorDraw)
				CDrawing::GetInstance()->Draw_String(x - 30, y + (11 * 3), Color(0, 122, 204, 255), DT_CENTER, XorStr("Armor : %d"), fArmor);

			if (Vars.VisualMenu.ESPDistance)
				CDrawing::GetInstance()->Draw_String(x - 30, y + (11 * 4), Color(255, 122, 0, 255), DT_CENTER, XorStr("Distance : %.f M"), Dist / 100);

			if (Vars.VisualMenu.ESPWeapon)
				CDrawing::GetInstance()->Draw_String(x - 30, y + (11 * 5), Color(255, 122, 204, 255), DT_CENTER, XorStr("%s"), name.c_str());

			if (Vars.VisualMenu.ESPLastPlace)
				CDrawing::GetInstance()->Draw_String(x - 30, y + (11 * 6), Color(255, 122, 0, 255), DT_CENTER, XorStr("%s"), pEntity->GetLastPlace());

			if (Vars.VisualMenu.ShowPitch)
				CDrawing::GetInstance()->Draw_String(x - 30, y + (11 * 7), Color(240, 240, 255, 255), DT_CENTER, XorStr("Pitch: %.1f"), pEntity->GetEyeAngles().X);

			if (Vars.VisualMenu.ShowYaw)
				CDrawing::GetInstance()->Draw_String(x - 30, y + (11 * 8), Color(240, 240, 255, 255), DT_CENTER, XorStr("Yaw: %.1f"), pEntity->GetEyeAngles().Y);

			if (Vars.VisualMenu.IsFlashed && pEntity->IsFlashed())
				CDrawing::GetInstance()->Draw_String(x - 30, y + (11 * 9), Color(240, 240, 0, 255), DT_CENTER, XorStr("Ослеплен"));


			FLOAT Height = abs(vScreenLeg.Y - vScreenHead.Y);
			FLOAT Width = Height / 2.0f;

			if (Vars.VisualMenu.HPBar)
				CDrawing::GetInstance()->Draw_Bar(vScreenHead.X - 2, vScreenLeg.Y + 5, fHealth, Width, 5, Color(0, 255, 0, 255));

			if (Vars.VisualMenu.ArmorBar)
				CDrawing::GetInstance()->Draw_Bar(vScreenHead.X - 2, vScreenLeg.Y + 14, fArmor, Width, 5, Color(0, 122, 204, 255));

			if (Vars.VisualMenu.BulletTrace)
				CDrawing::GetInstance()->BulletTrace(pEntity, Color(240, 0, 0, 255), Vars.VisualMenu.BulletTraceLength);

			if (Vars.VisualMenu.CircleEsp)
				CDrawing::GetInstance()->DrawWave(vLeg, 25, IsVisible(pEntity) ? Color(0, 255, 0, 255) : Color(255, 0, 0, 255));

			JUNK_CODE_ONE

		}

	}


}

extern int crs;
void Player_Loop()
{

	JUNK_CODE_ONE

		if (pEngine->IsTakingScreenshot() || pEngine->IsInGame() == false)
			return;

	auto WndW = GetSystemMetrics(SM_CXSCREEN);
	auto WndH = GetSystemMetrics(SM_CYSCREEN);

	int WScreen = 0, HScreen = 0;
	pEngine->GetScreenSize(WScreen, HScreen);

	if (bShowWindow)
		CDrawing::GetInstance()->Filled_Rect(0, 0, WndW + 100.f, WndH + 100.f, Color(0, 0, 0, 220));

	auto pLocalEntity = pClientEntList->GetClientEntity(pEngine->GetLocalPlayer());

	if (pLocalEntity->IsValid() == false)
		return;

	Sound::Draw();
	hitmarker::singleton()->Paint();


	//if (Vars.VisualMenu.SniperCrosshair)
	if (pLocalEntity->GetWeapon()->GetWeaponType() == WeaponType::Sniper)
		SniperCrosshair(Color(255, 0, 0, 255));

	for (int i = 0; i <= pClientEntList->GetHighestEntityIndex(); i++)
	{
		auto pEntity = pClientEntList->GetClientEntity(i);

		if (pEntity == nullptr)
			continue;

		auto cClass = pEntity->GetClientClass();

		if (cClass == nullptr)
			continue;

		Draw_Weapon(pEntity, cClass);

		if (pEntity == pLocalEntity)
			continue;

		player_info_t pi;

		if (pEngine->GetPlayerInfo(i, &pi) == false)
			continue;

		Draw_Player(pLocalEntity, pEntity, cClass, pi, WScreen, HScreen);

	}
	JUNK_CODE_ONE

}

