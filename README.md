# IslanderNet: WSN Protocol Comparison (LEACH vs PEGASIS) 
**Technologies:** OMNeT++ 6.3.0, INET 4.5, C++

This project evaluates and compares the performance of **LEACH** (Low-Energy Adaptive Clustering Hierarchy) and **PEGASIS** (Power-Efficient Gathering in Sensor Information Systems) protocols in a Wireless Sensor Network environment.

---

## 📊 Simulation Analysis & Results
The complete technical report, including performance metrics, energy consumption analysis, and protocol comparisons, is available below:

### [👉 Click Here to View Full Results (PDF)](https://github.com/user-attachments/files/26194415/WSN.pdf)

> **Note:** The report covers scalar/vector analysis from 24 different simulation runs, focusing on network longevity and data propagation efficiency.

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
5. **Verify Project Settings:**
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
Example test runs:
*   **Run #15:** ($0="Pegasis", $1=18, $repetition=0)
*   **Run #10:** ($0="Leach", $1=26, $repetition=1)

---

## 🛠 Known Issues and Deviations

*   **macOS Path Conflicts:** Resolved Python path conflicts (System vs Homebrew vs Conda) by referencing the correct path in `configure.user`.
*   **INET Linking:** If modules are missing, re-verify "Project References" and rebuild the index.
*   **Energy Optimization:** Modified `config_G5.ini` to include a low-power **sleep state (0.18mW)**. This allows the simulation to run for the full 1800s while maintaining realistic signal propagation (100mW).

---

## 📬 Contact
**Rohan Mulukuntla**  
[rmulukuntla@islander.tamucc.edu](mailto:rmulukuntla@islander.tamucc.edu)  
