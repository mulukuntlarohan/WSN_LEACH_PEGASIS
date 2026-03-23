# IslanderNet: WSN Protocol Comparison (LEACH vs PEGASIS)
**Course:** COSC6357  
**Project Group:** G5  

This project implements and compares the **LEACH** and **PEGASIS** protocols within a Wireless Sensor Network (WSN) using OMNeT++ and the INET Framework.


---

## 📊 Project Results
Detailed simulation results, scalar/vector analysis, and performance graphs can be found in the official report:

👉 **[View Simulation Results PDF][WSN.pdf](https://github.com/user-attachments/files/26194415/WSN.pdf)** 
*(Note: Ensure your PDF is named 'Simulation_Results.pdf' and is uploaded to the root of this repository)*

---

## 💻 System Requirements
*   **Operating Systems:** macOS / Linux
*   **OMNeT++ Version:** 6.3.0
*   **INET Framework:** 4.5

---

## ⚙️ Prerequisites & Installation

### A. Installing OMNeT++
1. Open your terminal and navigate to the extracted OMNeT++ source code.
2. Set up environment variables:
   *   **macOS:** `source setenv`
   *   **Linux:** `source .setenv`
3. Configure the build: `./configure`
4. Compile: `make` (This may take some time)
5. Launch the IDE: `omnetpp`

### B. Installing INET Framework
1. Inside the OMNeT++ IDE, go to **Help** -> **Install Simulation Models**.
2. Select **INET Framework (v4.5)** and click **Install**.
3. Wait for installation and indexing to complete.

---

## 📥 Importing and Configuring

1. Unzip `COSC6357_G5_IslanderNet_Project.zip`.
2. In OMNeT++ IDE, go to **File** -> **Import**.
3. Select **General** -> **Existing Projects into Workspace** -> **Next**.
4. Browse to the unzipped folder and click **Finish**.
5. **Verify Settings:**
   *   Right-click the project folder (`WSN_G5`) -> **Properties**.
   *   **Project References:** Ensure `inet4.5` is checked.
   *   **OMNeT++:** Ensure "OMNeT++ Nature" is enabled.

---

## 🚀 Building and Running

### 1. Build the Project
*   Right-click `WSN_G5` -> **Clean Project**.
*   Right-click again -> **Build Project**. (Ensure 0 errors).

### 2. Run the Simulation
*   Navigate to the `simulations` folder.
*   Right-click `config_G5.ini` -> **Run As** -> **OMNeT++ Simulation**.

### 3. Selection Configuration
Select: `Config Group5 -- Clustered(2 clusters, 18); LEACH vs PEGASIS`.
Choose a specific run (0-23). Examples:
*   **Run #15:** (Pegasis, 18 nodes, repetition 0)
*   **Run #10:** (Leach, 26 nodes, repetition 1)

---

## 🛠 Known Issues and Deviations

### 1. Environment Setup (macOS)
We encountered path conflicts between system Python, Homebrew, and Anaconda during `./configure`. 
**Resolution:** Referenced the correct Python path in `configure.user` and temporarily deactivated Conda environments.

### 2. INET Linking
Project occasionally failed to find INET modules.
**Resolution:** Re-verified **Project References** and rebuilt the project index.

### 3. Energy Model Configuration
*   **Issue:** Nodes drained battery within 300s using standard parameters.
*   **Resolution:** Modified `config_G5.ini` to decouple physical transmission power from energy consumption. We enabled a low-power **sleep state (0.18mW)** and adjusted parameters to allow a full 30-minute simulation while maintaining realistic 100mW signal propagation.

---

## ✉️ Contact
For questions regarding the simulation or configuration:
**Rohan Mulukuntla** - [rmulukuntla@islander.tamucc.edu](mailto:rmulukuntla@islander.tamucc.edu)
