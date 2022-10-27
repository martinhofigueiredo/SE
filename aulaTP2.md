# Response Time Analysis

 - The response time analysis doesnt variate from the prioritization mode or forces the rate to be monotonic

# Online scheduling with dynamic priorities

The schedule is being __built__ while it works so it maintains an otptimum order.

# Pros
- Easily Scalable
	- since it considers everytime in runtime it can deal with a bigger amount of task
	- this property makes it able to deal with sporadic tasks

# Cons
- Harder to implement than cyclic 
	- this needs to be constantly updating so theres a compute power loss since the scheduler needs some cycle itseld to run

# Dynamic priorities

- __EDF__ Earliest Deadline first
	- Inversely proprotional to the time of the deadline
	- optimal with respect to dynamic priorities criteria

- __LSF__ Least Slack First or __LLF__ Least Laxity First
	- Inversely proportional to slack or laxity rsad %t%
	- optimal with respect to dynamic priorities criteria

- __FCFS__ First Come First Serve
	- doesnt need preemption because it will always do the task by order of request

## EDF Utilization base schedulability tests for EDF

- In this mode the task with the closest deadline will be prioritized. We can also conclude that with the Utilization Rate that if it is under 1 then it is schedulable 

$$ U = \frac{C_i}{T_i} $$

$$ U = \sum{n}{i=1}\frac{C_i}{min(T_i,D_i)} $$

## (Rate Monotonic)__RM__  vs __EDF__

- If the worst case possible is possible (when the tasks run with the least slack) the a case with more slack will work

## Notion of fairness


## CPU Demand Analysis

Knowing L, we then need to guarantee that the following load condition is met, i.e. 

$$ h(t) <= t $$
