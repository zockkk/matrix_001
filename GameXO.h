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
	AgentXO player1(3, { 9, 9, 9 });
	AgentXO player2(3, { 9, 9, 9 });
	EnvironmentXO state;
	Matrix<double> Y = Matrix <double>::colVector(9);
	Matrix<double> check=Matrix<double>::colVector(9, 0);
	const int epoch = 100;
	const int games = 100;
	bool flag = true;
	for (int i = 0; i < epoch; i++) {
		Matrix<double> errors_Y1 = Matrix<double>::colVector(9);
		Matrix<double> errors_Y2 = Matrix<double>::colVector(9);
		for (int j = 0; j < games; j++) {
			int color = -1;
			flag = true;
			while (state.nextState(check) && flag) {
				//state.restart();
				color *= (-1);
				//std::cout << std::endl;
				if (color == 1) {
					player1.doAction(state.getBoard(), Y);
					player1.setReward(1);
					//Y.print();
					errors_Y1 = (-1) * Y;
					correct_action(Y, probabilities, dre);
					errors_Y1 += Y;
					//Y.print();
					if (!check_action(Y, state.getArr())) {
						player1.setReward(-10);
						//state.print();
						//std::cout << i << std::endl;
						//std::cout << "1 lose" << std::endl;
						flag = false;
					}
					state.nextState(Y);

				}
				else {
					player2.doAction(state.getBoard(), Y);
					player2.setReward(1);
					//Y.print();
					errors_Y2 = (-1) * Y;
					correct_action(Y, probabilities, dre);
					errors_Y2 += Y;
					//Y.print();
					if (!check_action(Y, state.getArr())) {
						player2.setReward(-10);
						//state.print();
						//std::cout << -i << std::endl;
						//std::cout << "2 lose" << std::endl;
						flag = false;
					}
					Y *= (-1);
					state.nextState(Y);
					Y *= (-1);
				}
				/*if ((j + 1) % 100 == 0 && (i + 1) % 100 == 0)
				{ 
					state.print();
					std::cout << i << std::endl;
				}*/
			}
			//std::cout << player1.getReward() << std::endl << player2.getReward() << std::endl;
			if (!state.nextState(check))
			{
				player1.setReward(state.win()*10);
				player2.setReward(-state.win()*10);
				//state.print();
				//std::cout << state.win() << std::endl;
			}
			//state.print();
			state.restart();
		}
		std::cout << player1.getReward() << std::endl << player2.getReward() << std::endl;
		errors_Y1 *= (1.0 / games)*player1.getReward();
		//errors_Y1.print();
		player1.print();
		player1.save(std::to_string(i) + ".txt");
		player1.print();
		player1.learning(&errors_Y1);// ERROR
		//player2.set_fromfile(std::to_string(i) + ".txt");
		//errors_Y2 *= (1.0 / games) * player2.getReward();
		//player2.learning(&errors_Y2);
		player1.setReward(-player1.getReward());
		player2.setReward(-player2.getReward());
	}
}