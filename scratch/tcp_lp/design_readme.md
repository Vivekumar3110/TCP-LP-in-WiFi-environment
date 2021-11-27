# Planning/Design Document for Exhaustive Evaluation of TCP-LP in WiFi Environment.


## Project Overview :

<p> 
  In this Project, we are evaluating TCP Low Priority (TCP-LP), a distributed algorithm whose goal is to utilize only the excess network bandwidth as compared to the "fair share" of bandwidth as targeted by TCP. The key mechanisms unique to TCP-LP congestion control are the use of one-way packet delays for congestion indications and a TCP-transparent congestion avoidance policy. Our simulation results show that: (1) TCP-LP is largely non-intrusive to TCP traffic; (2) both single and aggregate TCP-LP flows are able to successfully utilize excess network bandwidth; moreover, multiple TCP-LP flows share excess bandwidth fairly; (3) substantial amounts of excess bandwidth are available to low-priority class, even in the presence of "greedy" TCP flows; (4) the response times of web connections in the best-effort class decrease by up to 90% when long-lived bulk data transfers use TCP-LP rather than TCP.
  
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


The required arguments for each programe can be accesible via `--help` flag as proper argument message will be display for better understanding.

Example : 

    ./waf --run "<tcplp-evaluation-filename> --simulationTime=300s --rateAdaptationAlgo=aarf errorRateModel=yansErrorRate"
    
For Running with default arguments just type following: 

    ./waf --run  <tcplp-evaluation-filename> 
    
Finally, calculating Throughput and generating corresponding plots for evaluation purposes for the different command line arguments example for different rate adaptation algorithms.

The Link Delays and Link Rate we did not specify in below images as that will be dynamic in nature and will depend upon the value entered by user (as mentioned in above section).

The Evaluation Examples Experiments are planned to carry out on 802.11 b/g and 802.11ac Gigabit Wifi Standards.
<b r/>

## Exhaustive Evaluation Examples ( Topology Design ) :
 
 <p>
The Images for the topology are created by team itself by use of online available tool  : https://app.diagrams.net/  

  
</p>

<br />

<ol>
  <li>  Simple pRp wireless network Tolpology <br />
   <img src = "https://github.com/Vivekumar3110/TCP-LP-in-WiFi-envioronment/"> <br />
   <p> This is an simple node(STA)-AP-node(STA) Topology. The STAs will be configured to have a mobility model helping simulator to calculate received signal.
     </p>
    <br />
  </li>
      
  <li> Wireless dumbell topology  <br /> <img src = ""> <br />
    <p>This is a Simple Dumbell Topology having 3 STA (which will be configured to have count decided during runtime) connected to a AP and another 3 nodes (which will be configured to have count decided during runtime) at right side  connected to router via P2P link. This topology is inspired from <a href="https://datatracker.ietf.org/doc/html/draft-irtf-iccrg-tcpeval">here</a>.
    </p>
    <br />
  </li>
 </ol>




## Timelines :
<br />

  <table>
    <thead>
      <tr>
        <th>Week</th>
        <th>Task</th>
      </tr>
    </thead>
    <tbody>
        <tr>
            <td>Week 1</td>
            <td>
              <ul>
                <li> Revising ns3 documentation.</li>
                <li> Reading helper classes. </li>
                <li> Understanding code-base for WiFi module a listed in References. </li>
                <li> Implementation will be Initiated.</li>
              </ul>
          </td>
        </tr>
        <tr>
            <td>Week 2</td>
           <td>
              <ul>
                <li> Starting to work with simple P-R-P, Simple dumbell and Star. </li>
                <li> Analyze performance measuring throughput and generating graphs. </li>
              </ul>
          </td>
        </tr>
      <tr>
            <td>Week 3</td>
           <td>
              <ul>
                <li> Implementing the rest mentioned topologies.</li>
                <li> Followed by analyzing the performance of TCP-LP for different Rate Adaptation Algorithms and generating plots. </li>
              </ul>
          </td>
        </tr>
      <tr>
            <td>Week 4</td>
           <td>
              <ul>
                <li> Working on Documentation of all those topologies stating the configuration done. </li>
              </ul>
          </td>
        </tr>
    </tbody>
  </table>

<br />

## References :

<ol>
  <li> <a href="http://ieeexplore.ieee.org/document/6814737/"> Less-than-Best-Effort Service for Community Wireless Networks: Challenges at Three Layers </a>  </li>
  <li> <a href="https://www.researchgate.net/publication/257517254_Exploration_and_evaluation_of_traditional_TCP_congestion_control_techniques" > Exploration and evaluation of traditional TCP congestion control techniques </a>  </li>
  <li> <a href="https://datatracker.ietf.org/doc/html/draft-irtf-iccrg-tcpeval"> Common TCP Evaluation Suite draft-irtf-iccrg-tcpeval-01 </a> </li>
  <li> <a href="https://www.nsnam.org/docs/models/html/wifi-design.html"> Wi-Fi architecture in ns-3 </a> </li>
  <li> <a href="https://www.nsnam.org/docs/models/html/wifi-user.html"> User documentation for Wi-Fi simulations using ns-3 </a> </li>
</ol>
