#pragma once
#include <wx/wx.h>
#include <vector>
#include <string>
#include "../../server/include/Constants.hpp"
class DrawingCanvas;
class InfoPanel;
class ActionPanel;
class StatusBar;
class GameStage;
class ClientFrame;
struct GameManagmentData {
    unsigned int lastPlayerId = 0;
};
wxDECLARE_EVENT(wxEVT_SOLO_WIN, wxCommandEvent);

class EffectManager {
    public:
        EffectManager();
        //void DrawingCanvasEffect();
        //void GameManagmantEffect();
        void UpdateCurrentStake(const std::string&);
        void HighlightCurrentPlayer(const unsigned int);
        void Kill(const unsigned int);
        void SwapToSmallBlind();
        void SetStake(int,int);
        void SetPot(const std::string&);
        void SetCards(int, struct Card&, struct Card&);
        void SoloWin(int);
        void MultiWin(std::vector<int>);
        static DrawingCanvas* drawingCanvas;
        static std::vector<InfoPanel*> players;
        static ActionPanel* actionPanel;
        static StatusBar* statusBar;
        static GameStage* gameStage;
        static ClientFrame* clientFrame;
    private:
        InfoPanel* GetPlayerById(unsigned int) const;
        struct GameManagmentData gmData;
};