//
// Created by awing on 10/05/2026.
//

#include "Strategie.h"


namespace cerveau::strategie {
    void generateBlueStrat(){}
    void generateYellowStrat(){}
    void stratDeSecoursBleu(){}
    void stratDeSecoursJaune(){}
}


///ActionNode* action(auto nf){
///     auto* n = new Grafcet::ActionNode();
///     n->actionFunction = nf
///     return n;
///};

///nf1 = Wheeledbase::GOTO(&positions_bleu[R0L_B], true, PurePursuit::FORWARD, false);
///n1 = action(nf1);
///n1->addChild(t0);


///ActionNode* transition(tf){
///     auto* t = new Grafcet::Transition();
///     t->actionFunction = tf;
///     return t;
///}

///tf1 = Wheelbase::POSITION_REACHED() & 0b01;
///t1 = transition(tf1);
///tf1->addChild(n1);
