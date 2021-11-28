# Design Document for Exhaustive Evaluation of TCP-LP in WiFi Environment.


## Overview of TCP-lp :

<p> 
  In this Project, we are evaluating TCP Low Priority (TCP-LP), a distributed algorithm whose goal is to utilize only the excess network bandwidth as compared to the "fair share" of bandwidth as targeted by TCP. The key mechanisms unique to TCP-LP congestion control are the use of one-way packet delays for congestion indications and a TCP-transparent congestion avoidance policy. Our simulation results show that: 
  <ul>
    <li>TCP-LP is largely non-intrusive to TCP traffic.</li>
    <li>both single and aggregate TCP-LP flows are able to successfully utilize excess network bandwidth;
       moreover, multiple TCP-LP flows share excess bandwidth fairly.
    <li> substantial amounts of excess bandwidth are available to low-priority class, even in the presence of "greedy" TCP flows.</li>
     <li> the response times of web connections in the best-effort class decrease by up to 90% when long-lived bulk data transfers use TCP-LP rather than TCP.</li>
     </ul>
  
</p>

<br />

<p>
  This project aims to evaluate the performance of TCP-LP in WiFi environments, including Gigabit WiFi, with and without Rate Adaptation.
</p>



## What we wanted to do

Clearly, the goal of this assignment is to come up with at least one to two exhaustive evaluation examples of programmes for analysing how TCP-LP performs in wireless environments.We have planned to come up with examples of programmes which are scalable in nature. Users can pass Command Line Arguments before running the programme to simulate for the desired simulation time, the desired rate adaptation algorithm and error rate model.
Finally, calculating Throughput and generating corresponding plots for evaluation purposes for the different command line arguments example for different rate adaptation algorithms.
The Link Delays and Link Rate we did not specify in below images as that will be dynamic in nature and will depend upon the value entered by user
The Evaluation Examples Experiments are planned to carry out on 802.11 b/g and 802.11ac Gigabit Wifi Standards.
<b r/>

### Topology Design used for evaluation :
 
 <p>


  
</p>

<br />

<ol>
  <li> pRp topology  <br /> 
    <img src = "https://github.com/Vivekumar3110/TCP-LP-in-WiFi-environment/blob/tcp_lp/Topology-images/pRp.png"> <br /> 
    <br />
    <p>In this topology,there are 2 station connected to same AP).
      <b>We have implemented this topology to evaluate tcp-lp. Code is present in scrach/tcp_lp file named <a href="https://github.com/Vivekumar3110/TCP-LP-in-WiFi-environment/blob/tcp_lp/scratch/tcp_lp/pRp_tcp-lp.cc">pRp_tcp-lp.cc</a>  which is sucessfully running.</b> 
    </p>
    <br />
  </li>
  <li> Adhoc Network topology  <br /> 
    <img src = "https://github.com/Vivekumar3110/TCP-LP-in-WiFi-environment/blob/tcp_lp/Topology-images/Ad-Hoc%20Network.drawio.png"> <br /> 
    <br />
    <p>In this topology,there are 6 nodes and two nodes are connected by  P2P link. And all these 3 P2P link is connected to WIFI.
      <b>We have implemented this topology to evaluate tcp-lp.Code is present in scrach/tcp_lp file named <a href="https://github.com/Vivekumar3110/TCP-LP-in-WiFi-environment/blob/tcp_lp/scratch/tcp_lp/adhoc_topology_tcp-lp.cc">Adhoc_topology_tcp-lp.cc</a> which is sucessfully running.</b> 
    </p>
    <br />
  </li>
  
      
  <li> Wireless dumbell topology  <br /> 
    <img src = "https://github.com/Vivekumar3110/TCP-LP-in-WiFi-environment/blob/tcp_lp/Topology-images/dumbell.jpeg"> <br /> 
    <br />
    <p>This is a Simple Dumbell Topology having 3 STA connected to a AP and another 3 nodes  at right side  connected to router via P2P link. This topology is inspired from <a href="https://datatracker.ietf.org/doc/html/draft-irtf-iccrg-tcpeval">here</a>.
    </p>
    <br />
  </li>
  <li> Tree topology  <br /> 
    <img src = "https://github.com/Vivekumar3110/TCP-LP-in-WiFi-environment/blob/tcp_lp/Topology-images/tree.jpeg"> <br /> 
    <br />
    <p>This is a treeTopology having tree like structure.In this topology,R1,R2,R3.......R10 are different routers/APs  having 2 STA connected to R9 and R1 as Source STA and Destination STA respectively.But we could not implement this topology.This topology is inspired from <a href="https://www.ijert.org/research/performance-evaluation-of-transmission-control-protocol-tcp-on-different-topologies-by-varying-impairments-IJERTCONV5IS20007.pdf">here</a>.
    </p>
    <br />
  </li>
 </ol>






## References :

<ol>
  <li> <a href="http://ieeexplore.ieee.org/document/6814737/"> Less-than-Best-Effort Service for Community Wireless Networks: Challenges at Three Layers </a>  </li>
  <li> <a href="https://www.researchgate.net/publication/257517254_Exploration_and_evaluation_of_traditional_TCP_congestion_control_techniques" > Exploration and evaluation of traditional TCP congestion control techniques </a>  </li>
  <li> <a href="https://datatracker.ietf.org/doc/html/draft-irtf-iccrg-tcpeval"> Common TCP Evaluation Suite draft-irtf-iccrg-tcpeval-01 </a> </li>
  <li> <a href="https://www.nsnam.org/docs/models/html/wifi-design.html"> Wi-Fi architecture in ns-3 </a> </li>
  <li> <a href="https://www.nsnam.org/docs/models/html/wifi-user.html"> User documentation for Wi-Fi simulations using ns-3 </a> </li>
  <li> <a href="https://www.ijert.org/performance-evaluation-of-transmission-control-protocol-tcp-on-different-topologies-by-varying-impairments"> Performance Evaluation of Transmission Control Protocol (TCP) on Different Topologies by Varying Impairments </a> </li>
</ol>

