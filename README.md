# Analysis of TCP Cubic and TCP DCTCP in NS3 simulator
In this project, I have assessed the performance of TCP Cubic and DCTCP in terms of throughput and average flow completion time. 
I have implemented a dumbbell topology in the ns-3 simulator. 
I have ran multiple experiments to evaluate the performance of both TCP versions for the given metrics. 
I have tried to demonstrate how well these two protocols coexist with each other and which one performs better in terms of responding to the congestion in the network.

## Measurement Metrics
- **Throughput** tells how much data is transferred per unit time from source to destination over a given period of time. Its unit is bits per second (bps).
- **Average Flow Completion Time** measures the time taken by the sender to send the desired amount of data to the receiver. It is measured in seconds

## Topology
![Dumbbell Topology](https://github.com/sharathKV/TCP-Analysis/blob/master/dumbbell-topology.png)

## Experiments
- S1 sends traffic to D1 using TCP Cubic, S2 and D2 are not used in this experiment
- S1 sends traffic to D1 and S2 sends traffic to D2, both senders will use TCP Cubic and start sending data to respective destinations simultaneously
- S1 sends traffic to D1 using DCTCP, S2 and D2 are not used in this experiment 
- S1 sends traffic to D1 and S2 sends traffic to D2, Both senders will use DCTCP and start sending data to respective destinations simultaneously
- S1 sends traffic to D1 using TCP Cubic whereas S2 sends traffic to D2 using DCTCP, both senders will start sending data to respective destinations simultaneously
