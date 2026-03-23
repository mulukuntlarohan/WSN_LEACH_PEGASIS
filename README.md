SYSTEM REQUIREMENTS
------------------------------------------------------------------------
Operating Systems Used: macOS and Linux
OMNeT++ Version: OMNeT++ 6.3.0
INET Framework: INET 4.5
------------------------------------------------------------------------
3. PREREQUISITES & INSTALLATION
------------------------------------------------------------------------
Before importing the project, ensure OMNeT++ and INET are installed.
A. Installing OMNeT++
1. Open your terminal.
2. Navigate to the path where you extracted the OMNeT++ source code.
3. Set up the environment variables:
- For macOS: Type `source setenv`
- For Linux: Type `source .setenv`
4. Configure the build:
- Type `./configure`
5. Compile OMNeT++:
- Type `make` (This may take some time).
6. Launch the IDE:
- Type `omnetpp`
B. Installing INET Framework (If not already installed)
1. inside the OMNeT++ IDE, go to the Header Menu.
2. Click "Help" -> "Install Simulation Models".
3. Select "INET Framework" (ensure version 4.5 is selected) and click "Install".
4. Wait for the installation and indexing to complete.
------------------------------------------------------------------------
4. IMPORTING AND CONFIGURING THE PROJECT

------------------------------------------------------------------------
1. Unzip the file `COSC6357_G5_IslanderNet_Project.zip` to a known location.
2. In the OMNeT++ IDE, go to "File" -> "Import".
3. Select "General" -> "Existing Projects into Workspace" and click "Next".
4. Browse to the unzipped folder, select the project, and click "Finish".
5. Verifying Project Settings:
- Right-click the project folder (WSN_G5) -> "Properties".
- Go to "Project References": Ensure `inet4.5` is checked.
- Go to "OMNeT++": Ensure "OMNeT++ Nature" is enabled.
- Click "Apply and Close".
------------------------------------------------------------------------
5. BUILDING AND RUNNING THE SIMULATION
------------------------------------------------------------------------
1. Build the Project:
- Right-click on the project folder `WSN_G5`.
- Select "Clean Project".
- Once cleaned, right-click again and select "Build Project".
- Ensure the build completes with "0 Errors".
2. Run the Simulation:
- Navigate to the `simulations` folder in the Project Explorer.
- Locate `config_G5.ini`.
- Right-click `config_G5.ini` -> "Run As" -> "OMNeT++ Simulation".
3. Selecting the Run Configuration:
- A dialog box will appear showing available configurations.
- Select: `Config Group5 -- Clustered(2 clusters,18); LEACH vs PEGASIS`.
- You will see a list of numbered runs (0 to 23) with different protocols and energy levels.
- Examples to test:
* Run #15: ($0="Pegasis", $1=18, $repetition=0)
* Run #10: ($0="Leach", $1=26, $repetition=1)
- Click "OK" to start.
4. Viewing Results:
- The Qtenv simulation window will open. You can press the "Fast Forward" (double arrow)
button to speed up the simulation.
- Once the simulation finishes (1800s), scalar (.sca) and vector (.vec) files will be generated in
the `results` folder.
------------------------------------------------------------------------
6. KNOWN ISSUES AND DEVIATIONS
------------------------------------------------------------------------
1. Environment Setup:
- We encountered path conflicts between the system Python, Homebrew Python, and
Anaconda environments on macOS during the initial OMNeT++ setup (`./configure`). We
resolved this by ensuring the correct Python path was referenced in `configure.user` or by
temporarily deactivating Conda environments.
2. INET Linking:
- Initial issues occurred where the project could not find INET modules. This was resolved by
re-verifying the "Project References" and rebuilding the project index.
3. Energy Model Configuration:
- Issue: In initial tests, sensor nodes drained their battery completely within 300 seconds using
standard radio parameters.

- Resolution: We modified `config_G5.ini` to decouple physical transmission power from
energy consumption. We enabled a low-power "sleep" state (0.18mW) for the idle mode and
adjusted transmission/reception parameters. This allows the simulation to run the full 30 minutes
while maintaining realistic signal propagation (100mW physical transmission power to reach the
Base Station).
