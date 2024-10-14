# Computational-Physics
Simulations + numerical methods in C++ to solve selected problems in physics! 

In this repository are C++ files for simulations/numerical methods completed in my Computational Physics class! In this course I had the opportunity to program super cool simulations like Monte Carlo simulations and molecular dynamics. I wanted to have a repository to share everything I learned here!  

## Monte Carlo 2D Ising Simulation
The 2D Ising model is a great excercise for a computational physicists to gain hands on experience with Monte Carlo simulations. The model describes a magnetic system composed of classical spins, $s_{i,j}$, on an $L$ $\times$ $L$ lattice, where each spin can either be spin up or spin down. At temperatures, $T$, above the critical temperature, $T_c$, the system is in a paramagnetic state, i.e. the spins are randomly ordered. At $T_c$, the system undergoes a phase transition, and at $T < T_c$, the system becomes ferromagnetic, i.e. the spins are all aligned in the same direction. 

The ideo of this simulation is to use a Monte Carlo algorithm to set up a random walk which will sample different configurations of the system, such that the configurations occur with the probability given by the Boltzmann distribution. 

The algorithm is as follows: 
1. 



