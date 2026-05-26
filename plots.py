import matplotlib.pyplot as plt
import numpy as np

def plot_deterministic_lifespan(salary, loan, budget):
    years = 30
    loan_rate = 0.065
    invest_rate = 0.07
    threshold = 29385
    
    # Trackers for plotting
    x_years = np.arange(1, years + 1)
    history_bal_A, history_invest_A = [], []
    history_bal_B, history_invest_B = [], []
    
    bal_A, invest_A = loan, 0
    bal_B, invest_B = loan, 0
    current_salary = salary
    
    for year in range(years):
        mandatory_pay = max(0, (current_salary - threshold) * 0.09)
        
        # Scenario A: Invest
        if bal_A > 0:
            bal_A = max(0, (bal_A * (1 + loan_rate)) - mandatory_pay)
        invest_A = (invest_A * (1 + invest_rate)) + budget
        
        # Scenario B: Overpay
        if bal_B > 0:
            total_pay = mandatory_pay + budget
            bal_B = (bal_B * (1 + loan_rate)) - total_pay
            if bal_B < 0:
                invest_B += abs(bal_B)
                bal_B = 0
        else:
            invest_B = (invest_B * (1 + invest_rate)) + mandatory_pay + budget
            
        current_salary *= 1.025
        
        history_bal_A.append(bal_A)
        history_invest_A.append(invest_A)
        history_bal_B.append(bal_B)
        history_invest_B.append(invest_B)

    # --- Plotting the Data ---
    plt.figure(figsize=(10, 6))
    
    # Plot Universe A
    plt.plot(x_years, history_bal_A, label="Loan Balance (Invest Strategy)", color='red', linestyle='--')
    plt.plot(x_years, history_invest_A, label="Investment Pot (Invest Strategy)", color='blue')
    
    # Plot Universe B
    plt.plot(x_years, history_bal_B, label="Loan Balance (Overpay Strategy)", color='darkred', linestyle=':')
    plt.plot(x_years, history_invest_B, label="Investment Pot (Overpay Strategy)", color='green')
    
    plt.title("UK Student Loan: Invest vs. Overpay (30-Year Projection)")
    plt.xlabel("Years")
    plt.ylabel("Value (£)")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.show()

# Run the plot
plot_deterministic_lifespan(35000, 45000, 2400