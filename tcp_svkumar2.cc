 #include <iostream>
 #include <iomanip>
 
 #include "ns3/core-module.h"
 #include "ns3/network-module.h"
 #include "ns3/internet-module.h"
 #include "ns3/point-to-point-module.h"
 #include "ns3/applications-module.h"
 #include "ns3/traffic-control-module.h"
 #include "ns3/bulk-send-helper.h"
 #include "ns3/bulk-send-application.h"
 #include "assert.h"
 #include "ns3/flow-monitor-module.h"
 using namespace ns3;
 
  int main (int argc, char *argv[])
  {
 std::string tcpTypeId = "TcpBic";
 std::string tcpTypeId_d ="TcpDctcp";
 std::string rate = "1Gbps"; // P2P link
 uint32_t maxBytes=500000000;//500MB
        
  std::ofstream myFile("tcp_svkumar2.csv");
	   float tp,ct;
	   float t1,t2,t3,t7,t8,t9,t10,t11,t12,t19,t20,t21,t25,t26,t27,t28,t29,t30,t37,t38,t39,t40,t41,t42;
	  float tp1,tp2,tp3,tp7,tp8,tp9,tp10,tp11,tp12,tp19,tp20,tp21,tp25,tp26,tp27,tp28,tp29,tp30,tp37,tp38,tp39,tp40,tp41,tp42;
	  float t_avg1,t_avg2,t_avg3,t_avg4,t_avg5,t_avg6,t_avg7,t_avg8;
	   float a_avg1,a_avg2,a_avg3,a_avg4,a_avg5,a_avg6,a_avg7,a_avg8;
float a_sd1,a_sd2,a_sd3,a_sd4,a_sd5,a_sd6,a_sd7,a_sd8;
float t_sd1,t_sd2,t_sd3,t_sd4,t_sd5,t_sd6,t_sd7,t_sd8;

 
 CommandLine cmd;
      cmd.AddValue ("tcpTypeId", "ns-3 TCP TypeId", tcpTypeId);
 cmd.AddValue ("rate", "P2P data rate in bps", rate);
 cmd.Parse (argc, argv);
 Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::" + tcpTypeId));
 
 NodeContainer c; // ALL Nodes
 c.Create(6);

 NodeContainer n0n4 = NodeContainer (c.Get (0), c.Get (4));
 NodeContainer n1n4 = NodeContainer (c.Get (1), c.Get (4));
 NodeContainer n2n5 = NodeContainer (c.Get (2), c.Get (5));
 NodeContainer n3n5 = NodeContainer (c.Get (3), c.Get (5));
 NodeContainer n4n5 = NodeContainer (c.Get (4), c.Get (5));
 
 InternetStackHelper internet;
      internet.Install (c);
 
 PointToPointHelper p2p;
 p2p.SetDeviceAttribute ("DataRate", StringValue (rate));

 NetDeviceContainer d0d4 = p2p.Install (n0n4);
 NetDeviceContainer d1d4 = p2p.Install (n1n4);
 NetDeviceContainer d4d5 = p2p.Install (n4n5);
 NetDeviceContainer d2d5 = p2p.Install (n2n5);
 NetDeviceContainer d3d5 = p2p.Install (n3n5);
 
 Ipv4AddressHelper ipv4;
 ipv4.SetBase ("10.1.1.0", "255.255.255.0");
 Ipv4InterfaceContainer i0i4 = ipv4.Assign (d0d4);

 ipv4.SetBase ("10.1.2.0", "255.255.255.0");
 Ipv4InterfaceContainer i1i4 = ipv4.Assign (d1d4);

 ipv4.SetBase ("10.1.3.0", "255.255.255.0");
 Ipv4InterfaceContainer i4i5 = ipv4.Assign (d4d5);

 ipv4.SetBase ("10.1.4.0", "255.255.255.0");
 Ipv4InterfaceContainer i2i5 = ipv4.Assign (d2d5);

 ipv4.SetBase ("10.1.5.0", "255.255.255.0");
 Ipv4InterfaceContainer i3i5 = ipv4.Assign (d3d5);
 
 Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
 

//Experiment 1

 // TCP connfection from N0 to N2
//creating sink at n2
 uint16_t sinkPort = 8080;          
 Address sinkAddress (InetSocketAddress (i2i5.GetAddress (0), sinkPort)); // interface of n2
 PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
 ApplicationContainer sinkApps = packetSinkHelper.Install (c.Get (2)); //n2 as sink
 
 sinkApps.Start (Seconds (0.));
 sinkApps.Stop (Seconds (10.0));

        //creating source at n0
       
BulkSendHelper client ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort));
        client.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps1=client.Install(c.Get(0));
clientApps1.Start (Seconds (1.));

         clientApps1.Stop (Seconds(10.0));


//2
 uint16_t sinkPortq = 8081;          
 Address sinkAddressq (InetSocketAddress (i2i5.GetAddress (0), sinkPortq)); // interface of n2
 PacketSinkHelper packetSinkHelperq ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPortq));
 ApplicationContainer sinkAppsq = packetSinkHelperq.Install (c.Get (2)); //n2 as sink
 sinkAppsq.Start (Seconds (11.));
 sinkAppsq.Stop (Seconds (21.0));

        //creating source at n0
       
BulkSendHelper clientq ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPortq));
        clientq.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps1q=clientq.Install(c.Get(0));
clientApps1q.Start (Seconds (12.));

         clientApps1q.Stop (Seconds(21.0));
//3
 uint16_t sinkPortw = 8082;          
 Address sinkAddressw (InetSocketAddress (i2i5.GetAddress (0), sinkPortw)); // interface of n2
 PacketSinkHelper packetSinkHelperw ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPortw));
 ApplicationContainer sinkAppsw = packetSinkHelperw.Install (c.Get (2));
 sinkAppsw.Start (Seconds (22.));
 sinkAppsw.Stop (Seconds (32.0));

        //creating source at n0
       
BulkSendHelper clientw ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPortw));
        clientw.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps1w=clientw.Install(c.Get(0));
clientApps1w.Start (Seconds (23.));

         clientApps1w.Stop (Seconds(32.0));

//Experiment 2

//1.	
	
// TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort2 = 8090;           
	  Address sinkAddress2 (InetSocketAddress (i2i5.GetAddress (0), sinkPort2)); // interface of n2
	  PacketSinkHelper packetSinkHelper2 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort2));
	  ApplicationContainer sinkApps2 = packetSinkHelper2.Install (c.Get (2)); //n2 as sink
	 // sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps2.Start (Seconds ( 33.));
	  sinkApps2.Stop (Seconds ( 43.0));

        //creating source at n0
        
	BulkSendHelper client2 ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort2)); 
//S1 sends traffic to D1 only
        client2.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps2=client2.Install(c.Get(0));
	clientApps2.Start (Seconds ( 34.));
	
         clientApps2.Stop (Seconds(43.0));

	//TCP connection from N1 to N3
         //creating sink at N3
	  uint16_t sinkPort22 = 8091;           
	  Address sinkAddress22 (InetSocketAddress (i3i5.GetAddress (0), sinkPort22)); // interface of n2
	  PacketSinkHelper packetSinkHelper22 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort22));
	  ApplicationContainer sinkApps22 = packetSinkHelper22.Install (c.Get (3)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps22.Start (Seconds (33.));
	  sinkApps22.Stop (Seconds (43.0));

        //creating source at N1
        
	BulkSendHelper client22 ("ns3::TcpSocketFactory",InetSocketAddress (i3i5.GetAddress (0), sinkPort22)); 
//S1 sends traffic to D1 only
        client22.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps22=client22.Install(c.Get(1));
	clientApps22.Start (Seconds (34.));
	
         clientApps22.Stop (Seconds(43.0));

//2.

	// TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort2q = 8092;           
	  Address sinkAddress2q (InetSocketAddress (i2i5.GetAddress (0), sinkPort2q)); // interface of n2
	  PacketSinkHelper packetSinkHelper2q ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort2q));
	  ApplicationContainer sinkApps2q = packetSinkHelper2q.Install (c.Get (2)); //n2 as sink
	 // sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps2q.Start (Seconds ( 44.));
	  sinkApps2q.Stop (Seconds ( 54.0));

        //creating source at n0
        
	BulkSendHelper client2q ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort2q)); 
//S1 sends traffic to D1 only
        client2q.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps2q=client2q.Install(c.Get(0));
	clientApps2q.Start (Seconds ( 45.));
	
         clientApps2q.Stop (Seconds(54.0));

	//TCP connection from N1 to N3
         //creating sink at N3
	  uint16_t sinkPort22q = 8093;           
	  Address sinkAddress22q (InetSocketAddress (i3i5.GetAddress (0), sinkPort22q)); // interface of n2
	  PacketSinkHelper packetSinkHelper22q ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort22q));
	  ApplicationContainer sinkApps22q = packetSinkHelper22q.Install (c.Get (3)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps22q.Start (Seconds (44.));
	  sinkApps22q.Stop (Seconds (54.0));

        //creating source at N1
        
	BulkSendHelper client22q ("ns3::TcpSocketFactory",InetSocketAddress (i3i5.GetAddress (0), sinkPort22q)); 
//S1 sends traffic to D1 only
        client22q.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps22q=client22q.Install(c.Get(1));
	clientApps22q.Start (Seconds (45.));
	
         clientApps22q.Stop (Seconds(54.0));

//.3
// TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort2w = 8094;           
	  Address sinkAddress2w (InetSocketAddress (i2i5.GetAddress (0), sinkPort2w)); // interface of n2
	  PacketSinkHelper packetSinkHelper2w ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort2w));
	  ApplicationContainer sinkApps2w = packetSinkHelper2w.Install (c.Get (2)); //n2 as sink
	 // sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps2w.Start (Seconds ( 55.));
	  sinkApps2w.Stop (Seconds ( 65.0));

        //creating source at n0
        
	BulkSendHelper client2w ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort2w)); 
//S1 sends traffic to D1 only
        client2w.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps2w=client2w.Install(c.Get(0));
	clientApps2w.Start (Seconds ( 56.));
	
         clientApps2w.Stop (Seconds(65.0));

	//TCP connection from N1 to N3
         //creating sink at N3
	  uint16_t sinkPort22w = 8094;           
	  Address sinkAddress22w (InetSocketAddress (i3i5.GetAddress (0), sinkPort22w)); // interface of n2
	  PacketSinkHelper packetSinkHelper22w ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort22w));
	  ApplicationContainer sinkApps22w = packetSinkHelper22w.Install (c.Get (3)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps22w.Start (Seconds (55.));
	  sinkApps22w.Stop (Seconds (65.0));

        //creating source at N1
        
	BulkSendHelper client22w ("ns3::TcpSocketFactory",InetSocketAddress (i3i5.GetAddress (0), sinkPort22w)); 
//S1 sends traffic to D1 only
        client22w.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps22w=client22w.Install(c.Get(1));
	clientApps22w.Start (Seconds (56.));
	
         clientApps22w.Stop (Seconds(65.0));


//Experiment 3
//1.
Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::" + tcpTypeId_d)); //Dctcp configuration

	  // TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort3 = 9050;           
	  Address sinkAddress3 (InetSocketAddress (i2i5.GetAddress (0), sinkPort3)); // interface of n2
	  PacketSinkHelper packetSinkHelper3 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort3));
	  ApplicationContainer sinkApps3 = packetSinkHelper3.Install (c.Get (2)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps3.Start (Seconds (66.)); //decide time
	  sinkApps3.Stop (Seconds (76.0));

        //creating source at n0
        
	BulkSendHelper client3 ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort3)); 
//S1 sends traffic to D1 only
        client3.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps3=client3.Install(c.Get(0));
	clientApps3.Start (Seconds (67.));
	
         clientApps3.Stop (Seconds(76.0));

//2.
	 // TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort3q = 9051;           
	  Address sinkAddress3q (InetSocketAddress (i2i5.GetAddress (0), sinkPort3q)); // interface of n2
	  PacketSinkHelper packetSinkHelper3q ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort3q));
	  ApplicationContainer sinkApps3q = packetSinkHelper3q.Install (c.Get (2)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps3q.Start (Seconds (77.)); //decide time
	  sinkApps3q.Stop (Seconds (87.0));

        //creating source at n0
        
	BulkSendHelper client3q ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort3q)); 
//S1 sends traffic to D1 only
        client3q.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps3q=client3q.Install(c.Get(0));
	clientApps3q.Start (Seconds (78.));
	
         clientApps3q.Stop (Seconds(87.0));
//3.
 // TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort3w = 9052;           
	  Address sinkAddress3w (InetSocketAddress (i2i5.GetAddress (0), sinkPort3w)); // interface of n2
	  PacketSinkHelper packetSinkHelper3w ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort3w));
	  ApplicationContainer sinkApps3w = packetSinkHelper3w.Install (c.Get (2)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps3w.Start (Seconds (88.)); //decide time
	  sinkApps3w.Stop (Seconds (98.0));

        //creating source at n0
        
	BulkSendHelper client3w ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort3w)); 
//S1 sends traffic to D1 only
        client3w.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps3w=client3w.Install(c.Get(0));
	clientApps3w.Start (Seconds (89.));
	
         clientApps3w.Stop (Seconds(98.0));

//Experiment 4

//1.

 // TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort4 = 9060;           
	  Address sinkAddress4 (InetSocketAddress (i2i5.GetAddress (0), sinkPort4)); // interface of n2
	  PacketSinkHelper packetSinkHelper4 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort4));
	  ApplicationContainer sinkApps4 = packetSinkHelper4.Install (c.Get (2)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps4.Start (Seconds (99.));
	  sinkApps4.Stop (Seconds (109.0));

        //creating source at n0
        
	BulkSendHelper client4 ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort4)); 
//S1 sends traffic to D1 only
        client4.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps4=client4.Install(c.Get(0));
	clientApps4.Start (Seconds (100.));
	
         clientApps4.Stop (Seconds(109.0));

	//TCP connection from N1 to N3
         //creating sink at N3
	  uint16_t sinkPort44 = 9061;           
	  Address sinkAddress44 (InetSocketAddress (i3i5.GetAddress (0), sinkPort44)); // interface of n2
	  PacketSinkHelper packetSinkHelper44 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort44));
	  ApplicationContainer sinkApps44 = packetSinkHelper44.Install (c.Get (3)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps44.Start (Seconds (99.));
	  sinkApps44.Stop (Seconds (109.0));

        //creating source at N1
        
	BulkSendHelper client44 ("ns3::TcpSocketFactory",InetSocketAddress (i3i5.GetAddress (0), sinkPort44)); 
//S1 sends traffic to D1 only
        client44.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps44=client44.Install(c.Get(1));
	clientApps44.Start (Seconds (100.));
	
         clientApps44.Stop (Seconds(109.0));
  
//2.

 // TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort4w = 9062;           
	  Address sinkAddress4w (InetSocketAddress (i2i5.GetAddress (0), sinkPort4w)); // interface of n2
	  PacketSinkHelper packetSinkHelper4w ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort4w));
	  ApplicationContainer sinkApps4w = packetSinkHelper4w.Install (c.Get (2)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps4w.Start (Seconds (110.));
	  sinkApps4w.Stop (Seconds (120.0));

        //creating source at n0
        
	BulkSendHelper client4w ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort4w)); 
//S1 sends traffic to D1 only
        client4w.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps4w=client4w.Install(c.Get(0));
	clientApps4w.Start (Seconds (111.));
	
         clientApps4w.Stop (Seconds(120.0));

	//TCP connection from N1 to N3
         //creating sink at N3
	  uint16_t sinkPort44w = 9063;           
	  Address sinkAddress44w (InetSocketAddress (i3i5.GetAddress (0), sinkPort44w)); // interface of n2
	  PacketSinkHelper packetSinkHelper44w ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort44w));
	  ApplicationContainer sinkApps44w = packetSinkHelper44w.Install (c.Get (3)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps44w.Start (Seconds (110.));
	  sinkApps44w.Stop (Seconds (120.0));

        //creating source at N1
        
	BulkSendHelper client44w ("ns3::TcpSocketFactory",InetSocketAddress (i3i5.GetAddress (0), sinkPort44w)); 
//S1 sends traffic to D1 only
        client44w.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps44w=client44w.Install(c.Get(1));
	clientApps44w.Start (Seconds (111.));
	
         clientApps44w.Stop (Seconds(120.0));
  
//3.

 // TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort4e = 9064;           
	  Address sinkAddress4e (InetSocketAddress (i2i5.GetAddress (0), sinkPort4e)); // interface of n2
	  PacketSinkHelper packetSinkHelper4e ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort4e));
	  ApplicationContainer sinkApps4e = packetSinkHelper4e.Install (c.Get (2)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps4e.Start (Seconds (121.));
	  sinkApps4e.Stop (Seconds (131.0));

        //creating source at n0
        
	BulkSendHelper client4e ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort4e)); 
//S1 sends traffic to D1 only
        client4e.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps4e=client4e.Install(c.Get(0));
	clientApps4e.Start (Seconds (122.));
	
         clientApps4e.Stop (Seconds(131.0));

	//TCP connection from N1 to N3
         //creating sink at N3
	  uint16_t sinkPort44e = 9065;           
	  Address sinkAddress44e (InetSocketAddress (i3i5.GetAddress (0), sinkPort44e)); // interface of n2
	  PacketSinkHelper packetSinkHelper44e ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort44e));
	  ApplicationContainer sinkApps44e = packetSinkHelper44e.Install (c.Get (3)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps44e.Start (Seconds (121.));
	  sinkApps44e.Stop (Seconds (131.0));

        //creating source at N1
        
	BulkSendHelper client44e ("ns3::TcpSocketFactory",InetSocketAddress (i3i5.GetAddress (0), sinkPort44e)); 
//S1 sends traffic to D1 only
        client44e.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps44e=client44e.Install(c.Get(1));
	clientApps44e.Start (Seconds (122.));
	
         clientApps44e.Stop (Seconds(131.0));
  
//Experiment 5
//1.
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::" + tcpTypeId));  //Cubic config

// TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort5 = 9075;           
	  Address sinkAddress5 (InetSocketAddress (i2i5.GetAddress (0), sinkPort5)); // interface of n2
	  PacketSinkHelper packetSinkHelper5 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort5));
	  ApplicationContainer sinkApps5 = packetSinkHelper5.Install (c.Get (2)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps5.Start (Seconds (132.));
	  sinkApps5.Stop (Seconds (142.0));

        //creating source at n0
        
	BulkSendHelper client5 ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort5)); 
//S1 sends traffic to D1 only
        client5.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps5=client5.Install(c.Get(0));
	clientApps5.Start (Seconds (133.));
	
         clientApps5.Stop (Seconds(142.0));

Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::" + tcpTypeId_d)); //Dctcp configuration

	//TCP connection from N1 to N3
         //creating sink at N3
	  uint16_t sinkPort55 = 9076;           
	  Address sinkAddress55 (InetSocketAddress (i3i5.GetAddress (0), sinkPort55)); // interface of n2
	  PacketSinkHelper packetSinkHelper55 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort55));
	  ApplicationContainer sinkApps55 = packetSinkHelper55.Install (c.Get (3)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps55.Start (Seconds (132.));
	  sinkApps55.Stop (Seconds (142.0));

        //creating source at N1
        
	BulkSendHelper client55 ("ns3::TcpSocketFactory",InetSocketAddress (i3i5.GetAddress (0), sinkPort55)); 
//S1 sends traffic to D1 only
        client55.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps55=client55.Install(c.Get(1));
	clientApps55.Start (Seconds (133.));
	
         clientApps55.Stop (Seconds(142.0));
//2.
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::" + tcpTypeId));  //Cubic config

// TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort5q = 9077;           
	  Address sinkAddress5q (InetSocketAddress (i2i5.GetAddress (0), sinkPort5q)); // interface of n2
	  PacketSinkHelper packetSinkHelper5q ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort5q));
	  ApplicationContainer sinkApps5q = packetSinkHelper5q.Install (c.Get (2)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps5q.Start (Seconds (143.));
	  sinkApps5q.Stop (Seconds (153.0));

        //creating source at n0
        
	BulkSendHelper client5q ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort5q)); 
//S1 sends traffic to D1 only
        client5q.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps5q=client5q.Install(c.Get(0));
	clientApps5q.Start (Seconds (144.));
	
         clientApps5q.Stop (Seconds(153.0));

Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::" + tcpTypeId_d)); //Dctcp configuration

	//TCP connection from N1 to N3
         //creating sink at N3
	  uint16_t sinkPort55q = 9078;           
	  Address sinkAddress55q (InetSocketAddress (i3i5.GetAddress (0), sinkPort55q)); // interface of n2
	  PacketSinkHelper packetSinkHelper55q ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort55q));
	  ApplicationContainer sinkApps55q = packetSinkHelper55q.Install (c.Get (3)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps55q.Start (Seconds (143.));
	  sinkApps55q.Stop (Seconds (153.0));

        //creating source at N1
        
	BulkSendHelper client55q ("ns3::TcpSocketFactory",InetSocketAddress (i3i5.GetAddress (0), sinkPort55q)); 
//S1 sends traffic to D1 only
        client55q.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps55q=client55q.Install(c.Get(1));
	clientApps55q.Start (Seconds (144.));
	
         clientApps55q.Stop (Seconds(153.0));
//3.
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::" + tcpTypeId));  //Cubic config

// TCP connection from N0 to N2 
	//creating sink at n2
	  uint16_t sinkPort5w = 9079;           
	  Address sinkAddress5w (InetSocketAddress (i2i5.GetAddress (0), sinkPort5w)); // interface of n2
	  PacketSinkHelper packetSinkHelper5w ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort5w));
	  ApplicationContainer sinkApps5w = packetSinkHelper5w.Install (c.Get (2)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps5w.Start (Seconds (154.));
	  sinkApps5w.Stop (Seconds (164.0));

        //creating source at n0
        
	BulkSendHelper client5w ("ns3::TcpSocketFactory",InetSocketAddress (i2i5.GetAddress (0), sinkPort5w)); 
//S1 sends traffic to D1 only
        client5w.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps5w=client5w.Install(c.Get(0));
	clientApps5w.Start (Seconds (155.));
	
         clientApps5w.Stop (Seconds(164.0));

Config::SetDefault ("ns3::TcpL4Protocol::SocketType", StringValue ("ns3::" + tcpTypeId_d)); //Dctcp configuration

	//TCP connection from N1 to N3
         //creating sink at N3
	  uint16_t sinkPort55w = 9020;           
	  Address sinkAddress55w (InetSocketAddress (i3i5.GetAddress (0), sinkPort55w)); // interface of n2
	  PacketSinkHelper packetSinkHelper55w ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort55w));
	  ApplicationContainer sinkApps55w = packetSinkHelper55w.Install (c.Get (3)); //n2 as sink
	  //sink1 = StaticCast<PacketSink> (sinkApps.Get (0));
	  sinkApps55w.Start (Seconds (154.));
	  sinkApps55w.Stop (Seconds (164.0));

        //creating source at N1
        
	BulkSendHelper client55w ("ns3::TcpSocketFactory",InetSocketAddress (i3i5.GetAddress (0), sinkPort55w)); 
//S1 sends traffic to D1 only
        client55w.SetAttribute("MaxBytes", UintegerValue(maxBytes));
         ApplicationContainer clientApps55w=client55w.Install(c.Get(1));
	clientApps55w.Start (Seconds (155.));
	
         clientApps55w.Stop (Seconds(164.0));

//End experiments

FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();
 
Simulator::Stop (Seconds(200.0));

p2p.EnablePcapAll("finalpcap");

 Simulator::Run ();

monitor->CheckForLostPackets ();

  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
	int j=1;
  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
    {
	/*
	  Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
      if ((t.sourceAddress=="10.1.1.1"))
      {
          std::cout << "Flow " << i->first  << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
          std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
          std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
      	  std::cout << "  Throughput: " << i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024  << " Mbps\n";
     }
*/

	// std::cout << "Flow " << i->first  << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
          std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
          std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
      	  std::cout << "  Throughput for : "<<j<<"->"<< i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024  << " Mbps\n";
tp=i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024;
ct=i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds();


		//exp1
			if(j==1)
			{
			tp1=tp;
			t1=ct;
			
			}
			if(j==3)
			{
			tp2=tp;
			t2=ct;
		//	b2=iter->second.rxBytes * 8.0 ;
			}	
			if(j==5)
			{
			tp3=tp;
			t3=ct;
		//	b3=iter->second.rxBytes * 8.0 ;
			}

		
			// exp2
			if(j==7)
			{
			tp7=tp;
			t7=ct;
		//	b7=iter->second.rxBytes * 8.0 ;
			}
			if(j==11)
			{
			tp8=tp;
			t8=ct;
		//	b8=iter->second.rxBytes * 8.0 ;
			}	
			if(j==15)
			{
			tp9=tp;
			t9=ct;
		//	b9=iter->second.rxBytes * 8.0 ;
			}
			if(j==8)
			{
			tp10=tp;
			t10=ct;
		//	b10=iter->second.rxBytes * 8.0 ;
			}
			if(j==12)
			{
			tp11=tp;
			t11=ct;
		//	b11=iter->second.rxBytes * 8.0 ;
			}	
			if(j==16)
			{
			tp12=tp;
			t12=ct;
		//	b12=iter->second.rxBytes * 8.0 ;
			}

		//exp3
			if(j==19)
			{
			tp19=tp;
			t19=ct;
		//	b19=iter->second.rxBytes * 8.0 ;
			}
			if(j==21)
			{
			tp20=tp;
			t20=ct;
		//	b20=iter->second.rxBytes * 8.0 ;
			}	
			if(j==23)
			{
			tp21=tp;
			t21=ct;
		//	b21=iter->second.rxBytes * 8.0 ;
			}

		//exp4
		if(j==25)
			{
			tp25=tp;
			t25=ct;
		//	b25=iter->second.rxBytes * 8.0 ;
			}
			if(j==29)
			{
			tp26=tp;
			t26=ct;
		//	b26=iter->second.rxBytes * 8.0 ;
			}	
			if(j==33)
			{
			tp27=tp;
			t27=ct;
		//	b27=iter->second.rxBytes * 8.0 ;
			}
			if(j==26)
			{
			tp28=tp;
			t28=ct;
		//	b28=iter->second.rxBytes * 8.0 ;
			}
			if(j==30)
			{
			tp29=tp;
			t29=ct;
		//	b29=iter->second.rxBytes * 8.0 ;
			}	
			if(j==34)
			{
			tp30=tp;
			t30=ct;
		//	b30=iter->second.rxBytes * 8.0 ;
			}

		
		//exp5

			if(j==37)
			{
			tp37=tp;
			t37=ct;
		//	b37=iter->second.rxBytes * 8.0 ;
			}
			if(j==41)
			{
			tp38=tp;
			t38=ct;
		//	b38=iter->second.rxBytes * 8.0 ;
			}	
			if(j==45)
			{
			tp39=tp;
			t39=ct;
		//	b39=iter->second.rxBytes * 8.0 ;
			}
			if(j==38)
			{
			tp40=tp;
			t40=ct;
		//	b40=iter->second.rxBytes * 8.0 ;
			}
			if(j==42)
			{
			tp41=tp;
			t41=ct;
		//	b41=iter->second.rxBytes * 8.0 ;
			}	
			if(j==46)
			{
			tp42=tp;
			t42=ct;
		//	b42=iter->second.rxBytes * 8.0 ;
			}


        j=j+1;
    }
	 t_avg1=(tp1+tp2+tp3)/3;
			 t_avg2=(tp7+tp8+tp9)/3;
 			t_avg3=(tp10+tp11+tp12)/3;
 			t_avg4=(tp19+tp20+tp21)/3;
 			t_avg5=(tp25+tp26+tp27)/3;
 			t_avg6=(tp28+tp29+tp30)/3;
 			t_avg7=(tp37+tp38+tp39)/3;
 			t_avg8=(tp40+tp41+tp42)/3;

			 
			t_sd1=sqrt(((pow( tp1 - t_avg1,2)) + (pow(tp2-t_avg1,2)) + (pow(tp3-t_avg1,2)))/3);
			t_sd2=sqrt(((pow( tp7 - t_avg2,2)) + (pow(tp8-t_avg2,2)) + (pow(tp9-t_avg2,2)))/3);
			t_sd3=sqrt(((pow( tp10 - t_avg3,2)) + (pow(tp11-t_avg3,2)) + (pow(tp12-t_avg3,2)))/3);
			t_sd4=sqrt(((pow( tp19 - t_avg4,2)) + (pow(tp20-t_avg4,2)) + (pow(tp21-t_avg4,2)))/3);
			t_sd5=sqrt(((pow( tp25 - t_avg5,2)) + (pow(tp26-t_avg5,2)) + (pow(tp27-t_avg5,2)))/3);
			t_sd6=sqrt(((pow( tp28 - t_avg6,2)) + (pow(tp29-t_avg6,2)) + (pow(tp30-t_avg6,2)))/3);
			t_sd7=sqrt(((pow( tp37 - t_avg7,2)) + (pow(tp38-t_avg7,2)) + (pow(tp39-t_avg7,2)))/3);
			t_sd8=sqrt(((pow( tp40 - t_avg8,2)) + (pow(tp41-t_avg8,2)) + (pow(tp42-t_avg8,2)))/3);

		
			 a_avg1=(t1+t2+t3)/3;
			 a_avg2=(t7+t8+t9)/3;
 			a_avg3=(t10+t11+t12)/3;
 			a_avg4=(t19+t20+t21)/3;
 			a_avg5=(t25+t26+t27)/3;
 			a_avg6=(t28+t29+t30)/3;
 			a_avg7=(t37+t38+t39)/3;
 			a_avg8=(t40+t41+t42)/3;

			a_sd1=sqrt(((pow( t1 - a_avg1,2)) + (pow(t2-a_avg1,2)) + (pow(t3-a_avg1,2)))/3);
			a_sd2=sqrt(((pow( t7 - a_avg2,2)) + (pow(t8-a_avg2,2)) + (pow(t9-a_avg2,2)))/3);
			a_sd3=sqrt(((pow( t10 - a_avg3,2)) + (pow(t11-a_avg3,2)) + (pow(t12-a_avg3,2)))/3);
			a_sd4=sqrt(((pow( t19 - a_avg4,2)) + (pow(t20-a_avg4,2)) + (pow(t21-a_avg4,2)))/3);
			a_sd5=sqrt(((pow( t25 - a_avg5,2)) + (pow(t26-a_avg5,2)) + (pow(t27-a_avg5,2)))/3);
			a_sd6=sqrt(((pow( t28 - a_avg6,2)) + (pow(t29-a_avg6,2)) + (pow(t30-a_avg6,2)))/3);
			a_sd7=sqrt(((pow( t37 - a_avg7,2)) + (pow(t38-a_avg7,2)) + (pow(t39-a_avg7,2)))/3);
			a_sd8=sqrt(((pow( t40 - a_avg8,2)) + (pow(t41-a_avg8,2)) + (pow(t42-a_avg8,2)))/3);
	
	myFile << "exp,r1_s1,r2_s1,r3_s1,avg_s1,std_s1,unit_s1,r1_s2,r2_s2,r3_s2,avg_s2,std_s2,unit_s2,\n";

			
	 // Send data to the stream
    myFile << "th_1,"<< tp1<<","<<tp2<<","<<tp3<<","<<t_avg1<<","<<t_sd1<<","<<"Mbps"<<",,,,,,\n";

   myFile << "th_2,"<< tp7<<","<<tp8<<","<<tp9<<","<<t_avg2<<","<<t_sd2<<","<<"Mbps"<<","<<tp10<<","<<tp11<<","<<tp12<<","<<t_avg3<<","<<t_sd3<<",Mbps"<<"\n";

    myFile << "th_3,"<< tp19<<","<<tp20<<","<<tp21<<","<<t_avg4<<","<<t_sd4<<",Mbps,,,,,,\n";
    
    myFile << "th_4,"<< tp25<<","<<tp26<<","<<tp27<<","<<t_avg5<<","<<t_sd5<<","<<"Mbps,"<<tp28<<","<<tp29<<","<<tp30<<","<<t_avg6<<","<<t_sd6<<","<<"Mbps\n";

	 myFile << "th_5,"<< tp37<<","<<tp38<<","<<tp39<<","<<t_avg7<<","<<t_sd7<<","<<"Mbps,"<<tp40<<","<<tp41<<","<<tp42<<","<<t_avg8<<","<<t_sd8<<","<<"Mbps\n";

  myFile << "afct_1,"<< t1<<","<<t2<<","<<t3<<","<<a_avg1<<","<<a_sd1<<","<<"sec"<<",,,,,,\n";
   myFile << "afct_2,"<< t7<<","<<t8<<","<<t9<<","<<a_avg2<<","<<a_sd2<<","<<"sec,"<<t10<<","<<t11<<","<<t12<<","<<a_avg3<<","<<a_sd3<<",sec"<<"\n";

    myFile << "afct_3,"<< t19<<","<<t20<<","<<t21<<","<<a_avg4<<","<<a_sd4<<",sec,,,,,,\n";
    
    myFile << "afct_4,"<< t25<<","<<t26<<","<<t27<<","<<a_avg5<<","<<a_sd5<<","<<"sec,"<<t28<<","<<t29<<","<<t30<<","<<a_avg6<<","<<a_sd6<<","<<"sec\n";

	 myFile << "afct_5,"<< t37<<","<<t38<<","<<t39<<","<<a_avg7<<","<<a_sd7<<","<<"sec,"<<t40<<","<<t41<<","<<t42<<","<<a_avg8<<","<<a_sd8<<","<<"sec\n";
          


	myFile.close();


	
     



  monitor->SerializeToXmlFile("svkumar2.flowmon", true, true);
    Simulator::Destroy ();

   return 0;
 } 
