/***************************************************************************
                          Score.cpp  -  description
                             -------------------
    begin                : Fri Jan 26 2001
    copyright            : (C) 2001 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

#include "Private.h"
#include "Behavior.h"
#include "Group.h"
#include "Pinball.h"
#include "Loader.h"
#include "StateMachine.h"
#include "Score.h"
#include "Keyboard.h"

class ScriptBehavior : public Behavior {
public:
	ScriptBehavior() : Behavior() {
		Loader * loader = Loader::getInstance();
		// init variables
		this->clear();
	};
	~ScriptBehavior() {};

	void onTick() {
		Score * score = Score::getInstance();
		// launch ball
		if (score->active() == 0 && 
				score->getCurrentBall() < 4 
				&& Keyboard::isKeyDown(SDLK_RETURN)) {
			switch (score->getCurrentBall()) {
			case 1 :
				if (score->isBallDead(PBL_BALL_1) ) {
					SendSignal( PBL_SIG_BALL1_ON, 0, this->getParent(), NULL );
					score->activateBall(PBL_BALL_1);	
					score->clearText();
					break;
				}	
			case 2 :
				if (score->isBallDead(PBL_BALL_2)) {
					SendSignal( PBL_SIG_BALL2_ON, 0, this->getParent(), NULL );
					score->activateBall(PBL_BALL_2);
					score->clearText();
					break;
				}
			case 3 :
				if (score->isBallDead(PBL_BALL_3)) {
					SendSignal( PBL_SIG_BALL3_ON, 0, this->getParent(), NULL );
					score->activateBall(PBL_BALL_3);
					score->clearText();
					break;
				}
				if (score->isBallDead(PBL_BALL_1) ) {
					SendSignal( PBL_SIG_BALL1_ON, 0, this->getParent(), NULL );
					score->activateBall(PBL_BALL_1);	
					score->clearText();
					break;
				}	
				if (score->isBallDead(PBL_BALL_2)) {
					SendSignal( PBL_SIG_BALL2_ON, 0, this->getParent(), NULL );
					score->activateBall(PBL_BALL_2);
					score->clearText();
					break;
				}
			default:
				throw string("all balls busy");
			}
			EM_COUT("Score::onTick() new ball", 1);
		}
	};

	void StdOnCollision() {};

	void StdOnSignal() {
		Score * score = Score::getInstance();
		Loader * loader = Loader::getInstance();
		//EM_COUT((int)em_signal, 1);
		
		OnSignal( PBL_SIG_RESET_ALL ) {
			this->clear();
		} else
		// ball dead
		OnSignal( PBL_SIG_BALL1_OFF OR_SI 
							PBL_SIG_BALL2_OFF OR_SI	
							PBL_SIG_BALL3_OFF OR_SI 
							PBL_SIG_BALL4_OFF ) {
			if (score->active() == 1) {
				// multiball is dead
				SendSignal( loader->getSignal("multiball_off"), 0, this->getParent(), NULL );
				m_bMultiBall = false;
			}
			if (score->active() == 0) {
				// no active ball
				SendSignal( loader->getSignal("allballs_off"), 0, this->getParent(), NULL );
				if (m_bExtraBall) {
					m_bExtraBall = false;
				} else if (score->getCurrentBall() < 4) {
					score->setCurrentBall(score->getCurrentBall()+1);
					if (score->getCurrentBall() == 4) {
						SendSignal( PBL_SIG_GAME_OVER, 0, this->getParent(), NULL );
						EM_COUT("game over", 1);
					}
				}
			}
		}
	}

	void clear() {
		m_bExtraBall = false;
		m_bMultiBall = false;
	};

private:
	bool m_bExtraBall;
	int m_bMultiBall;
};

extern "C"  void * new_object_fct(void) {
	return new ScriptBehavior();
}

