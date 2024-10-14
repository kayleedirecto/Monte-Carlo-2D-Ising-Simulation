#include <iostream> 
#include <math.h> 
#include <vector> 
#include <cmath> 
#include <typeinfo>
#include "MCvar.h"
#include <iomanip>
#include <string>

// Function that performs Nmcs MC sweeps 
void MCSweeps(std::vector<std::vector<int>> &SpinConf, int L, int Nmcs, double T, std::vector<double> ExpLookupTable,  std::vector<int> np,  std::vector<int> nm){ 
    // SpinConf = 2D vector holding the spins (-1 or 1) of the LxL lattice 
    // L = length of the lattice 
    // Nmcs = number of Monte Carlo sweeps 
    // T = temperature 
    // ExpLookupTable = Table w pre-computed values of exp(dE/T)
    // np = Array with indices for next neighbour 
    // nm = Array with indices for previous neighbour

    // First initializing the random number generators 
    std::random_device r; // Random number producer 
    std::uniform_int_distribution<int> uniform_discrete_dist(0, L-1); // Initializing the uniform discrete dist on [0,10]
    std::uniform_real_distribution<> unif_cont_dist(0,1); // Initializing the distribution, which is continuous uniform on 0,1
    std::mt19937 random_gen(r());  // The variable you feed into the distribution; Random number generator based on Mersenne Twister algorithm. Argument is the seed. r() intializes random seed. 

    // Performing MCSweep Nmcs times 
    for(int q = 0; q < Nmcs; q++){
        // Attempting to flip a spin LxL times 
        for(int n = 0; n < L*L; n++){ 
            // First randomly choosing coordinates for randomly chosen spin
            int i = uniform_discrete_dist(random_gen); // ith row
            int j = uniform_discrete_dist(random_gen);  // jth column 

            // Calculating the change in energy from flipping the spin at SpinConf[i,j]
            int si = SpinConf[i][j]; // Spin at current location 
            int sum_sj = SpinConf[np[i]][j] + SpinConf[nm[i]][j] + SpinConf[i][np[j]] + SpinConf[i][nm[j]]; // Sum of neighbouring spins. Using neighbour indice arrays (nm and np) to compute nearest neighbours. 
            int dE = 2 * si * sum_sj;  // Calculating the change in energy. We do not account for J here, so T units are in terms of k/J.  
            
            // Assigning prob based on ExpLookupTable
            int index = (dE + 8)/4; // Maps dE to correct index in lookup table 
            double prob = ExpLookupTable[index]; // Assigns probability using the pre-computed exp lookup table 

            // Now determining if we should flip the spin
            double p_flip = std::min(1., prob); 
            double rand_num = unif_cont_dist(random_gen); 
            if(p_flip > rand_num){ 
                SpinConf[i][j] *= -1; 
            }
        } 
    }
}

// Function to calculate the energy of the configuration 
long long Energy (const std::vector<std::vector<int>> &SpinConf, std::vector<int> np,  std::vector<int> nm){ 
        int L = SpinConf[0].size(); 
        long long E = 0; 
        for(int i = 0; i < L; i++){ 
            for(int j = 0; j < L; j++){ 
                int si = SpinConf[i][j]; // Spin at current location 
                int sum_sj = SpinConf[np[i]][j] + SpinConf[nm[i]][j] + SpinConf[i][np[j]] + SpinConf[i][nm[j]]; // Sum of neighbouring spins. 
                E += si * sum_sj; // Adding these interactions to the energy sum 
            }
        } 
    return - E / 2; // Divide by 2, to account for the double counting of interactions 
}

// Function to calculate the magnetization of the lattice 
long long Magnetization(const std::vector<std::vector<int>> &SpinConf){ 
    int L = SpinConf[0].size(); 
    long long value = 0; 
    for(int i = 0; i < L; i++){ 
        for(int j = 0; j < L; j++){ 
            value += SpinConf[i][j]; // Adding the spin of the current location to the magnetization
            }
        } 
    return value; 
}

// Function that initializes the spin configuration 
std::vector<std::vector<int>> Initialize(int L){ 
    // Takes in  the desired size of the square lattice 
    std::vector<std::vector<int>> spin_conf(L, std::vector<int>(L, 0));

    // Initializing random distribution 
    std::random_device r; // Random number producer 
    std::uniform_int_distribution<int> uniform_discrete_dist(0, 1); // Discrete distribution that will decide whether spin is +1 or -1
    std::mt19937 random_gen(r()); 

    for(int i = 0; i < L; i++){ 
        for(int j = 0; j < L; j++){ 
            int spin = uniform_discrete_dist(random_gen); // Generating 0 or 1 
            spin_conf[i][j] = (spin == 0) ? -1 : 1; // Using ternary operator to write concise if-else statement 
        }
    } 
    return spin_conf; 
}

// Fnuction that takes measurement of E, E^2, E^4, M, M^2, M^4
void do_measurement(const std::vector<std::vector<int>> &SpinConf, std::vector<int> np, std::vector<int> nm, MCvar<double> &E, MCvar<double> &E2, MCvar<double> &E4, MCvar<double> &M, MCvar<double> &M2, MCvar<double> &M4){ 
    int L = SpinConf[0].size(); 
    double e = Energy(SpinConf, np, nm); 
    double m = Magnetization(SpinConf); 
    E.push(e); 
    E2.push(e*e); 
    E4.push(e*e*e*e); 
    M.push(m); 
    M2.push(m*m); 
    M4.push(m*m*m*m); 
}

// Function that prints out calculated averages
void Printout(MCvar<double> E, MCvar<double> E2, MCvar<double> E4, MCvar<double> M, MCvar<double> M2, MCvar<double> M4){ 
    std::cout << std::fixed << std::setprecision(6); // Set precision for output
    std::cout << "Average E = " << E.Avrg() << " ± " << E.Err_Avrg() << std::endl; 
    std::cout << "Average E^2 = " << E2.Avrg() << " ± " << E2.Err_Avrg() << std::endl;
    std::cout << "Average E^4 = " << E4.Avrg() << " ± " << E4.Err_Avrg() << std::endl;
    std::cout << "Average M = " << M.Avrg() << " ± " << M.Err_Avrg() << std::endl;
    std::cout << "Average M^2 = " << M2.Avrg() << " ± " << M2.Err_Avrg() << std::endl;
    std::cout << "Average M^4 = " << M4.Avrg() << " ± " << M4.Err_Avrg() << std::endl;
} 

// Main function that simulates the Ising Model 
int main(){ 

    int L; 
    double T; 
    int Nwarmup; 
    int Nmeas; 
    int Nstep; 

    //Question 2.3 - 2.4 
    std::cout << "Please input size of lattice (int):" << std::endl; 
    std::cin >> L; // For 2.3, L = 50
    std::cout << "Please input Temperature, in units kB/J:" << std::endl; 
    std::cin >> T; // For 2.4 = 2.26, 2.45

    std::cout << "Please input desired number of warm up steps:" << std::endl; 
    std::cin >> Nwarmup; 
    std::cout << "Please input desired number of measurements:" << std::endl; 
    std::cin >> Nmeas; 
    std::cout << "Please input desired number of Monte Carlo sweeps to perform between each measurement:" << std::endl; 
    std::cin >> Nstep; 

    // Opening file to write to 
    FILE *fp;
    std::string T_string = std::to_string(T);
    std::string L_string = std::to_string(L);
    std::string file_name = "montecarlo_l" + L_string + "_t" + T_string + ".txt"; 
    fp = fopen(file_name.c_str(), "w"); 

    // Initializing the lookup table to optimize computing exp(dE/T)
    std::vector<double> ExpLookupTable(5, 0); // Vector to hold lookup table 
    int dE_values[5] = {-8, -4, 0, 4, 8}; // Possible values of dE (in units of J)
    for(int p = 0; p < 5; p++){ 
        ExpLookupTable[p] = exp(-dE_values[p]/T); // Calculating exp
    }  

    // Pre computing neighbour indices for accessing nearest neighbours in spin energy calculations, taking into account boundary conditions 
    std::vector<int> np(L); // Holds indices for next neighbour in 1D 
    std::vector<int> nm(L); // Holds indices for previous neighbour in 1D
    // Now filling the arrays with the nearest neighbour indices based on the boundary conditions 
    for(int p = 0; p < L; p++){ 
        np[p] = (p == L-1) ? 0 : p + 1; // If spin is at last index (L-1) next neighbour = 0, else next neighbour = current index + 1
        nm[p] = (p == 0) ? L-1 : p - 1;  // If spin is at first index (0) previous neighbour = current index - 1 , else previous neighbour = L-1
    }

    // Declaring MCVar measurements for each observable 
    MCvar<double> E, E2, E4, M, M2, M4; 

    // Initializing the spin configuration 
    std::vector<std::vector<int>> spin_conf = Initialize(L);

    // First warming up 
    std::cout << "Warming up" << std::endl; 
    MCSweeps(spin_conf, L, Nwarmup, T, ExpLookupTable, np, nm); 

    // Now performing the sweeps that will do the measurements for question 2.4 
    std::cout << "Now performing measurements" << std::endl; 
    for(int n = 0; n < Nmeas; n++){ 
        MCSweeps(spin_conf, L, Nstep, T,ExpLookupTable, np, nm); // Performing MCSweep NStep times 
        do_measurement(spin_conf, np, nm, E, E2, E4, M, M2, M4); // Taking measurements 

        // Writing magnetization to the file 
        fprintf(fp, "%lld \n", Magnetization(spin_conf));

        std::cout << "Measurement number " << n << std::endl; 
    } 
}

