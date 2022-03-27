#pragma once
#include "AbstractAgent.h"
#include "AbstractEnvironment.h"
#include <random>
#include <chrono>

void correct_action(Matrix<double>& _Y, std::vector<double>& _prob, std::default_random_engine& _dre) 
{
	for (size_t i = 0; i < 9; i++) {
		_prob[i] = _Y[i][0];
	}
	std::discrete_distribution<size_t> dd(begin(_prob), end(_prob));
	int a = dd(_dre);
	for (size_t i = 0; i < 9; i++) {
		_Y[i][0] = 0.0;
		if (a == i) {
			_Y[i][0] = 1.0;
		}
	}
}

bool check_action(const Matrix<double> action,const Matrix<double> state)
{
	for (size_t i = 0; i < 9; i++) {
		if (action[i][0] * state[i][0] != action[i][0]) return false;
	}
	return true;
}

void game() 
{
	std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());
	std::vector<double> probabilities(9);
	AgentXO player1(5, { 9, 81, 81, 81, 9 });
	AgentXO player2(5, { 9, 81, 81, 81, 9 });
	EnvironmentXO state;
	Matrix<double> Y = Matrix <double>::colVector(9);
	Matrix<double> check=Matrix<double>::colVector(9, 0);
	const int epoch = 1000;
	const int games = 100;
	bool flag = true;
	for (int i = 0; i < epoch; i++) {
		Matrix<double> errors_yEpoch = Matrix<double>::colVector(9, 0.0);
		int fails_epoch = 0;
		for (int j = 0; j < games; j++) {
			Matrix<double> errors_yGame = Matrix<double>::colVector(9, 0.0);
			int color = -1;
			flag = true;
			while (state.nextState(check) && flag) {
				color *= (-1);
				if (color == 1) {
					player1.doAction(state.getBoard(), Y);
					//player1.setReward(0.2);
					player1.setRewardGame(0.2);
					errors_yGame += (-1) * Y;
					correct_action(Y, probabilities, dre);
					errors_yGame += Y;
					if (!check_action(Y, state.getArr())) {
						//player1.setReward(-1);
						player1.setRewardGame(-4);
						fails_epoch++;
						flag = false;
					}
					state.nextState(Y);

				}
				else {
					state.inversion();
					player2.doAction(state.getBoard(), Y);
					//player2.setReward(0.2);
					correct_action(Y, probabilities, dre);
					if (!check_action(Y, state.getArr())) {
						//player2.setReward(-1);
						flag = false;
					}
					state.nextState(Y);
					state.inversion();
				}
				if ((i+1)%epoch==0)	{ state.print(); if (flag == false) { std::cout << "error" << std::endl; }	}
				//state.print();
			}
			if (!state.nextState(check))
			{
				//player1.setReward(state.win());
				player1.setRewardGame(state.win());
				//player2.setReward(-state.win());
			}
			//std::cout << player1.getRewardGame() << std::endl;
			errors_yGame = errors_yGame*player1.getRewardGame();
			errors_yEpoch += errors_yGame;
			player1.learning(&errors_yGame);
			player1.setReward(player1.getRewardGame());
			player1.setRewardGame(-player1.getRewardGame());
			state.restart();
		}
		//std::cout << player1.getReward() << std::endl << fails_epoch << std::endl; //<< player2.getReward() << std::endl;
		errors_yEpoch *= (1.0 / games);//check
		player1.save(std::to_string(i) + ".txt");
		player1.learning(&errors_yEpoch);//check
		//player2.set_fromfile(std::to_string(i) + ".txt");
		//errors_Y2 *= (1.0 / games) * player2.getReward();
		//player2.learning(&errors_Y2);
		player1.setReward(-player1.getReward());
		//player2.setReward(-player2.getReward());
	}
}