// Header file for the player base class
// Celestial Phineas @ ZJU
#ifndef __PLAYER_H
#define __PLAYER_H

#include <vector>
#include "board.h"
#include "winning_judge.h"
#include "te.h"

// The Player class defines an interface for the players. The player have a 
// pointer to the board (a player, either a human or an AI must have an eye on
// the gomoku board), and a stone_color (he must know what stone he is playing).
// To ask the player to make a dicision on a te, the te method should be used.
// And the remove method is used to let the player to remove a stone from the 
// given candidates (type std::vector<Te>).
class Player
{
public:
    typedef unsigned PlayerType;
    static const PlayerType ai_player = 1;
    static const PlayerType human_player = 2;
    static const bool black = false;
    static const bool white = true;
    Player(Board *_board, bool _stone) {board = _board; stone_color = _stone;}
    Player(const Player &src)
        {board = src.board; stone_color = src.stone_color;}
    virtual ~Player() {return;}
    // We need a clone method to request an instance with a base class pointer.
    virtual Player *clone() const = 0;
    virtual PlayerType player_type() const = 0;
    bool is_black() const {return !stone_color;}
    bool is_white() const {return stone_color;}
    void set_board(Board *_board) {board = _board;}
    void set_stone(bool _stone) {stone_color = _stone;}
    // The return value is success or not
    virtual bool te() = 0;
    void set_remove_candidates(const std::vector<Te>& _remove_candidates)
        {remove_candidates = _remove_candidates;}
    virtual bool remove();
    // Return true for willing to exchange.
    virtual bool exchange_choice() {return false;}
protected:
    Board *board;
    bool stone_color;
    std::vector<Te> remove_candidates;
};

class AIPlayer: public Player
{
public:
    AIPlayer(Board *_board, bool _stone, WinningJudge *_judge)
        : Player(_board, _stone) {judge = _judge;}
    AIPlayer(const AIPlayer &src): Player(src) {judge = src.judge;}
    PlayerType player_type() const {return ai_player;}
    virtual ~AIPlayer() {return;}
    // virtual Player *clone() const;
    // virtual bool te();
    // virtual remove();
    void set_judge(WinningJudge *_judge) {judge = _judge;}
protected:
    WinningJudge *judge;
};

#endif