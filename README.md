# Monte Carlo 2D Ising Simulation 

The 2D Ising model is a great excercise for a computational physicists to gain hands on experience with Monte Carlo simulations. The model describes a magnetic system composed of classical spins, $s_{i,j}$, on an $L$ $\times$ $L$ lattice, where each spin can either be spin up or spin down. At temperatures, $T$, above the critical temperature, $T_c$, the system is in a paramagnetic state, i.e. the spins are randomly ordered. At $T_c$, the system undergoes a phase transition, and at $T < T_c$, the system becomes ferromagnetic, i.e. the spins are all aligned in the same direction. 

The ideo of this simulation is to use a Monte Carlo algorithm to set up a random walk which will sample different configurations of the system, such that the configurations occur with the probability given by the Boltzmann distribution. 

The algorithm is as follows: 
1. Initialize a random configuration of spins on an $L \times L$ lattice
2. Choose a spin randomly on the lattice
3. Calculate the change in energy, $\delta E$, of the system in flipping the spin
4. Flip the spin with the probability used by the Metropolis algorithm, i.e. $P_{flip} = min(1,e^{-\delta E/kT})$
5. Go to 2

This algorithm should generate a sequence of configurations, with each configuration occuring at the probability given by the Boltzmann distribution. 


