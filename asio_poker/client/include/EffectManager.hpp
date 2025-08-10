#pragma once
#include <vector>
#include <string>
class DrawingCanvas;
class InfoPanel;
class ActionPanel;
class StatusBar;
struct GameManagmentData {
    unsigned int lastPlayerId = 0;
};
class EffectManager {
    public:
        EffectManager();
        //void DrawingCanvasEffect();
        //void GameManagmantEffect();
        void UpdateCurrentStake(const std::string&);
        void HighlightCurrentPlayer(const unsigned int);
        void Kill(const unsigned int);
        void SwapToSmallBlind();
        static DrawingCanvas* drawingCanvas;
        static std::vector<InfoPanel*> players;
        static ActionPanel* actionPanel;
        static StatusBar* statusBar;
    private:
        InfoPanel* GetPlayerById(unsigned int) const;
        struct GameManagmentData gmData;
};