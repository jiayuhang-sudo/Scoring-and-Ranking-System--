#pragma once

#define PlayerNumber 5
#define JudgeNumber 10

#include <string>
#include <deque>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

using std::string;
using std::deque;
using std::vector;
using std::cout;
using std::endl;

//类声明

//选手（姓名，得分）//使用类的明显标志!!!
class Player
{
public:
    /* data */
    string mName;
    deque<double> mAllScore;//去除最高分，去除最低分//双端处理用deque
    double mAverageScore;

public:
    Player(/* args */);
    ~Player();
};

//函数声明

void PlayerNameInit(vector<Player>& vTemp);

void JudgeScoring(vector<Player>& vTemp);

void GetAversgeScore(vector<Player>& vTemp);

bool ComparedByAverageScore(const Player& first,const Player& second);//用const保证不被修改, 用&避免拷贝, 提高效率, 也是规范

void RankingAndOutput(vector<Player>& vTemp);