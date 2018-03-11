# BankersAlgorithmImplementation


Abstract
-------

The Banker’s Algorithm is one of the techniques for the deadlock avoidance.
The name is chosen because the algorithm could be used in the banking
system to ensure that the bank never allocated ies available cash in such a
way that it could no longer satisfy the needs of all its customers.
Several data structures must be maintained to implement the banker’s
algorithm. These data structures encode the state of the resource-allocation
system. When a new process enters the system it must declare the maximum
number of instances of each resource type it may need. This number may not
exceed the total number of resources in the system. When a user requests a
set of resources the system must determine whether the allocation of these
resources will leave the system in a safe state. If it will, the resources are
allocated; otherwise the process must wait until some other process releases
enough resources.
2 Problem Definition


Implementation
--------------

We are using multithreading techniques to illustrate the working of Banking Algorithm . Implemented two algorithms , namely Safety Algorithm and Resource Request Algorithm.
and showed the working 

