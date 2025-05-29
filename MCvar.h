// Header file which handles binning for Monte Carlo simulations. Ensures measurements taken are independent. 

#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

template <class Type> class MCvar { // Template means it can handle different types of variables, "type" is a placeholder for whatever the variable is 
// Data
public:

private: // Only can access from inside the class 
	int bin_size;
        int count; // Tracks how many points have been added into a bin, resets when bin is filled 
        int no_of_bins; // Counter for the # of bins, increments each time a bin is filled 
	Type av; // Stores running sum of values in bin, is "type" so that it works with whatever type the class is 
	std::vector<double> Bins; // Stores average of completed bins 

//Methods
public: // Public means we can access these variables from anywhere in our code 
        // Constructor: special method automatically called when an object of a class is created, has the same name as the class
        MCvar() : bin_size(1000),count(0),no_of_bins(0) {} // Constructor that sets the bin size to 1000 (if no specific bin size is passed), count to 0, and # bins to 0 
        MCvar(int bsz) : bin_size(bsz),count(0),no_of_bins(0) {} // Constructor that allows you to pick specific bin size 
        void push(const Type v) // This method adds new data to the current bin 
	{ 
                if (count == 0) {
                        av = v;
                        count += 1;
                }else if (count < bin_size-1) {
                        av += v;
                        count += 1;
                }else {
                        av += v;
                        Bins.push_back(((double) av)/bin_size); 
                        count = 0;
                        no_of_bins += 1.;
                }
        }

        double Avrg() // This method computes the average of all the values over all the bins 
	{ 
                double res = 0.0;
                for (auto r : Bins) res += r; // Range based for loop. Loops over each value in vector Bins. 
                return (res/no_of_bins);
        }

        double Err_Avrg()
	{ 
                double sdom; 
                double res = 0.0, res2=0.0;

                for (auto r : Bins) {
                        res += r; // Sum for the mean < O >
                        res2 += r*r; // Sum for the second moment < O^2 > 
                }

                res = res / no_of_bins; // Calculating < O >
                res2 = res2 / no_of_bins; // Calculating < O^2 > 

                // Check to ensure that there is more than 1 bin
                if(no_of_bins > 1){ 
                        sdom = std::sqrt((res2 - (res*res)) / (no_of_bins - 1)); 
                } else { 
                        sdom = 0.; // Cannot compute the SDOM
                        std::cout << "Cannot compute the SDOM" << std::endl; 
                }
                return (sdom);
        }
};
