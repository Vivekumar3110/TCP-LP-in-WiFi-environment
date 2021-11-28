/*Vivek Kumar
                sta01----AP0---sta02                           
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
#include "ns3/command-line.h"
#include "ns3/wifi-module.h"
using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("TCP-LP-SIMPLE-BSS");



// FlowMonitor::FlowStatsContainer flowmonstatistics;
uint32_t prev = 0;

// Calculate goodput: Recieved Bytes are used for goodput calculation. 

static void
ThroughPut (Ptr<FlowMonitor> monitor)
{
 
  
  FlowMonitor::FlowStatsContainer flowmonstatistics = monitor->GetFlowStats ();
  std::ofstream througput ("ThroughPutLP.dat", std::ios::out | std::ios::app);
  througput <<  Now ().GetSeconds () << " " << 8 * (flowmonstatistics.begin ()->second.rxBytes - prev) / (1e6 * 0.150) << std::endl;
  std::cout <<  "Time" << Now ().GetSeconds () << " : Throughput " << ( (flowmonstatistics.begin ()->second.rxBytes - prev) * (double) 8 /1e6  ) / (double) 0.150 << std::endl;

  prev = flowmonstatistics.begin ()->second.rxBytes;
  Simulator::Schedule (Seconds (0.200), &ThroughPut, monitor);
  return ;
}



int main (int argc, char *argv [])
{
    uint16_t port = 47811;
    std::string tcpTypeId = "TcpLp";
    bool enablePcap = false;
    Time stopTime = Seconds (200);
    std::string raa = "ns3::AarfWifiManager";    /*raa Rate Adaptation Algorithm */

    CommandLine cmd (_FILE_);
    cmd.AddValue ("stopTime", "Stop time for simulation", stopTime);
    cmd.AddValue ("enablePcap", "Enable/Disable pcap generation of file", enablePcap);
    cmd.AddValue ("rateAdaptionAlgorithm", "Enter error rate adaptio algorithm to be used for wifi nodes", raa);
    cmd.Parse (argc, argv);


    // Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::TcpLp"));
    Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (std::string ("ns3::") + tcpTypeId)));
    Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (1500));


    NodeContainer stations;
    stations.Create (2);

    NodeContainer ap;
    ap.Create (1);


 

    WifiHelper wifi;
    wifi.SetStandard (WIFI_STANDARD_80211b);
    wifi.SetRemoteStationManager (raa);

    WifiMacHelper mac;


    // mac.SetType ("ns3::AdhocWifiMac",
    //             "Ssid", SsidValue ( Ssid ("TCP-LP-Vivek")));


    
    YansWifiChannelHelper channelall = YansWifiChannelHelper::Default ();;
    YansWifiPhyHelper channelphy = YansWifiPhyHelper::Default ();; 

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

  
    mac.SetType ("ns3::StaWifiMac",
                   "ActiveProbing", BooleanValue (true),
                   "Ssid", SsidValue ( Ssid ("TCP-LP-Vivek")));


    NetDeviceContainer sta0 = wifi.Install (channelphy, mac, stations.Get (0) );

    NetDeviceContainer sta1 = wifi.Install (channelphy, mac, stations.Get (1) );



    // setup ap --> AP0.
    mac.SetType ("ns3::ApWifiMac",
                    "Ssid", SsidValue ( Ssid ("TCP-LP-Vivek")));
    NetDeviceContainer ap0 = wifi.Install (channelphy, mac, ap);



    MobilityHelper mobility;
    mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    mobility.Install (stations);
    mobility.Install (ap);

    InternetStackHelper stack;
    stack.Install (ap);
    stack.Install (stations);

  Ipv4AddressHelper ipv4;
  NetDeviceContainer bss;
  bss.Add (sta0);
  bss.Add (sta1);
  bss.Add (ap0);

  ipv4.SetBase ("10.0.1.0", "255.255.255.0");

  Ipv4InterfaceContainer iifc = ipv4.Assign (bss);

//   Ipv4InterfaceContainer sta0Interfaces.Add (iifc.Get(0));


//   // ipv4.SetBase ("10.0.2.0", "255.255.255.0");

//   Ipv4InterfaceContainer sta1Interfaces.Add( iifc.Get(1));


//   // ipv4.SetBase ("10.0.0.0", "255.255.255.0");

//   Ipv4InterfaceContainer ap0Interfaces.Add(  iifc.Get(2) );
  ipv4.NewNetwork ();





  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

//   PacketSocketAddress socket;
//   socket.SetSingleDevice (wifiNetDevices.Get (0)->GetIfIndex ());
//   socket.SetPhysicalAddress (wifiNetDevices.Get (1)->GetAddress ());
//   socket.SetProtocol (1);

//   OnOffHelper onoff ("ns3::PacketSocketFactory", Address (socket));
//   onoff.SetConstantRate (DataRate (60000000));
//   onoff.SetAttribute ("PacketSize", UintegerValue (2000));

//   ApplicationContainer apps = onoff.Install (stations.Get (0));
//   apps.Start (Seconds (0.5));
//   apps.Stop (Seconds (250.0));


//   // BulkSendHelper source ("ns3::TcpSocketFactory", InetSocketAddress (middleInterfaces.GetAddress (1), port));
//   BulkSendHelper source ("ns3::TcpSocketFactory", Address ());
//   source.SetAttribute ("MaxBytes", UintegerValue (0));


// //////////////////////////////////////////////////////////////////////////////////////////////
//   NodeContainer topBottomNodes;
//   topBottomNodes.Add (ap.Get (1));
//   topBottomNodes.Add (ap.Get (2));

//   ApplicationContainer sourceApp = source.Install (topBottomNodes);

//   AddressValue sourceaddress (InetSocketAddress (bottomInterfaces.GetAddress (0), 8080));
//   source.SetAttribute ("Remote", sourceaddress);
//   sourceApp.Add (source.Install (ap.Get (0)));

//   // AddressValue sourceaddress_second (InetSocketAddress (topInterfaces.GetAddress (0), 8080));
//   // source.SetAttribute ("Remote", sourceaddress_second);
//   // sourceApp.Add (source.Install (ap.Get (2)));
//   sourceApp.Start (Seconds (0.0));
//   sourceApp.Stop (stopTime);

// PacketSinkHelper sink ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port));
//   ApplicationContainer sinkApps = sink.Install (ap.Get (1));
//   sinkApps.Start (Seconds (0.0));
//   sinkApps.Stop (stopTime);

  //BulksendApplication on Left side STAS/nodes
  BulkSendHelper source ("ns3::TcpSocketFactory", Address ());
  source.SetAttribute ("MaxBytes", UintegerValue (1024*1000));

  ApplicationContainer sourceApps;


  AddressValue sourceaddress (InetSocketAddress (iifc.GetAddress (1), port));
  source.SetAttribute ("Remote", sourceaddress);
  sourceApps.Add (source.Install (stations.Get (0)));

  sourceApps.Start (Seconds (0.0));
  sourceApps.Stop (stopTime);

  //PacketsinkHelper on right side STA nodes
  PacketSinkHelper sinkhelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), port));
  ApplicationContainer sinkAppsNodes;
  

  sinkAppsNodes.Add (sinkhelper.Install (stations.Get (1)));
    
    


   sinkAppsNodes.Start (Seconds (0.0));
   sinkAppsNodes.Stop (stopTime);


  AnimationInterface anim("tcpLP-BSS.xml");
  anim.SetConstantPosition(ap.Get(0),50.0 - 30.0,50.0);
  anim.SetConstantPosition(stations.Get(0),50.0-20.0,50.0);
  anim.SetConstantPosition(stations.Get(1),85.0,85.0);


 if (enablePcap)
    {
        channelphy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11_RADIO);
        channelphy.EnablePcapAll ("wifiLPNodes-BSS", true);
    }

if (enablePcap)
{
  std::cout<<"PCAP is Enabled"<<std::endl;
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
