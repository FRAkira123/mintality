#pragma once
using PaintTraverseFn = void(__stdcall*)(unsigned int, bool, bool);
PaintTraverseFn pPaintTraverse = nullptr;


extern void Player_Loop();


using ServerRankRevealAllFn = bool(__cdecl*)(float*);
ServerRankRevealAllFn ServerRankRevealAllEx = nullptr;

std::uintptr_t  dw_ServerRankRevealAllEx = FindPatternWithoutMask(XorStr("client.dll"), XorStr("55 8B EC 8B 0D ? ? ? ? 68 ? ? ? ? "));

void ServerRankRevealAll()
{
	static float fArray[3] = { 0.f, 0.f, 0.f };

	ServerRankRevealAllEx = (ServerRankRevealAllFn)(dw_ServerRankRevealAllEx);
	ServerRankRevealAllEx(fArray);
}

void __stdcall Hooked_PaintTraverse(unsigned int panel, bool forceRepaint, bool allowForce)
{
	pPaintTraverse(panel, forceRepaint, allowForce);

	static DWORD FocusOverlayPanel = NULL;

	if (FocusOverlayPanel == NULL)
	{
		string panelname = pPanel->GetName(panel);

		if (panelname.find("FocusOverlayPanel") != string::npos)
			FocusOverlayPanel = panel;

		if (espfont == NULL)
		{
			espfont = pSurface->CreateFontA();
			pSurface->SetFontGlyphSet(espfont, XorStr("Arial"), 11, 400, 0, 0, FONTFLAG_OUTLINE);
		}

	}

	if (panel != FocusOverlayPanel)
		return;

	if (Vars.Misc.Ranks && GetAsyncKeyState(VK_TAB))
		ServerRankRevealAll();


	Player_Loop();
	DrawGlow();
}

