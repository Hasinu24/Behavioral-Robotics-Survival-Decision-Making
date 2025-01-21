
# Behavioral-Robotics-Survival-Decision-Making 🤖



1. ## 🌟 Project Overview

This project implements a behavior-based architecture enabling an artificial agent to autonomously prioritize and fulfill survival-related needs in dynamic environments. The system balances competing demands such as resource acquisition (e.g., 🥤 water, 🍎 food) and threat avoidance, ensuring optimal performance in real-time scenarios.

2. ## ✨ Features

* ### 🛠️ Multi-layered Behavioral Architecture
  * Modular design for robust decision-making.

* ### 🔄 Dynamic Prioritization
  * Adjusts actions based on internal states and environmental conditions.

* ### 🥤 Resource-Seeking Behaviors
  * Locates and retrieves essential resources like food and water.

* ### ⚠️ Threat Response System
  * Reacts effectively to environmental dangers.

* ### 🌍 Random Walk Exploration
  * Ensures environmental coverage and resource discovery.

* ### 🎛️ Real-Time Sensor Processing
  * Integrates inputs from multiple sensors for situational awareness.

* ### 🎨 Color-Based Resource Detection
  * Identifies resources using camera input and image analysis.

3. ## 📂 Repository Structure

Here's an overview of the project directory to make navigation simple:

```plaintext
behavioral-robotics/
├── src/
│   ├── main.c                    # Main execution file
│   ├── sensors/                  # Sensor-related modules
│   │   ├── camera.c             # Camera-based input processing
│   │   └── receiver.c           # Communication module
│   ├── behaviors/               # Core behaviors
│   │   ├── resource_seeking.c   # Finds and collects resources
│   │   └── threat_response.c    # Handles threats dynamically
│   │   └── random_walk.c        # Implements random exploration
│   └── utils/
│       └── movement.c           # General movement functions
├── include/
│   └── robot_config.h           # Configuration settings for behaviors
├── docs/                        # Documentation
│   ├── architecture.md          # Detailed architecture overview
│   └── behaviors.md             # Behavior implementation details
├── tests/
│   └── test_behaviors.c         # Unit tests for behaviors
├── webots/                      # Webots-specific files
│   └── worlds/
│       └── robot_environment.wbt # Simulation environment
└── README.md                    # Project overview and instructions
```

4. ## 💻 Prerequisites

* 🤖 Webots: Version R2024a or later.
* 💻 C Compiler: GCC or equivalent.
* 📚 Basic Knowledge: Familiarity with robotics and behavior-based architectures.

5. ## 🔧 Installation

* Open the project in Webots:
  * Launch Webots.
  * Navigate to File → Open World.
  * Open `webots/worlds/robot_environment.wbt`.

6. ## 🎮 Usage

Once the simulation starts, the robot operates autonomously and performs these tasks:

* 💡 Monitor Internal States: Tracks hunger, thirst, and health levels.
* 📷 Resource Detection: Uses camera input to identify and locate resources.
* 🔝 Need Prioritization: Determines the most pressing need based on internal conditions.
* 🎯 Behavior Execution: Selects and executes the behavior addressing the highest-priority need.

To start the simulation, run:
```bash
webots webots/worlds/robot_environment.wbt
```

7. ## ⚙️ Configuration

Adjust key parameters in `include/robot_config.h` to fine-tune robot behavior:

* 🎚️ Sensor Thresholds: Adjust detection sensitivity for resources and threats.
* 🏃 Movement Speeds: Define speed parameters for exploration and pursuit behaviors.
* 🎨 Resource Detection Settings: Fine-tune color profiles and detection ranges.
* ⏳ State Decay Rates: Configure rates at which hunger, thirst, and health deteriorate.

8. ## 📖 Acknowledgments

* 📖 Based on research by Spier and McFarland (1997).
* 🤖 Developed using the Webots Robotics Simulator.
* 🌱 Inspired by biological systems and neuromodulation concepts.

Made with ❤️ by Hasinu24

