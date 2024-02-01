
![Logo](https://via.placeholder.com/468x150?text=Your+Logo+Here)



# Project Title

In this project, we developed a UEFI application designed to present an interactive display of system information. Leveraging UEFI services and protocols, our program retrieves and showcases comprehensive hardware and firmware details, empowering users to seamlessly inspect and interact with key system information.

UEFI stands for "Unified Extensible Firmware Interface." It is a standard interface specification that defines a software interface between the operating system and the system firmware (BIOS or UEFI firmware) during the boot process and the runtime of an operating system. UEFI is designed to replace the traditional BIOS (Basic Input/Output System) and offers several advantages, including support for larger hard drives, faster boot times, and improved security features.

UEFI programming refers to the development of software applications, known as UEFI applications, that run on systems with UEFI firmware. UEFI applications can perform various tasks, such as configuring hardware settings, interacting with the system firmware, and providing pre-boot utilities. UEFI programming often involves using languages such as C or C++ and making use of UEFI services and protocols to interact with the underlying firmware. UEFI programming is essential for creating applications that leverage the capabilities of modern UEFI firmware, providing a more flexible and extensible environment for system initialization and management compared to the traditional BIOS. This is particularly important in the context of modern computing systems, including PCs and servers.

Some of the Important components of system information are:

- System Table:
The system table, often referred to as the EFI System Table, is a data structure provided by the UEFI firmware. It contains information about various services and protocols available in the UEFI environment. UEFI applications can access this table to interact with firmware services and obtain critical information about the system.

- SMBIOS (System Management BIOS) Table:
SMBIOS is a standard developed by the Distributed Management Task Force (DMTF) that defines a structure (table) for conveying system information to the operating system. This information includes details about the system's hardware components, such as the processor, memory, BIOS version, and more. UEFI applications can access the SMBIOS table to retrieve and use this hardware information.

- ACPI (Advanced Configuration and Power Interface) Tables:
ACPI is an industry-standard that defines power management and configuration interfaces between the operating system and the hardware. ACPI tables contain information related to system configuration, power management, and other platform-specific details. UEFI applications can use ACPI tables to obtain information about the system's power management capabilities and configurations.

- UEFI Variables:
UEFI variables are a mechanism provided by the UEFI firmware to store and retrieve configuration data. These variables are used by both the firmware and UEFI applications to store persistent information, such as boot configuration settings, system language preferences, and other runtime data. UEFI applications can access these variables to retrieve and modify system-specific settings.

The implementation of this project consists of two main components:
#### Display and Navigation Features:
- Implementing methods to display information.
- Implementing navigation, search, and filtering functionalities.
  
#### Getting the System Information:
- Utilizing UEFI functions and protocols to acquire essential system data.
- Retrieving key system information, including the system table, SMBIOS table, ACPI tables, and UEFI variables.

## Week-by-Week Milestones
Week 1: 
- Install and run Edk2
- Build a "Hello World" package.
  
Week 2:
- Familiarization with available hardware and system firmware information
- Understanding information display protocols in UEFI.
  
Week 3:
- Understanding the functions of receiving information and proficiently working with them
- Navigating through the page efficiently
  
Week 4: 
- Presenting specific information
- Transitioning the base between different pages.
  
Week 5 and 6: 
- Verifying the remaining steps for project completion.
- Conducting a more detailed planning and time allocation for each task.
- Understanding functions related to text and display to present information in an organized and aesthetically pleasing manner.


## Tools
In this section, you should mention the hardware or simulators utilized in your project.
- Qemu
- EDK II


## Implementation Details

### Features
- Navigating between page items vertically and horizontally.
- Implementing search and filter functionality.
- Incorporating word highlighting when searching.
  
An example demonstrating the utilization of these features is presented below:

<img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/f132ee88-5238-48cd-94ab-5cd74279f7ae" width="500">

### Pages
In this section, a concise overview of each page is provided. Every page is equipped with both search and filter functionalities.
#### "Main" Page:
This serves as the primary and initial page that users encounter. They can select from options including "Processor Count," "SMBIOS Table Data," "ACPI Table," and "Network Table." The user's choice determines the subsequent content displayed on the page.

<img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/7ad488db-a55e-4066-a6fd-6c58a802886a" width="500">

#### "Processor count" page:
On this page, users can observe both the total number of processors and the count of enabled processors.

<img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/635363b8-04c9-4a2c-b5c9-5585ad105556" width="500">


#### "System Management Bios" page:
On this page, you will discover comprehensive details about the system's BIOS, including information such as "BIOS Version," "BIOS Release Date," "Manufacturer," "Processor Version," "Processor Manufacturer," "Processor Max Speed," "Number of Cores," "Memory Size in MB," and "Cache Size."

<img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/c40b80af-f0b4-4707-a050-7da649d1e1d0" width="500">


#### "ACPI" page:
The ACPI (Advanced Configuration and Power Interface) tables embedded in the UEFI (Unified Extensible Firmware Interface) firmware furnish details regarding the system's configuration and power management. On this page, you can view the signature, OEM ID, and details of the ACPI table. Clicking on "items" will navigate you to another page titled "Subtle Items."

<img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/85f1d957-f6ad-4536-b7e7-ace248f38881" width="500">

##### "Subtle Items" page:
The exact ACPI tables present can vary depending on the system and firmware implementation, but commonly encountered tables include:

- RSDP (Root System Description Pointer): Contains information about the location and structure of other ACPI tables.
- RSDT (Root System Description Table): Lists the 32-bit physical addresses of other ACPI tables.
- XSDT (Extended System Description Table): Similar to RSDT but supports 64-bit physical addresses.
- FACP (Fixed ACPI Description Table): Provides information about system power management and configuration.
- DSDT (Differentiated System Description Table): Contains the main ACPI description for the system, providing details about devices, power management, and more.
- SSDT (Secondary System Description Table): Supplemental tables that provide additional information and can be loaded dynamically.
- APIC (Multiple APIC Description Table): Describes the system's interrupt controllers.
- HPET (High Precision Event Timer): Provides information about the system's timer capabilities.
- SBST (Smart Battery Specification Table): Presents information about the system's smart battery if applicable.
- BGRT (Boot Graphics Resource Table): Contains information about the system's logo or boot graphics.
- SLIT (System Locality Information Table): Describes the relative distances between processors in a multi-processor system.


<img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/ec4d23e9-99eb-44b3-ab86-a03729626e13" width="500">

#### "Network" page:
On this page, you can select any desired network interface, and upon selection, you will be redirected to another page displaying specific details about the chosen interface.

<img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/0658c3b1-aec1-4081-96af-668fbefd247a" width="500">

##### "Network Interface" page:
On this page, you will find in-depth details regarding your chosen network interface. The information presented includes:

- "State": current operational status of the network interface.
- "Hardware Address": a unique identifier assigned to the network interface. It is a combination of letters and numbers assigned to network interfaces for communication on the physical network.
- "Media state": link status or connection status of the network interface.
- "Interface type": the technology or protocol used by the network interface for communication.


<img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/88ac8337-42f8-48b7-81d2-fad9d918dc36" width="500">

## How to Run

- Edit `setup_env.sh` to match your system and run `. ./setup_env.sh`.
- Use `make run` to build the package and start qemu. Then enter the following commands to run the program:
```
Shell> FS0:MainTable.efi
```
- Press `Ctrl-A X` to terminate.


## Results
You can observe our program performance on an actual system below:

1- <img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/39429486-df8f-4a35-a5b7-1c7a05629f07" width="500">

2- <img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/d1108ee7-1fd3-4279-9f10-1714ee059b85" width="500">

3- <img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/c9a07dfe-7e2f-4101-bfc0-4ead2a569520" width="500">

4- <img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/f89e923d-9cae-411e-8039-b73eb750597f" width="500">

5- <img align="center" src="https://github.com/Arman17Babaei/UEFI-System-Information-Viewer/assets/59363733/dc85ade5-a4f5-4e91-ac5b-d985cbf0c706" width="500">

## Related Links
Some links related to your project come here.
 - [EDK II](https://github.com/tianocore/edk2)
 - [UEFI Lessons](https://github.com/Kostr/UEFI-Lessons)


## Authors
Authors and their github link come here.
- [@panizhalvachi](https://github.com/panizhalvachi)
- [@Arman17Babaei](https://github.com/Arman17Babaei)
- [@yasamanzolfi](https://github.com/yasamanzolfi)

