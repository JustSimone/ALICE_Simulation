<h1>ALICE Simulation</h1>
<h2>ALICE Project</h2>
<p>The idea behind this project is to simulate the ALICE experiment conducted at CERN from 1993.
It consists on the study of the collisions of heavy particles to achieve temperatures and energy density that allow the formation of the Quark-Gluon-Plasma, a state of matter in which quarks and gluons are freed. (<a href="https://home.cern/science/experiments/alice">ALICE project</a>)</p>

<h2>The Simulation</h2>
<p>In our simulation we will recreate the collisions between the particles using the probabilities of obtaining certain particles, In particular: </p>

| Particle | Probability |
| -------- | ----------- |
| Pion + (π+)| 40% |
| Pion - (π-) | 40% |
| Kaon + (k+) | 5% |
| Kaon - (k-) | 5% |
| Proton + (P+)| 4.5% |
| Proton - (P-) | 4.5% |
| Kaon 0 (k0) | 1.5% |

<h2> Building </h2>
<p>To build the code using the main it is recommended to use <a href="https://cmake.org">Cmake</a>. You need to find yourself into the ALICE_Simulation/script folder into your terminal and use the following commands: </p>

~~~
cmake -S . -B Build
cmake --build Build
./build/ALICE_Simulation
~~~

<p>Otherwise it is also possible to build it using <a href="https://root.cern">ROOT</a>. Here, as before, you need to be into ALICE_Simulation from your terminal, open ROOT and use the following commands: </p>

~~~
.L script/ParticleType/ParticleType.cpp+
.L script/ResonanceType/ResonanceType.cpp+
.L script/Particle/Particle.cpp+
~~~
