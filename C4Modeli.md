Context Diagram
```plantuml
@startuml
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Context.puml
' uncomment the following line and comment the first to use locally
' !include C4_Context.puml

title System Context diagram for AutoWare Auto and ROS2

Person(Integrator, "Integrator", "Autonomous Vehicle Developer")
System(Autoware_Auto,"Autoware Auto", " Autoware is the world's first all-in-one open-source software for self-driving vehicles hosted under the Autoware Foundation. The Autoware.Auto project, based on ROS 2, is the next generation successor of the Autoware.AI project, based on ROS 1.")


System(Ros2 , "ROS2", "Robot Operating System (ROS) is a set of open source algorithms, hardware driver software and tools developed to develop robot control software. ROS includes mature open source libraries to be used for navigation, control, motion planning, vision and simulation purposes.")

System_Ext(DDS, "DDS", "Data Distribution Service (DDS)  is a data centric publish/subscribe middleware used for data transmission in distributed real time systems. ")

Rel(Integrator, Autoware_Auto, "Utilizes")
Rel_Neighbor(Autoware_Auto, Ros2 , "Based on")

Rel(Ros2 , DDS, "communication middleware")

@enduml
```


Container Diagram
```plantuml
@startuml
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Container.puml
' uncomment the following line and comment the first to use locally
' !include C4_Container.puml

' LAYOUT_TOP_DOWN()
' LAYOUT_AS_SKETCH()
LAYOUT_WITH_LEGEND()

title Container diagram for Autoware Auto


 Container(Sensing, "Sensing", "Autoware mainly recognizes road environments with the help of LIDAR scanners and cameras.") 

 Container(Localization, "Localization", "The localization contains nodes and libraries which provide an estimate regarding the location of the vehicle using various methods and algorithms") 
Container(Perception, "Perception",  "filters and segmentation. The filters are nodes and libraries which are part of the filtering pipeline for sensor data. Nodes work as standalone filtering modules or cascaded with other filtering algorithms working on the same sensor data types. Enable sensor data to be grouped into clusters or objects of interest which can provide downstream procsses more information about the environment.") 
Container(Planning, "Planning",  "Produce a trajectory towards a provided goal. Involved in the planning process in order to alleviate the complexity of the path-planning optimization problem.")

Container(Control, "Control", "Nodes and libraries related to the controller functionalities of the vehicle. They enable the autonomous vehicle to follow a reference trajectory appropriately by converting the input trajectory into longitudinal and lateral commands.")
Container(VehicleInterface, "Vehicle Interface", "Sensor/Actuator Drivers")

 
System_Ext(Vehicle, "Vehicle", "The Autonomous Vehicle") 
System_Ext(Sensors, "Sensors", "Lidar, Camera, GPS etc.")

Rel(Sensors, Sensing, "Socket, Serial etc.")
Rel(Sensing, Perception, "Sensing Data")
Rel_Neighbor(Perception, Planning, "Surrounding Environment") 
Rel_Neighbor(Planning, Control, "Trajectory")

Rel(Control, VehicleInterface, "Vehicle Commands")
Rel(VehicleInterface,Control, "Steering, Velocity Feedback")

BiRel(VehicleInterface, Vehicle, "Can, Socket, Serial")

Rel(Sensing, Localization, "Current Position and Velocity") 
Rel(Localization,Perception, "Current Position and velocity") 
Rel(Localization,Planning, "Current Position and velocity") 
Rel(Localization, Control, "Current Position and velocity")
Rel(VehicleInterface, Localization, "VehicleSensor")

@enduml
```





```plantuml
 @startuml
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Component.puml
' uncomment the following line and comment the first to use locally
' !include C4_Component.puml

LAYOUT_WITH_LEGEND()

title Component Diagram for ROS2 based Autoware Auto Application

Component_Ext(DDS, "DDS Middleware library", "DDS Library from DDS vendor")
Container(usercode, "User Code", "C++", "User code for Vehicle Interface, Perception, Planning etc.")

Container_Boundary(app, "ROS2 Components") {
Component(rmw, "RMW", "C++", "ROS middleware Interface")
Component(rcl, "rcl", "C++", "ROS Client Library")
Component(rclCPP, "rclCPP", "C++", "ROS Client Library C++ Wrapper.")
Rel(rmw, DDS, "Uses","Api")
Rel(usercode, rclCPP, "Uses","Api")
Rel(rclCPP, rcl, "Uses","Api")
Rel(rcl, rmw, "Uses","Api")
}

@enduml
```





```plantuml
@startuml
participant User_Code 
participant RCLCpp
participant RCL
participant RMW
participant DDS
autonumber 
User_Code->RCLCpp: Publisher::Publish 
RCLCpp->RCL: rcl_publish
RCL->RMW: rmw_publish
RMW->DDS: data_writer.write
@enduml

```
