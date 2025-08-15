#pragma once
#include <vector>
#include <string>
class DrawingCanvas;
class InfoPanel;
class ActionPanel;
class StatusBar;
class GameStage;
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
        void SetStake(int,int);
        void SetPot(const std::string&);
        static DrawingCanvas* drawingCanvas;
        static std::vector<InfoPanel*> players;
        static ActionPanel* actionPanel;
        static StatusBar* statusBar;
        static GameStage* gameStage;
    private:
        InfoPanel* GetPlayerById(unsigned int) const;
        struct GameManagmentData gmData;
};