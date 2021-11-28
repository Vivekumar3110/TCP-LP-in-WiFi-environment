# Design Document for Exhaustive Evaluation of TCP-LP in WiFi Environment.


## Overview :

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



## Goals and Deliverables :

Clearly, the goal of this assignment is to come up with at least one to two exhaustive evaluation examples of programmes for analysing how TCP-LP performs in wireless environments (WLAN/Wifi).

We have planned to come up with examples of programmes which are scalable in nature. Users can pass Command Line Arguments before running the programme to simulate (say)
<ul>
 <li> For the desired simulation time</li>
 <li> For the desired rate adaptation algorithm </li>
 <li> For the desired error rate model/mobility </li>
 <li> For the desired number of nodes in BSS (in some of the programmes), </li>
 <li> For linkrate and linkdelay in some cases, e.t.c. </li>
</ul>



    
Finally, calculating Throughput and generating corresponding plots for evaluation purposes for the different command line arguments example for different rate adaptation algorithms.

The Link Delays and Link Rate we did not specify in below images as that will be dynamic in nature and will depend upon the value entered by user (as mentioned in above section).

The Evaluation Examples Experiments are planned to carry out on 802.11 b/g and 802.11ac Gigabit Wifi Standards.
<b r/>

## Exhaustive Evaluation Examples ( Topology Design ) :
 
 <p>


  
</p>

<br />

<ol>
  
      
  <li> Wireless dumbell topology  <br /> 
    <img src = "https://github.com/Vivekumar3110/TCP-LP-in-WiFi-environment/blob/tcp_lp/Topology-images/dumbell.jpeg"> <br /> 
    <br />
    <p>This is a Simple Dumbell Topology having 3 STA connected to a AP and another 3 nodes  at right side  connected to router via P2P link. This topology is inspired from <a href="https://datatracker.ietf.org/doc/html/draft-irtf-iccrg-tcpeval">here</a>.
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
</ol>

