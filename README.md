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

## The Results 

As an example, let's take $T_c = 2.269 k_B/J$. We can create a histogram of the observed magnetization (sum of every spin on the lattice) at temperatures 2.26 $k_B/J$ and 2.45 $k_B/J$, as shown below. 

<img width="400" alt="Screenshot 2025-05-29 at 4 30 57 PM" src="https://github.com/user-attachments/assets/8942ce4b-102e-4041-b819-2df4669ea921" />

<img width="400" alt="Screenshot 2025-05-29 at 4 31 50 PM" src="https://github.com/user-attachments/assets/4e46c287-51d9-4d73-ba53-0d4a29c00c02" />

At 2.45 $k_B/J$, above the critical temperature, we see the lattice is paramagnetic, i.e. the spins are randomly ordered. There is a 50% chance the magnetization will be -1 and 50% chance it will be +1, so it makes sense that the average magnetization of the sample is centered around 0. 

At 2.26 $k_B/J$, just below the critical temperature, the lattice transitions to ferromagnetic, i.e. all spin up or spin down. In the specific simulation I've shown, we see the case where the majority of the samples magnetizations are close to entirely spin up, i.e. very close to 1. Other times I run this simulation, sometimes I get majority spin down, as shown below: 

<img width="400" alt="Screenshot 2025-05-29 at 4 39 54 PM" src="https://github.com/user-attachments/assets/c0d3ba8c-da04-4ad0-8e13-18ad8516a43a" />





