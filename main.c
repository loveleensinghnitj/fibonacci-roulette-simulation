#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Player {
    int bankroll;
    int bet;
};

int bet_size(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return bet_size(n - 1) + bet_size(n - 2);
}

int main() {

    srand(time(NULL));

    int n_simulations = 500000;
    int initial_bankroll = 1000;

    struct Player loveleen;
    loveleen.bankroll = initial_bankroll;
    int bet_controller = 1;

    int record_failures[n_simulations];

    for (int j = 0; j < n_simulations; j++) {
        loveleen.bankroll = initial_bankroll;
        bet_controller = 1;
        for (int i = 1; ; i++) {

            //Loveleen placing bet
            loveleen.bet = bet_size(bet_controller);

            //Check for enough bankroll
            if (loveleen.bet > loveleen.bankroll) {
                *(record_failures + j) = i;
                break;
            }

            //Spinning roulette wheel
            int result = rand() % 37;

            //Loveleen's Strategy
            if (result >= 1 && result <= 12) {
                loveleen.bankroll += 2 * loveleen.bet;
                bet_controller = 1;
            }
            else {
                loveleen.bankroll -= loveleen.bet;
                bet_controller++;
            }
        }
    }

    int highest_rounds = *record_failures, lowest_rounds = *record_failures;
    double average_rounds = 0;

    for (int j = 0; j < n_simulations; j++) {
        average_rounds += *(record_failures + j);
        if (highest_rounds < *(record_failures + j)) highest_rounds = *(record_failures + j);
        if (lowest_rounds > *(record_failures + j)) lowest_rounds = *(record_failures + j);
    }
    average_rounds /= n_simulations;

    printf("Highest rounds: %d\n", highest_rounds);
    printf("Lowest rounds: %d\n", lowest_rounds);
    printf("Average rounds: %lf\n", average_rounds);

    return 0;
}
