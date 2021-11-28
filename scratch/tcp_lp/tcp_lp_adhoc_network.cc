/*


                               n3
                              /
                       P2P   / 
                            /
                           /
      P2P                n2

n0-----------n1      WIFI

                         n4
                           \
                            \ 
                        P2P  \ 
                              \
                               \
                                n5

*/



#include <iostream>
#include "ns3/netanim-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/traffic-control-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/wifi-module.h"
using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("TCP-LP-WIFI-EVALUATION");



FlowMonitor::FlowStatsContainer flowmonstatistics;
uint32_t prev = 0;

// Calculate goodput: Recieved Bytes are used for goodput calculation. 

static void
ThroughPut (Ptr<FlowMonitor> monitor)
{
 
  flowmonstatistics = monitor->GetFlowStats ();
  std::ofstream througput ("ThroughPutLP.dat", std::ios::out | std::ios::app);
  througput <<  Now ().GetSeconds () << " " << 8 * (flowmonstatistics.begin ()->second.rxBytes - prev) / (1e6 * 0.150) << std::endl;
  prev = flowmonstatistics.begin ()->second.rxBytes;
  Simulator::Schedule (Seconds (0.150), &ThroughPut, monitor);
  return ;
}



int main (int argc, char *argv [])
{
    uint16_t port = 50001;
    std::string tcpTypeId = "TcpLp";
    bool enablePcap = false;
    Time stopTime = Seconds (20);
    std::string raa = "ns3::ConstantRateWifiManager";    /*raa Rate Adaptation Algorithm */


    CommandLine cmd (_FILE_);
    cmd.AddValue ("stopTime", "Stop time for simulation", stopTime);
    cmd.AddValue ("enablePcap", "Enable/Disable pcap generation of file", enablePcap);
    cmd.AddValue ("rateAdaptionAlgorithm", "Enter error rate adaptio algorithm to be used for wifi nodes", raa);
    cmd.Parse (argc, argv);


    Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::TcpLp"));
    // Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (std::string ("ns3::") + tcpTypeId)))


    NodeContainer wirelessNodes;
    wirelessNodes.Create (3);

    NodeContainer wiredNodes;
    wiredNodes.Create (3);


    PointToPointHelper tophelper;
    tophelper.SetDeviceAttribute    ("DataRate", StringValue ("50Mbps"));
    tophelper.SetChannelAttribute   ("Delay", StringValue ("2ms"));

    PointToPointHelper bottomhelper;
    //middleInterfacesmiddleInterfaces
    bottomhelper.SetDeviceAttribute    ("DataRate", StringValue ("50Mbps"));
    bottomhelper.SetChannelAttribute   ("Delay", StringValue ("1ms"));


    PointToPointHelper middlehelper;
    middlehelper.SetDeviceAttribute    ("DataRate", StringValue ("50Mbps"));
    middlehelper.SetChannelAttribute   ("Delay", StringValue ("3ms"));


    NetDeviceContainer topNetDevices = tophelper.Install (wiredNodes.Get (1), wirelessNodes.Get (1));
    NetDeviceContainer bottomNetDevices = bottomhelper.Install(wirelessNodes.Get (2),wiredNodes.Get (2));
    NetDeviceContainer middleNetDevices = middlehelper.Install(wirelessNodes.Get (0),wiredNodes.Get (0));



    WifiHelper wifi;
    wifi.SetStandard (WIFI_STANDARD_80211b);
    wifi.SetRemoteStationManager (raa, "DataMode", StringValue ("DsssRate11Mbps"), "ControlMode", StringValue ("DsssRate11Mbps"));

    WifiMacHelper mac;
    mac.SetType ("ns3::AdhocWifiMac");


    
    YansWifiChannelHelper channelall ;
    YansWifiPhyHelper channelphy; 
    channelall.AddPropagationLoss ("ns3::FriisPropagationLossModel", "Frequency", DoubleValue (5e9));
    channelphy.SetChannel (channelall.Create ());
    channelphy.SetErrorRateModel ("ns3::YansErrorRateModel");


    // YansWifiChannelHelper channelbottom ;
    // YansWifiPhyHelper channelphybottom; 
    // channelbottom.AddPropagationLoss ("ns3::FriisPropagationLossModel", "Frequency", DoubleValue (5e9));
    // channelphybottom.SetChannel (channelphybottom.Create ());
    // channelphybottom.SetErrorRateModel ("ns3::YansErrorRateModel");
    // channelphybottom.SetChannel (channelbottom.Create ());
    // YansWifiChannelHelper channelmiddle ;
    // YansWifiPhyHelper channelphymiddle; 
    // channelmiddle.AddPropagationLoss ("ns3::FriisPropagationLossModel", "Frequency", DoubleValue (5e9));
    // channelphymiddle.SetChannel (channelmiddle.Create ());
    // channelphymiddle.SetErrorRateModel ("ns3::YansErrorRateModel");
    // channelphymiddle.SetChannel (channelmiddle.Create ());

    


    NetDeviceContainer wifiNetDevices;
    wifiNetDevices = wifi.Install (channelphy, mac, wirelessNodes);

    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install (wirelessNodes);

    InternetStackHelper stack;
    stack.Install (wiredNodes);
    stack.Install (wirelessNodes);

  Ipv4AddressHelper ipv4;

  ipv4.SetBase ("10.0.0.0", "255.255.255.0");

  Ipv4InterfaceContainer topInterfaces = ipv4.Assign (topNetDevices);
  ipv4.NewNetwork ();

  Ipv4InterfaceContainer bottomInterfaces = ipv4.Assign (bottomNetDevices);
  ipv4.NewNetwork ();

  Ipv4InterfaceContainer middleInterfaces = ipv4.Assign (middleNetDevices);
  ipv4.NewNetwork ();




  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  BulkSendHelper source ("ns3::TcpSocketFactory", InetSocketAddress (middleInterfaces.GetAddress (1), port));
  source.SetAttribute ("MaxBytes", UintegerValue (0));


//////////////////////////////////////////////////////////////////////////////////////////////
  NodeContainer topBottomNodes;
  topBottomNodes.Add (wiredNodes.Get (1));
  topBottomNodes.Add (wiredNodes.Get (2));
  ApplicationContainer sourceApp = source.Install (topBottomNodes);
  sourceApp.Start (Seconds (0.0));
  sourceApp.Stop (stopTime);

PacketSinkHelper sink ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port));
  ApplicationContainer sinkApps = sink.Install (wiredNodes.Get (0));
  sinkApps.Start (Seconds (0.0));
  sinkApps.Stop (stopTime);


  AnimationInterface anim("tcpLP.xml");
  anim.SetConstantPosition(wiredNodes.Get(0),50.0 - 30.0,50.0);
  anim.SetConstantPosition(wiredNodes.Get(0),70.0,70.0);
  anim.SetConstantPosition(wiredNodes.Get(0),90.0,90.0);
  anim.SetConstantPosition(wirelessNodes.Get(0),50.0-20.0,50.0);
  anim.SetConstantPosition(wirelessNodes.Get(0),65.0,65.0);
  anim.SetConstantPosition(wirelessNodes.Get(1),85.0,85.0);


 if (enablePcap)
    {
        channelphy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11_RADIO);
        channelphy.EnablePcapAll ("wifiLPNodes", true);
    }

  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll ();

  Simulator::Schedule (Seconds (0), &ThroughPut, monitor);

  Simulator::Stop (stopTime );

  Simulator::Run ();
  Simulator::Destroy ();

  double averageTHroughPut = double(8 * (prev)) / double(1e6 * (100));
  std::cout << "\nAverage ThroughPUT --> : " << averageTHroughPut  << " Mbit/s" <<  " Total Bytes transfered" <<std::endl<<double(prev)/double(1e6);
  return 0;


}
