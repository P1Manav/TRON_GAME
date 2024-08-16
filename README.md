
---

## Tron Game

### Description
This Tron game is developed using the SFML library in C++. It is a two-player game where players control their bikes and try to avoid crashing into the trails left by themselves and their opponent. The game features smooth graphics and dynamic gameplay, making it an engaging experience for both players.

### How to Play the Game
If you just want to play the game without modifying the code, follow these simple steps:

1. **Clone the Repository**:
   - Clone this repository to your local machine using the following command:
     ```bash
     git clone https://github.com/P1Manav/TRON_GAME.git
     ```

2. **Run the Game**:
   - Navigate to the `Release` folder in the cloned repository.
   - Double-click on the `tron.exe` (or `tron` application file) to start playing the game.

### How to Set Up the Development Environment
If you want to view, modify, or understand the code, follow these steps to set up the development environment:

1. **Clone the Repository**:
   - Clone this repository to your local machine using the following command:
     ```bash
     git clone https://github.com/P1Manav/TRON_GAME.git
     ```

2. **Setup Visual Studio**:
   - Make sure you have Visual Studio installed. You can download it from [here](https://visualstudio.microsoft.com/downloads/).
   - Open Visual Studio and clone a new repository directly or open the `.sln` file from the project directory.

3. **Add SFML Library Paths**:
   - In Visual Studio, right-click on the project in the Solution Explorer and select **Properties**.
   - Under **C/C++** > **General**, add the path to the SFML `include` directory to **Additional Include Directories**.
   - Under **Linker** > **General**, add the path to the SFML `lib` directory to **Additional Library Directories**.
   - Under **Linker** > **Input**, add the following libraries to **Additional Dependencies**:
     - For the **Release** configuration, add:
       ```
       sfml-system.lib
       sfml-window.lib
       sfml-graphics.lib
       sfml-audio.lib
       sfml-network.lib
       ```
     - For the **Debug** configuration, add:
       ```
       sfml-system-d.lib
       sfml-window-d.lib
       sfml-graphics-d.lib
       sfml-audio-d.lib
       sfml-network-d.lib
       ```

4. **Build the Project**:
   - Set the configuration to `x86`.
   - Build the project by clicking on `Build` > `Build Solution` or pressing `Ctrl+Shift+B`.

5. **Run the Game**:
   - Run the game by clicking on `Debug` > `Start Without Debugging` or pressing `Ctrl+F5`.

### How to Play
- **Player Controls**:
  - Player 1 (Green): Use the `W`, `A`, `S`, `D` keys to move up, left, down, and right respectively.
  - Player 2 (Red): Use the arrow keys (`↑`, `←`, `↓`, `→`) to move up, left, down, and right respectively.

- **Objective**:
  - The objective of the game is to avoid crashing into your own trail or your opponent's trail. The player who survives the longest wins the game. If both players crash simultaneously, the game ends in a draw.
  - The walls in this game function like those in Pac-Man. This means that when a player moves off one edge of the screen, they reappear on the opposite side. Use this to your advantage to outmaneuver your opponent.

- **Winning the Game**:
  - If one player crashes while the other survives, the surviving player is declared the winner. The game will display the winner on the screen.

### Screenshots

<p align="center">
  <img src="Red WINS.png" alt="Red Wins" width="800">
</p>
<p align="center">
  <img src="Green WINS.png" alt="Green Wins" width="800">
</p>
<p align="center">
  <img src="DRAW!.png" alt="Draw" width="800">
</p>

---

This version provides the option to simply play the game directly without needing to set up Visual Studio, while also including the steps for those interested in development.
