#include <iostream>
#include <random>
#include <algorithm>

int main (){
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Mean market return of 7% (0.07), with a 15% (0.15) standard deviation
    std::normal_distribution<double> market_dist(0.07, 0.15); 
    
    // Core Variables
    const int SIMULATIONS = 10000;
    const int YEARS = 30;
    const double STARTING_SALARY = 35000.0;
    const double STARTING_LOAN = 45000.0;
    const double OVERPAY_BUDGET = 2400.0;
    
    int invest_wins = 0;
    int overpay_wins = 0;

    // The Monte Carlo Loop
    for (int i = 0; i < SIMULATIONS; ++i) {
        
        double bal_A = STARTING_LOAN, invest_A = 0.0; // Scenario A: Invest
        double bal_B = STARTING_LOAN, invest_B = 0.0; // Scenario B: Overpay
        double current_salary = STARTING_SALARY;

        // Simulate 30 individual years
        for (int year = 0; year < YEARS; ++year) {
            
            // Draw a random market return for THIS specific year
            double yearly_market_return = market_dist(gen);
            
            // Fixed loan rate for simplicity (could also be randomized based on RPI)
            double loan_rate = 0.065; 
            
            double mandatory_pay = std::max(0.0, (current_salary - 29385.0) * 0.09);

            // --- UNIVERSE A: Invest ---
            if (bal_A > 0) {
                bal_A = (bal_A * (1.0 + loan_rate)) - mandatory_pay;
            }
            invest_A = (invest_A * (1.0 + yearly_market_return)) + OVERPAY_BUDGET;

            // --- UNIVERSE B: Overpay ---
            if (bal_B > 0) {
                double total_pay = mandatory_pay + OVERPAY_BUDGET;
                bal_B = (bal_B * (1.0 + loan_rate)) - total_pay;
                
                if (bal_B < 0) {
                    invest_B += std::abs(bal_B);
                    bal_B = 0;
                }
            } else {
                invest_B = (invest_B * (1.0 + yearly_market_return)) + mandatory_pay + OVERPAY_BUDGET;
            }

            // Standard 2.5% salary growth
            current_salary *= 1.025; 
        }

        // Tally the winner of this specific simulation
        if (invest_A > invest_B) {
            invest_wins++;
        } else {
            overpay_wins++;
        }
    }

    // 4. Output the Probability
    std::cout << "Ran " << SIMULATIONS << " simulations.\n";
    std::cout << "Investing won: " << (static_cast<double>(invest_wins) / SIMULATIONS) * 100.0 << "%\n";
    std::cout << "Overpaying won: " << (static_cast<double>(overpay_wins) / SIMULATIONS) * 100.0 << "%\n";

    return 0;
}
